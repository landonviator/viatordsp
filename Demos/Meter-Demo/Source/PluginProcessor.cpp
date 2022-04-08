/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
MeterDemoAudioProcessor::MeterDemoAudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
     : AudioProcessor (BusesProperties()
                     #if ! JucePlugin_IsMidiEffect
                      #if ! JucePlugin_IsSynth
                       .withInput  ("Input",  juce::AudioChannelSet::stereo(), true)
                      #endif
                       .withOutput ("Output", juce::AudioChannelSet::stereo(), true)
                     #endif
                       )
#endif
{
}

MeterDemoAudioProcessor::~MeterDemoAudioProcessor()
{
}


//==============================================================================
const juce::String MeterDemoAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool MeterDemoAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool MeterDemoAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool MeterDemoAudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double MeterDemoAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int MeterDemoAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int MeterDemoAudioProcessor::getCurrentProgram()
{
    return 0;
}

void MeterDemoAudioProcessor::setCurrentProgram (int index)
{
}

const juce::String MeterDemoAudioProcessor::getProgramName (int index)
{
    return {};
}

void MeterDemoAudioProcessor::changeProgramName (int index, const juce::String& newName)
{
}

//==============================================================================
void MeterDemoAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    
    
    leftLevel.reset(sampleRate, 0.5);
    rightLevel.reset(sampleRate, 0.5);
}

void MeterDemoAudioProcessor::releaseResources()
{
    leftLevel.setTargetValue(-60.0);
    rightLevel.setTargetValue(-60.0);
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool MeterDemoAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
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

void MeterDemoAudioProcessor::processBlock (juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiMessages)
{
    juce::ScopedNoDenormals noDenormals;
    //auto totalNumInputChannels  = getTotalNumInputChannels();
    //auto totalNumOutputChannels = getTotalNumOutputChannels();

    // Get new current value for all samples in block
    leftLevel.skip(buffer.getNumSamples());
    rightLevel.skip(buffer.getNumSamples());
    
    // Convert values from gain to dB
    setLevelForMeter(buffer);
    
    // Smoothed value logic for levels
    levelSmoothLogic();
    
    for (int ch = 0; ch < buffer.getNumChannels(); ++ch)
    {
        float* data = buffer.getWritePointer(ch);
        
        for (int sample = 0; sample < buffer.getNumSamples(); ++sample)
        {
            sampleValue += data[sample];
        }
    }
    
    if (sampleValue == 0.0)
    {
        leftLevel.setTargetValue(-60.0);
        rightLevel.setTargetValue(-60.0);
    }
    
    juce::AudioPlayHead::CurrentPositionInfo info;
    getPlayHead()->getCurrentPosition(info);
    
    if (!info.isPlaying)
    {
        leftLevel.setTargetValue(-60.0);
        rightLevel.setTargetValue(-60.0);
    }
}

double MeterDemoAudioProcessor::getLeftLevel()
{
    return leftLevel.getNextValue();
}

double MeterDemoAudioProcessor::getRightLevel()
{
    return rightLevel.getNextValue();
}

void MeterDemoAudioProcessor::setMeterType(bool newstate)
{
    isRMS = newstate;
}

void MeterDemoAudioProcessor::setLevelForMeter(juce::AudioBuffer<float> &theBuffer)
{
    if (isRMS)
    {
        leftDB = juce::Decibels::gainToDecibels(theBuffer.getRMSLevel(0, 0, theBuffer.getNumSamples()));
        rightDB = juce::Decibels::gainToDecibels(theBuffer.getRMSLevel(1, 0, theBuffer.getNumSamples()));
    }
    
    else
    {
        leftDB = juce::Decibels::gainToDecibels(theBuffer.getMagnitude(0, 0, theBuffer.getNumSamples()));
        rightDB = juce::Decibels::gainToDecibels(theBuffer.getMagnitude(1, 0, theBuffer.getNumSamples()));
    }
}

void MeterDemoAudioProcessor::levelSmoothLogic()
{
    if (leftDB < leftLevel.getCurrentValue())
    {
        leftLevel.setTargetValue(leftDB);
    }

    else
    {
        leftLevel.setCurrentAndTargetValue(leftDB);
    }

    if (rightDB < rightLevel.getCurrentValue())
    {
        rightLevel.setTargetValue(rightDB);
    }

    else
    {
        rightLevel.setCurrentAndTargetValue(rightDB);
    }
}

//==============================================================================
bool MeterDemoAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

juce::AudioProcessorEditor* MeterDemoAudioProcessor::createEditor()
{
    return new MeterDemoAudioProcessorEditor (*this);
}

//==============================================================================
void MeterDemoAudioProcessor::getStateInformation (juce::MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
}

void MeterDemoAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
}

//==============================================================================
// This creates new instances of the plugin..
juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new MeterDemoAudioProcessor();
}
