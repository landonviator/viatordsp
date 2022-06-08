/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
MixDemoAudioProcessor::MixDemoAudioProcessor()
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
    treeState.addParameterListener("input", this);
    treeState.addParameterListener("mix", this);
}

MixDemoAudioProcessor::~MixDemoAudioProcessor()
{
    treeState.removeParameterListener("input", this);
    treeState.removeParameterListener("mix", this);
}

juce::AudioProcessorValueTreeState::ParameterLayout MixDemoAudioProcessor::createParameterLayout()
{
    std::vector <std::unique_ptr<juce::RangedAudioParameter>> params;
        
    auto pInput = std::make_unique<juce::AudioParameterFloat>("input", "Input", -24.0f, 24.0f, 0.0f);
    auto pWet = std::make_unique<juce::AudioParameterFloat>("mix", "Mix", 0.0f, 100.0f, 0.0f);
    
    params.push_back(std::move(pInput));
    params.push_back(std::move(pWet));
    
    return { params.begin(), params.end() };
}

void MixDemoAudioProcessor::parameterChanged(const juce::String &parameterID, float newValue)
{
    drive = juce::Decibels::decibelsToGain(treeState.getRawParameterValue("input")->load());
    mix = juce::jmap(treeState.getRawParameterValue("mix")->load(), 0.0f, 100.0f, 0.0f, 1.0f);
}

//==============================================================================
const juce::String MixDemoAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool MixDemoAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool MixDemoAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool MixDemoAudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double MixDemoAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int MixDemoAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int MixDemoAudioProcessor::getCurrentProgram()
{
    return 0;
}

void MixDemoAudioProcessor::setCurrentProgram (int index)
{
}

const juce::String MixDemoAudioProcessor::getProgramName (int index)
{
    return {};
}

void MixDemoAudioProcessor::changeProgramName (int index, const juce::String& newName)
{
}

//==============================================================================
void MixDemoAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    drive = juce::Decibels::decibelsToGain(treeState.getRawParameterValue("input")->load());
    mix = juce::jmap(treeState.getRawParameterValue("mix")->load(), 0.0f, 100.0f, 0.0f, 1.0f);
}

void MixDemoAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool MixDemoAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
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

void MixDemoAudioProcessor::processBlock (juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiMessages)
{
    juce::ScopedNoDenormals noDenormals;
    auto totalNumInputChannels  = getTotalNumInputChannels();
    auto totalNumOutputChannels = getTotalNumOutputChannels();

    for (auto i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
        buffer.clear (i, 0, buffer.getNumSamples());
    
    juce::dsp::AudioBlock<float> audioBlock {buffer};
    
    for (auto channel = 0; channel < audioBlock.getNumChannels(); channel++)
    {
        auto* data = audioBlock.getChannelPointer(channel);
        
        for (auto sample = 0; sample < audioBlock.getNumSamples(); sample++)
        {
            auto input = data[sample] * drive;
            float output;
            
            if (input <= thresh)
            {
                output = input;
            }
            
            else if (input > thresh)
            {
                output = thresh + (input - thresh) / (1.0 + std::pow((( input - thresh ) / (1.0 - thresh)), 2.0));
            }
            
            else if (input > 1.0)
            {
                output = (thresh + 1.0) * 0.5;
            }
            
            if (input < -0.8)
            {
                output = -0.8;
            }
            
            data[sample] = (1.0 - mix) * output + data[sample] * mix;
        }
    }
    
//    x < a:
//      f(x) = x
//    x > a:
//      f(x) = a + (x-a)/(1+((x-a)/(1-a))^2)
//    x > 1:
//      f(x) = (a+1)/2
    
}

//==============================================================================
bool MixDemoAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

juce::AudioProcessorEditor* MixDemoAudioProcessor::createEditor()
{
    //return new MixDemoAudioProcessorEditor (*this);
    return new juce::GenericAudioProcessorEditor (*this);
}

//==============================================================================
void MixDemoAudioProcessor::getStateInformation (juce::MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
}

void MixDemoAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
}

//==============================================================================
// This creates new instances of the plugin..
juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new MixDemoAudioProcessor();
}
