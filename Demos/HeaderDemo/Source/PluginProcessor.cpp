/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
HeaderDemoAudioProcessor::HeaderDemoAudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
     : AudioProcessor (BusesProperties()
                     #if ! JucePlugin_IsMidiEffect
                      #if ! JucePlugin_IsSynth
                       .withInput  ("Input",  juce::AudioChannelSet::stereo(), true)
                      #endif
                       .withOutput ("Output", juce::AudioChannelSet::stereo(), true)
                     #endif
                       )
, treeState(*this, nullptr, "PARAMETERS", createParameterLayout())
#endif
{
    cpuPercentage.store(0.0);
    
    treeState.addParameterListener("input", this);
}

HeaderDemoAudioProcessor::~HeaderDemoAudioProcessor()
{
    treeState.removeParameterListener("input", this);
}

juce::AudioProcessorValueTreeState::ParameterLayout HeaderDemoAudioProcessor::createParameterLayout()
{
    std::vector <std::unique_ptr<juce::RangedAudioParameter>> params;
        
    auto pInput = std::make_unique<juce::AudioParameterFloat>("input", "Input", -12.0f, 12.0f, 0.0f);
    
    params.push_back(std::move(pInput));
    
    return { params.begin(), params.end() };
}

void HeaderDemoAudioProcessor::parameterChanged(const juce::String &parameterID, float newValue)
{
    myDistortionModule.setDrive(treeState.getRawParameterValue("input")->load());
}

//==============================================================================
const juce::String HeaderDemoAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool HeaderDemoAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool HeaderDemoAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool HeaderDemoAudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double HeaderDemoAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int HeaderDemoAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int HeaderDemoAudioProcessor::getCurrentProgram()
{
    return 0;
}

void HeaderDemoAudioProcessor::setCurrentProgram (int index)
{
}

const juce::String HeaderDemoAudioProcessor::getProgramName (int index)
{
    return {};
}

void HeaderDemoAudioProcessor::changeProgramName (int index, const juce::String& newName)
{
}

//==============================================================================
void HeaderDemoAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    // Initialize spec for dsp modules
    juce::dsp::ProcessSpec spec;
    spec.maximumBlockSize = samplesPerBlock;
    spec.sampleRate = sampleRate;
    spec.numChannels = getTotalNumOutputChannels();
    
    gainModule.prepare(spec);
    gainModule.setGainDecibels(treeState.getRawParameterValue("input")->load());
    gainModule.setRampDurationSeconds(0.02);
    
    myDistortionModule.prepare(spec);
    myDistortionModule.setDrive(treeState.getRawParameterValue("input")->load());
    
    cpuMeasureModule.reset(spec.sampleRate, spec.maximumBlockSize);
}

void HeaderDemoAudioProcessor::releaseResources()
{
    gainModule.reset();
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool HeaderDemoAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
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

void HeaderDemoAudioProcessor::processBlock (juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiMessages)
{
    juce::ScopedNoDenormals noDenormals;
    auto totalNumInputChannels  = getTotalNumInputChannels();
    auto totalNumOutputChannels = getTotalNumOutputChannels();
    
    juce::AudioProcessLoadMeasurer::ScopedTimer s(cpuMeasureModule);
    
    juce::dsp::AudioBlock<float> audioBlock {buffer};
    
    myDistortionModule.processBlock(audioBlock);
    
    cpuPercentage.store(cpuMeasureModule.getLoadAsPercentage());
}

float HeaderDemoAudioProcessor::getCPU()
{
    return cpuPercentage.load();
}

//==============================================================================
bool HeaderDemoAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

juce::AudioProcessorEditor* HeaderDemoAudioProcessor::createEditor()
{
    return new HeaderDemoAudioProcessorEditor (*this);
    //return new juce::GenericAudioProcessorEditor (*this);
}

//==============================================================================
void HeaderDemoAudioProcessor::getStateInformation (juce::MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
}

void HeaderDemoAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
}

//==============================================================================
// This creates new instances of the plugin..
juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new HeaderDemoAudioProcessor();
}
