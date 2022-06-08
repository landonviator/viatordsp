/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
ParaEQDemoAudioProcessor::ParaEQDemoAudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
     : AudioProcessor (BusesProperties()
                     #if ! JucePlugin_IsMidiEffect
                      #if ! JucePlugin_IsSynth
                       .withInput  ("Input",  juce::AudioChannelSet::stereo(), true)
                      #endif
                       .withOutput ("Output", juce::AudioChannelSet::stereo(), true)
                     #endif
                       ),
treeState(*this, nullptr, "PARAMETERS", createParameterLayout())
#endif
{
    treeState.addParameterListener("band1Gain", this);
    treeState.addParameterListener("band1Cutoff", this);
    treeState.addParameterListener("band1Q", this);
}

ParaEQDemoAudioProcessor::~ParaEQDemoAudioProcessor()
{
    treeState.removeParameterListener("band1Gain", this);
    treeState.removeParameterListener("band1Cutoff", this);
    treeState.removeParameterListener("band1Q", this);
}

juce::AudioProcessorValueTreeState::ParameterLayout ParaEQDemoAudioProcessor::createParameterLayout()
{
    std::vector <std::unique_ptr<juce::RangedAudioParameter>> params;
        
    auto pBand1Gain = std::make_unique<juce::AudioParameterFloat>("band1Gain", "Band1Gain", -15.0f, 15.0f, 0.0f);
    auto pBand1Cutoff = std::make_unique<juce::AudioParameterFloat>("band1Cutoff", "Band1Cutoff", 20.0f, 250.0f, 100.0f);
    auto pBand1Q = std::make_unique<juce::AudioParameterFloat>("band1Q", "Band1Q", 0.36f, 0.8f, 0.5f);
    
    params.push_back(std::move(pBand1Gain));
    params.push_back(std::move(pBand1Cutoff));
    params.push_back(std::move(pBand1Q));
    
    return { params.begin(), params.end() };
    
}

void ParaEQDemoAudioProcessor::parameterChanged(const juce::String &parameterID, float newValue)
{
    if (parameterID == "band1Gain" || parameterID == "band1Cutoff" || parameterID == "band1Q")
    {
        updateBand1(treeState.getRawParameterValue("band1Gain")->load(), treeState.getRawParameterValue("band1Cutoff")->load(), treeState.getRawParameterValue("band1Q")->load());
    }
}

//==============================================================================
const juce::String ParaEQDemoAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool ParaEQDemoAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool ParaEQDemoAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool ParaEQDemoAudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double ParaEQDemoAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int ParaEQDemoAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int ParaEQDemoAudioProcessor::getCurrentProgram()
{
    return 0;
}

void ParaEQDemoAudioProcessor::setCurrentProgram (int index)
{
}

const juce::String ParaEQDemoAudioProcessor::getProgramName (int index)
{
    return {};
}

void ParaEQDemoAudioProcessor::changeProgramName (int index, const juce::String& newName)
{
}

//==============================================================================
void ParaEQDemoAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    // Initialize spec for dsp modules
    juce::dsp::ProcessSpec spec;
    spec.maximumBlockSize = samplesPerBlock;
    spec.sampleRate = sampleRate;
    spec.numChannels = getTotalNumOutputChannels();
    
    band1.prepare(spec);
    updateBand1(treeState.getRawParameterValue("band1Gain")->load(), treeState.getRawParameterValue("band1Cutoff")->load(), treeState.getRawParameterValue("band1Q")->load());
}

void ParaEQDemoAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool ParaEQDemoAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
  #if JucePlugin_IsMidiEffect
    juce::ignoreUnused (layouts);
    return true;
  #else
    // This is the place where you check if the layout is supported.
    // In this template code we only support mono or stereo.
    // Some plugin hosts, such as certain GarageBand versions, will only
    // load plugins that support stereo bus layouts.
    if (layouts.getMainOutputChannelSet() != juce::AudioChannelSet::mono()
     && layouts.getMainOutputChannelSet() != juce::AudioChannelSet::stereo())
        return false;

    // This checks if the input layout matches the output layout
   #if ! JucePlugin_IsSynth
    if (layouts.getMainOutputChannelSet() != layouts.getMainInputChannelSet())
        return false;
   #endif

    return true;
  #endif
}
#endif

void ParaEQDemoAudioProcessor::processBlock (juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiMessages)
{
    juce::ScopedNoDenormals noDenormals;
    auto totalNumInputChannels  = getTotalNumInputChannels();
    auto totalNumOutputChannels = getTotalNumOutputChannels();

    juce::dsp::AudioBlock<float> audioBlock {buffer};
    band1.process(juce::dsp::ProcessContextReplacing<float>(audioBlock));
}

void ParaEQDemoAudioProcessor::updateBand1(float gain, float cutoff, float q)
{
    *band1.state = *juce::dsp::IIR::Coefficients<float>::makeLowShelf(getSampleRate(), cutoff, q, juce::Decibels::decibelsToGain(gain));
}

//==============================================================================
bool ParaEQDemoAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

juce::AudioProcessorEditor* ParaEQDemoAudioProcessor::createEditor()
{
    //return new ParaEQDemoAudioProcessorEditor (*this);
    return new juce::GenericAudioProcessorEditor (*this);
}

//==============================================================================
void ParaEQDemoAudioProcessor::getStateInformation (juce::MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
}

void ParaEQDemoAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
}

//==============================================================================
// This creates new instances of the plugin..
juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new ParaEQDemoAudioProcessor();
}
