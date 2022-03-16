/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
OversamplingdemoAudioProcessor::OversamplingdemoAudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
     : AudioProcessor (BusesProperties()
                     #if ! JucePlugin_IsMidiEffect
                      #if ! JucePlugin_IsSynth
                       .withInput  ("Input",  juce::AudioChannelSet::stereo(), true)
                      #endif
                       .withOutput ("Output", juce::AudioChannelSet::stereo(), true)
                     #endif
                       ),
treeState(*this, nullptr, "PARAMETERS", createParameterLayout()),
oversamplingModule(2, 2, juce::dsp::Oversampling<float>::FilterType::filterHalfBandPolyphaseIIR)
#endif
{
    treeState.addParameterListener ("os", this);
    treeState.addParameterListener ("input", this);
}

OversamplingdemoAudioProcessor::~OversamplingdemoAudioProcessor()
{
    treeState.removeParameterListener ("os", this);
    treeState.removeParameterListener ("input", this);
}

juce::AudioProcessorValueTreeState::ParameterLayout OversamplingdemoAudioProcessor::createParameterLayout()
{
  std::vector <std::unique_ptr<juce::RangedAudioParameter>> params;

  // Make sure to update the number of reservations after adding params
  auto pOSToggle = std::make_unique<juce::AudioParameterBool>("os", "OS", false);
  auto pInput = std::make_unique<juce::AudioParameterFloat>("input", "Input", -24.0, 24.0, 0.0);
  
  params.push_back(std::move(pOSToggle));
  params.push_back(std::move(pInput));

  return { params.begin(), params.end() };
}

void OversamplingdemoAudioProcessor::parameterChanged(const juce::String &parameterID, float newValue)
{
    if (parameterID == "os")
    {
        osToggle = newValue;
    }
    
    if (parameterID == "input")
    {
        dbInput = newValue;
        rawInput = juce::Decibels::decibelsToGain(newValue);
    }
}

//==============================================================================
const juce::String OversamplingdemoAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool OversamplingdemoAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool OversamplingdemoAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool OversamplingdemoAudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double OversamplingdemoAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int OversamplingdemoAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int OversamplingdemoAudioProcessor::getCurrentProgram()
{
    return 0;
}

void OversamplingdemoAudioProcessor::setCurrentProgram (int index)
{
}

const juce::String OversamplingdemoAudioProcessor::getProgramName (int index)
{
    return {};
}

void OversamplingdemoAudioProcessor::changeProgramName (int index, const juce::String& newName)
{
}

//==============================================================================
void OversamplingdemoAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    juce::dsp::ProcessSpec spec;
    spec.sampleRate = sampleRate;
    spec.maximumBlockSize = samplesPerBlock;
    spec.numChannels = getTotalNumInputChannels();
    
    osToggle = treeState.getRawParameterValue("os")->load();
    oversamplingModule.initProcessing(samplesPerBlock);
}

void OversamplingdemoAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool OversamplingdemoAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
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

void OversamplingdemoAudioProcessor::processBlock (juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiMessages)
{
    juce::ScopedNoDenormals noDenormals;
    auto totalNumInputChannels  = getTotalNumInputChannels();
    auto totalNumOutputChannels = getTotalNumOutputChannels();

    for (auto i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
        buffer.clear (i, 0, buffer.getNumSamples());

    juce::dsp::AudioBlock<float> block (buffer);
    juce::dsp::AudioBlock<float> upSampledBlock (buffer);
    
    // If oversampling is on
    if (osToggle)
    {
        // Increase sampling rate
        upSampledBlock = oversamplingModule.processSamplesUp(block);
        
        // Soft clip distortion
        for (int sample = 0; sample < upSampledBlock.getNumSamples(); ++sample)
        {
            for (int ch = 0; ch < upSampledBlock.getNumChannels(); ++ch)
            {
                float* data = upSampledBlock.getChannelPointer(ch);

                data[sample] = softClipData(data[sample]);
            }
        }
        
        // Decrease sample rate
        oversamplingModule.processSamplesDown(block);
    }
    
    // If oversampling is off
    else
    {
        // Soft clip distortion
        for (int sample = 0; sample < block.getNumSamples(); ++sample)
        {
            for (int ch = 0; ch < block.getNumChannels(); ++ch)
            {
                float* data = block.getChannelPointer(ch);
                
                data[sample] = softClipData(data[sample]);
            }
        }
    }
}

float OversamplingdemoAudioProcessor::softClipData(float samples)
{
    return piDivisor * std::atan(samples * rawInput);
}

//==============================================================================
bool OversamplingdemoAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

juce::AudioProcessorEditor* OversamplingdemoAudioProcessor::createEditor()
{
    //return new OversamplingdemoAudioProcessorEditor (*this);
    return new juce::GenericAudioProcessorEditor (*this);
}

//==============================================================================
void OversamplingdemoAudioProcessor::getStateInformation (juce::MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
}

void OversamplingdemoAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
}

//==============================================================================
// This creates new instances of the plugin..
juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new OversamplingdemoAudioProcessor();
}
