/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
ClippertesterAudioProcessor::ClippertesterAudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
     : AudioProcessor (BusesProperties()
                     #if ! JucePlugin_IsMidiEffect
                      #if ! JucePlugin_IsSynth
                       .withInput  ("Input",  juce::AudioChannelSet::stereo(), true)
                      #endif
                       .withOutput ("Output", juce::AudioChannelSet::stereo(), true)
                     #endif
                       ),
treeState(*this, nullptr, "PARAMETER", createParameterLayout())
#endif
{
    treeState.addParameterListener ("od input", this);
    treeState.addParameterListener ("clip type", this);
}

ClippertesterAudioProcessor::~ClippertesterAudioProcessor()
{
    treeState.removeParameterListener ("od input", this);
    treeState.removeParameterListener ("clip type", this);
}

juce::AudioProcessorValueTreeState::ParameterLayout ClippertesterAudioProcessor::createParameterLayout()
{
  std::vector <std::unique_ptr<juce::RangedAudioParameter>> params;

  // Make sure to update the number of reservations after adding params
  params.reserve(1);
  juce::StringArray cliptypes = {"Hard", "Soft", "Diode"};
    
  auto pODInput = std::make_unique<juce::AudioParameterFloat>("od input", "OD Input", 0.0, 20.0, 0.0);
  auto pClipChoice = std::make_unique<juce::AudioParameterChoice>("clip type", "Clip Type", cliptypes, 0);
    
  params.push_back(std::move(pODInput));
  params.push_back(std::move(pClipChoice));
    
  return { params.begin(), params.end() };
}

void ClippertesterAudioProcessor::parameterChanged(const juce::String &parameterID, float newValue)
{
    if (parameterID == "od input")
    {
        clipper.setParameter(viator_dsp::Clipper<float>::ParameterId::kPreamp, newValue);
    }
    
    if (parameterID == "clip type")
    {
        switch (static_cast<int>(newValue))
        {
            case 0: clipper.setClipperType(viator_dsp::Clipper<float>::ClipType::kHard); break;
            case 1: clipper.setClipperType(viator_dsp::Clipper<float>::ClipType::kSoft); break;
            case 2: clipper.setClipperType(viator_dsp::Clipper<float>::ClipType::kDiode); break;
        }
        
    }
}

//==============================================================================
const juce::String ClippertesterAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool ClippertesterAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool ClippertesterAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool ClippertesterAudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double ClippertesterAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int ClippertesterAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int ClippertesterAudioProcessor::getCurrentProgram()
{
    return 0;
}

void ClippertesterAudioProcessor::setCurrentProgram (int index)
{
}

const juce::String ClippertesterAudioProcessor::getProgramName (int index)
{
    return {};
}

void ClippertesterAudioProcessor::changeProgramName (int index, const juce::String& newName)
{
}

//==============================================================================
void ClippertesterAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    juce::dsp::ProcessSpec spec;
    spec.sampleRate = sampleRate;
    spec.maximumBlockSize = samplesPerBlock;
    spec.numChannels = getTotalNumInputChannels();
    
    clipper.prepare(spec);
    clipper.setClipperType(viator_dsp::Clipper<float>::ClipType::kHard);
    clipper.setParameter(viator_dsp::Clipper<float>::ParameterId::kPreamp, static_cast<float>(*treeState.getRawParameterValue("od input")));
}

void ClippertesterAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool ClippertesterAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
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

void ClippertesterAudioProcessor::processBlock (juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiMessages)
{
    juce::ScopedNoDenormals noDenormals;
    auto totalNumInputChannels  = getTotalNumInputChannels();
    auto totalNumOutputChannels = getTotalNumOutputChannels();

    for (auto i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
        buffer.clear (i, 0, buffer.getNumSamples());

    juce::dsp::AudioBlock<float> block (buffer);
    clipper.process(juce::dsp::ProcessContextReplacing<float>(block));

}

//==============================================================================
bool ClippertesterAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

juce::AudioProcessorEditor* ClippertesterAudioProcessor::createEditor()
{
    //return new ClippertesterAudioProcessorEditor (*this);
    return new juce::GenericAudioProcessorEditor (*this);
}

//==============================================================================
void ClippertesterAudioProcessor::getStateInformation (juce::MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
}

void ClippertesterAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
}

//==============================================================================
// This creates new instances of the plugin..
juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new ClippertesterAudioProcessor();
}
