/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
DelayModuleAudioProcessor::DelayModuleAudioProcessor()
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
    treeState.addParameterListener("delay", this);
}

DelayModuleAudioProcessor::~DelayModuleAudioProcessor()
{
    treeState.removeParameterListener("delay", this);
}

juce::AudioProcessorValueTreeState::ParameterLayout DelayModuleAudioProcessor::createParameterLayout()
{
    std::vector <std::unique_ptr<juce::RangedAudioParameter>> params;
        
    auto pDelay = std::make_unique<juce::AudioParameterFloat>("delay", "Delay", 0.01f, 1000.0f, 500.0f);
    
    params.push_back(std::move(pDelay));
    
    return { params.begin(), params.end() };
}

void DelayModuleAudioProcessor::parameterChanged(const juce::String &parameterID, float newValue)
{
    delayModule.setDelay(newValue / 1000.0f * getSampleRate());
}

//==============================================================================
const juce::String DelayModuleAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool DelayModuleAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool DelayModuleAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool DelayModuleAudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double DelayModuleAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int DelayModuleAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int DelayModuleAudioProcessor::getCurrentProgram()
{
    return 0;
}

void DelayModuleAudioProcessor::setCurrentProgram (int index)
{
}

const juce::String DelayModuleAudioProcessor::getProgramName (int index)
{
    return {};
}

void DelayModuleAudioProcessor::changeProgramName (int index, const juce::String& newName)
{
}

//==============================================================================
void DelayModuleAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    // Initialize spec for dsp modules
    juce::dsp::ProcessSpec spec;
    spec.maximumBlockSize = samplesPerBlock;
    spec.sampleRate = sampleRate;
    spec.numChannels = getTotalNumOutputChannels();
    
    delayModule.prepare(spec);
    delayModule.reset();
    std::fill (lastDelayOutput.begin(), lastDelayOutput.end(), 0.0f);
    delayModule.setDelay(treeState.getRawParameterValue("delay")->load() / 1000.0f * getSampleRate());
}

void DelayModuleAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool DelayModuleAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
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

void DelayModuleAudioProcessor::processBlock (juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiMessages)
{
    juce::ScopedNoDenormals noDenormals;
    auto totalNumInputChannels  = getTotalNumInputChannels();
    auto totalNumOutputChannels = getTotalNumOutputChannels();

    const auto numChannels = juce::jmax (totalNumInputChannels, totalNumOutputChannels);
    
    auto audioBlock = juce::dsp::AudioBlock<float> (buffer).getSubsetChannelBlock (0, (size_t) numChannels);
    auto context = juce::dsp::ProcessContextReplacing<float>(audioBlock);
    
    const auto& input = context.getInputBlock();
    const auto& output = context.getOutputBlock();
    
    
    for (size_t channel = 0; channel < numChannels; ++channel)
    {
        
        auto* samplesIn = input.getChannelPointer (channel);
        auto* samplesOut = output.getChannelPointer (channel);
        
        for (size_t sample = 0; sample < input.getNumSamples(); ++sample)
        {
            //auto input = samplesIn[sample] - lastDelayOutput[channel];
            auto input = samplesIn[sample];
            delayModule.pushSample((int)channel, input);
            samplesOut[sample] = delayModule.popSample((int)channel);
            
            //lastDelayOutput[channel] = samplesOut[sample] * 0.99;
        }
    }
}

//==============================================================================
bool DelayModuleAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

juce::AudioProcessorEditor* DelayModuleAudioProcessor::createEditor()
{
    //return new DelayModuleAudioProcessorEditor (*this);
    return new juce::GenericAudioProcessorEditor (*this);
}

//==============================================================================
void DelayModuleAudioProcessor::getStateInformation (juce::MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
}

void DelayModuleAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
}

//==============================================================================
// This creates new instances of the plugin..
juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new DelayModuleAudioProcessor();
}
