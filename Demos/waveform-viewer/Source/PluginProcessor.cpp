/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
WaveformviewerAudioProcessor::WaveformviewerAudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
     : AudioProcessor (BusesProperties()
                     #if ! JucePlugin_IsMidiEffect
                      #if ! JucePlugin_IsSynth
                       .withInput  ("Input",  juce::AudioChannelSet::stereo(), true)
                      #endif
                       .withOutput ("Output", juce::AudioChannelSet::stereo(), true)
                     #endif
                       ), waveViewer(1)
#endif
{
    waveViewer.setRepaintRate(30);
    waveViewer.setBufferSize(256);
}

WaveformviewerAudioProcessor::~WaveformviewerAudioProcessor()
{
}

//==============================================================================
const juce::String WaveformviewerAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool WaveformviewerAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool WaveformviewerAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool WaveformviewerAudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double WaveformviewerAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int WaveformviewerAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int WaveformviewerAudioProcessor::getCurrentProgram()
{
    return 0;
}

void WaveformviewerAudioProcessor::setCurrentProgram (int index)
{
}

const juce::String WaveformviewerAudioProcessor::getProgramName (int index)
{
    return {};
}

void WaveformviewerAudioProcessor::changeProgramName (int index, const juce::String& newName)
{
}

//==============================================================================
void WaveformviewerAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    waveViewer.clear();
}

void WaveformviewerAudioProcessor::releaseResources()
{
    waveViewer.clear();
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool WaveformviewerAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
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

void WaveformviewerAudioProcessor::processBlock (juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiMessages)
{
    juce::ScopedNoDenormals noDenormals;
    auto totalNumInputChannels  = getTotalNumInputChannels();
    auto totalNumOutputChannels = getTotalNumOutputChannels();


    for (auto i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
        buffer.clear (i, 0, buffer.getNumSamples());
    
    currentNumChannels = buffer.getNumChannels();
    waveViewer.pushBuffer(buffer);

}

int WaveformviewerAudioProcessor::getCurrentNumChannels()
{
    return currentNumChannels;
}

//==============================================================================
bool WaveformviewerAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

juce::AudioProcessorEditor* WaveformviewerAudioProcessor::createEditor()
{
    return new WaveformviewerAudioProcessorEditor (*this);
}

//==============================================================================
void WaveformviewerAudioProcessor::getStateInformation (juce::MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
}

void WaveformviewerAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
}

//==============================================================================
// This creates new instances of the plugin..
juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new WaveformviewerAudioProcessor();
}
