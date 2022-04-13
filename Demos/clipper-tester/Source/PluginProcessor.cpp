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
    treeState.addParameterListener ("model", this);
    treeState.addParameterListener ("input", this);
    treeState.addParameterListener ("mix", this);
    treeState.addParameterListener ("filter type", this);
    treeState.addParameterListener ("filter gain", this);
    treeState.addParameterListener ("cutoff", this);
    treeState.addParameterListener ("q", this);
}

ClippertesterAudioProcessor::~ClippertesterAudioProcessor()
{
    treeState.removeParameterListener ("model", this);
    treeState.removeParameterListener ("input", this);
    treeState.removeParameterListener ("mix", this);
    treeState.removeParameterListener ("filter type", this);
    treeState.removeParameterListener ("filter gain", this);
    treeState.removeParameterListener ("cutoff", this);
    treeState.removeParameterListener ("q", this);
}

juce::AudioProcessorValueTreeState::ParameterLayout ClippertesterAudioProcessor::createParameterLayout()
{
  std::vector <std::unique_ptr<juce::RangedAudioParameter>> params;

  // Make sure to update the number of reservations after adding params
  params.reserve(7);
  juce::StringArray models = {"Hard Clip", "Saturation", "Tube", "Tape"};
  juce::StringArray filtertypes = {"LowPass", "LowShelf", "Notch", "HighPass", "HighShelf"};

  // Make sure to update the number of reservations after adding params
  auto pModelChoice = std::make_unique<juce::AudioParameterChoice>("model", "Model", models, 0);
  auto pODInput = std::make_unique<juce::AudioParameterFloat>("input", "Input", 0.0, 20.0, 0.0);
  auto pMix = std::make_unique<juce::AudioParameterFloat>("mix", "Mix", 0.0, 100.0, 0.0);
  auto pFilterChoice = std::make_unique<juce::AudioParameterChoice>("filter type", "Filter Type", filtertypes, 0);
  auto pFilterGain = std::make_unique<juce::AudioParameterFloat>("filter gain", "Filter Gain", -24.0, 24.0, 0.0);
  auto pCutoff = std::make_unique<juce::AudioParameterFloat>("cutoff", "Cutoff", juce::NormalisableRange<float>(20.0, 20000.0, 1.0, 0.2), 1000.0);
  auto pBandwidth = std::make_unique<juce::AudioParameterFloat>("q", "Q", 0.1, 0.9, 0.33);
    
  params.push_back(std::move(pModelChoice));
  params.push_back(std::move(pODInput));
  params.push_back(std::move(pMix));
  params.push_back(std::move(pFilterChoice));
  params.push_back(std::move(pFilterGain));
  params.push_back(std::move(pCutoff));
  params.push_back(std::move(pBandwidth));
    
  return { params.begin(), params.end() };
}

void ClippertesterAudioProcessor::parameterChanged(const juce::String &parameterID, float newValue)
{
    updateSaturationParameters();
    updateFilterParameters();
}

void ClippertesterAudioProcessor::updateFilterParameters()
{
    switch (static_cast<int>(treeState.getRawParameterValue("filter type")->load()))
    {
        case 0:
        {
            leftFilter.setParameter(viator_dsp::SVFilter<float>::ParameterId::kType, viator_dsp::SVFilter<float>::FilterType::kLowPass);
            rightFilter.setParameter(viator_dsp::SVFilter<float>::ParameterId::kType, viator_dsp::SVFilter<float>::FilterType::kLowPass); break;

        }
            
        case 1:
        {
            leftFilter.setParameter(viator_dsp::SVFilter<float>::ParameterId::kType, viator_dsp::SVFilter<float>::FilterType::kLowShelf);
            rightFilter.setParameter(viator_dsp::SVFilter<float>::ParameterId::kType, viator_dsp::SVFilter<float>::FilterType::kLowShelf); break;

        }
            
        case 2:
        {
            leftFilter.setParameter(viator_dsp::SVFilter<float>::ParameterId::kType, viator_dsp::SVFilter<float>::FilterType::kBandShelf);
            rightFilter.setParameter(viator_dsp::SVFilter<float>::ParameterId::kType, viator_dsp::SVFilter<float>::FilterType::kBandShelf); break;

        }
            
        case 3:
        {
            leftFilter.setParameter(viator_dsp::SVFilter<float>::ParameterId::kType, viator_dsp::SVFilter<float>::FilterType::kHighPass);
            rightFilter.setParameter(viator_dsp::SVFilter<float>::ParameterId::kType, viator_dsp::SVFilter<float>::FilterType::kHighPass); break;

        }
            
        case 4:
        {
            leftFilter.setParameter(viator_dsp::SVFilter<float>::ParameterId::kType, viator_dsp::SVFilter<float>::FilterType::kHighShelf);
            rightFilter.setParameter(viator_dsp::SVFilter<float>::ParameterId::kType, viator_dsp::SVFilter<float>::FilterType::kHighShelf); break;

        }
    }
    
    leftFilter.setParameter(viator_dsp::SVFilter<float>::ParameterId::kCutoff, treeState.getRawParameterValue("cutoff")->load());
    rightFilter.setParameter(viator_dsp::SVFilter<float>::ParameterId::kCutoff, treeState.getRawParameterValue("cutoff")->load());
    
    leftFilter.setParameter(viator_dsp::SVFilter<float>::ParameterId::kQ, treeState.getRawParameterValue("q")->load());
    rightFilter.setParameter(viator_dsp::SVFilter<float>::ParameterId::kQ, treeState.getRawParameterValue("q")->load());

    leftFilter.setParameter(viator_dsp::SVFilter<float>::ParameterId::kGain, treeState.getRawParameterValue("filter gain")->load());
    rightFilter.setParameter(viator_dsp::SVFilter<float>::ParameterId::kGain, treeState.getRawParameterValue("filter gain")->load());

}

void ClippertesterAudioProcessor::updateSaturationParameters()
{
    switch (static_cast<int>(treeState.getRawParameterValue("model")->load()))
    {
        case 0:
        {
            saturationModule.setDistortionType(viator_dsp::Saturation<float>::DistortionType::kHard);
            break;
        }
                
        case 1:
        {
            saturationModule.setDistortionType(viator_dsp::Saturation<float>::DistortionType::kSaturation);
            break;
        }
                
        case 2:
        {
            saturationModule.setDistortionType(viator_dsp::Saturation<float>::DistortionType::kTube);
            break;
        }
                
        case 3:
        {
            saturationModule.setDistortionType(viator_dsp::Saturation<float>::DistortionType::kTape);
            break;
        }
    }
    
    saturationModule.setParameter(viator_dsp::Saturation<float>::ParameterId::kPreamp, treeState.getRawParameterValue("input")->load());
    saturationModule.setParameter(viator_dsp::Saturation<float>::ParameterId::kMix, treeState.getRawParameterValue("mix")->load());
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
    
    saturationModule.prepare(spec);
    updateSaturationParameters();
    
    leftFilter.prepare(spec);
    rightFilter.prepare(spec);
    updateFilterParameters();
    
    leftLFO.prepare(spec);
    leftLFO.setWaveType(viator_dsp::LFOGenerator::WaveType::kSine);
    leftLFO.setParameter(viator_dsp::LFOGenerator::ParameterId::kFrequency, 2);
    
    rightLFO.prepare(spec);
    rightLFO.setWaveType(viator_dsp::LFOGenerator::WaveType::kSine);
    rightLFO.setParameter(viator_dsp::LFOGenerator::ParameterId::kFrequency, 2);
}

void ClippertesterAudioProcessor::releaseResources()
{
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

    playHead = this->getPlayHead();
    playHead->getCurrentPosition (currentPositionInfo);
    setBPM(currentPositionInfo.bpm);

    juce::dsp::AudioBlock<float> block (buffer);
    
    frequencyFromRhythm(Rhythm::kQuarter);
    
    if (currentPositionInfo.isPlaying)
    {
        for (int sample = 0; sample < block.getNumSamples(); ++sample)
        {
            auto leftGain = leftLFO.processSample(block.getSample(0, sample)) * 24.0f;
            auto rightGain = rightLFO.processSample(block.getSample(1, sample)) * 24.0f;
            
            leftFilter.setParameter(viator_dsp::SVFilter<float>::ParameterId::kGain, leftGain);
            block.setSample(0, sample, leftFilter.processSample(block.getSample(0, sample), 1));
            
            rightFilter.setParameter(viator_dsp::SVFilter<float>::ParameterId::kGain, rightGain);
            block.setSample(1, sample, rightFilter.processSample(block.getSample(1, sample), 1));
        }
    }
}

float ClippertesterAudioProcessor::getBPM()
{
    return m_BPM;
}

void ClippertesterAudioProcessor::setBPM(float newBPM)
{
    m_BPM = newBPM;
    DBG(m_BPM);
}

void ClippertesterAudioProcessor::frequencyFromRhythm(Rhythm newRhythm)
{
    switch (newRhythm)
    {
        case Rhythm::kQuarter:
        {
            leftLFO.setParameter(viator_dsp::LFOGenerator::ParameterId::kFrequency, m_BPM / 60.0);
            rightLFO.setParameter(viator_dsp::LFOGenerator::ParameterId::kFrequency, m_BPM / 60.0); break;
        }
            
        case Rhythm::kEighth:
        {
            leftLFO.setParameter(viator_dsp::LFOGenerator::ParameterId::kFrequency, m_BPM / 30.0);
            rightLFO.setParameter(viator_dsp::LFOGenerator::ParameterId::kFrequency, m_BPM / 30.0); break;
        }
            
        case Rhythm::kTriplet:
        {
            leftLFO.setParameter(viator_dsp::LFOGenerator::ParameterId::kFrequency, m_BPM / 30.0);
            rightLFO.setParameter(viator_dsp::LFOGenerator::ParameterId::kFrequency, m_BPM / 30.0); break;
        }
            
        case Rhythm::kSixteenth:
        {
            leftLFO.setParameter(viator_dsp::LFOGenerator::ParameterId::kFrequency, m_BPM / 15.0);
            rightLFO.setParameter(viator_dsp::LFOGenerator::ParameterId::kFrequency, m_BPM / 15.0); break;
        }
    }
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
    // Save params
    juce::MemoryOutputStream stream(destData, false);
    treeState.state.writeToStream (stream);
}

void ClippertesterAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // Recall params
        auto tree = juce::ValueTree::readFromData (data, size_t(sizeInBytes));
        
        if (tree.isValid())
        {
            treeState.state = tree;
            updateSaturationParameters();
            updateFilterParameters();
        }
}

//==============================================================================
// This creates new instances of the plugin..
juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new ClippertesterAudioProcessor();
}
