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
    treeState.addParameterListener ("model", this);
    treeState.addParameterListener ("input", this);
    treeState.addParameterListener ("bias", this);
    treeState.addParameterListener ("cutoff", this);
}

OversamplingdemoAudioProcessor::~OversamplingdemoAudioProcessor()
{
    treeState.removeParameterListener ("os", this);
    treeState.removeParameterListener ("model", this);
    treeState.removeParameterListener ("input", this);
    treeState.removeParameterListener ("bias", this);
    treeState.removeParameterListener ("cutoff", this);
}

juce::AudioProcessorValueTreeState::ParameterLayout OversamplingdemoAudioProcessor::createParameterLayout()
{
  std::vector <std::unique_ptr<juce::RangedAudioParameter>> params;
    
    juce::StringArray disModels = {"Soft", "Hard", "Tube", "Half-Wave", "Full-Wave"};

  // Make sure to update the number of reservations after adding params
  auto pOSToggle = std::make_unique<juce::AudioParameterBool>("os", "OS", false);
  auto pModels = std::make_unique<juce::AudioParameterChoice>("model", "Model", disModels, 0);
  auto pInput = std::make_unique<juce::AudioParameterFloat>("input", "Input", -24.0, 24.0, 0.0);
  auto pBias = std::make_unique<juce::AudioParameterFloat>("bias", "Bias", 0.0, 1.0, 0.0);
  auto pCutoff = std::make_unique<juce::AudioParameterFloat>("cutoff", "Cutoff", juce::NormalisableRange<float>(20.0, 20000.0, 1.0, 0.22), 1000.0);
  
  params.push_back(std::move(pOSToggle));
  params.push_back(std::move(pModels));
  params.push_back(std::move(pInput));
  params.push_back(std::move(pBias));
  params.push_back(std::move(pCutoff));

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
        if (disModel == DisModels::kTube)
        {
            dbInput = newValue * 0.4;
            rawInput = juce::Decibels::decibelsToGain(dbInput);
        }
        
        else
        {
            dbInput = newValue;
            rawInput = juce::Decibels::decibelsToGain(dbInput);
        }
    }
    
    if (parameterID == "bias")
    {
        bias = newValue;
    }
    
    if (parameterID == "model")
    {
        switch (static_cast<int>(newValue))
        {
            case 0: disModel = DisModels::kSoft; break;
            case 1: disModel = DisModels::kHard; break;
            case 2: disModel = DisModels::kTube; break;
            case 3: disModel = DisModels::kHalfWave; break;
            case 4: disModel = DisModels::kFullWave; break;
        }
    }
    
    if (parameterID == "cutoff")
    {
        cutoff = newValue;
        lowPassFilter.setCutoffFrequency(cutoff);
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
    
    lowPassFilter.prepare(spec);
    lowPassFilter.setType(juce::dsp::LinkwitzRileyFilterType::lowpass);
    lowPassFilter.setCutoffFrequency(treeState.getRawParameterValue("cutoff")->load());
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

                switch (disModel)
                {
                    case DisModels::kSoft: data[sample] = softClipData(data[sample]); break;
                    case DisModels::kHard: data[sample] = hardClipData(data[sample]); break;
                    case DisModels::kTube: data[sample] = cheapTubeData(data[sample]); break;
                    case DisModels::kHalfWave: data[sample] = halfWaveData(data[sample]); break;
                    case DisModels::kFullWave: data[sample] = fullWaveData(data[sample]); break;
                }
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
                
                switch (disModel)
                {
                    case DisModels::kSoft: data[sample] = softClipData(data[sample]); break;
                    case DisModels::kHard: data[sample] = hardClipData(data[sample]); break;
                    case DisModels::kTube: data[sample] = cheapTubeData(data[sample]); break;
                    case DisModels::kHalfWave: data[sample] = halfWaveData(data[sample]); break;
                    case DisModels::kFullWave: data[sample] = fullWaveData(data[sample]); break;
                }
            }
        }
        
        lowPassFilter.process(juce::dsp::ProcessContextReplacing<float>(block));
    }
}

float OversamplingdemoAudioProcessor::softClipData(float samples)
{
    samples *= rawInput;
    
    return piDivisor * std::atan(samples);
}

float OversamplingdemoAudioProcessor::hardClipData(float samples)
{
    samples *= rawInput;
    
    if (std::abs(samples) > 1.0)
    {
        samples *= 1.0 / std::abs(samples);
    }
    
    return samples;
}

float OversamplingdemoAudioProcessor::cheapTubeData(float samples)
{
    samples *= rawInput;
    samples += 0.1;
    
    if (samples < 0.0)
    {
        samples = softClipData(samples);
    }
    
    else
    {
        samples = hardClipData(samples);
    }
    
    samples -= 0.1;
    
    return softClipData(samples);
}

float OversamplingdemoAudioProcessor::halfWaveData(float samples)
{
    samples *= rawInput;
    samples += 0.15;
    
    if (samples < 0.0)
    {
        samples = 0.0;
    }
    
    samples -= 0.15;
    
    return softClipData(samples);
}

float OversamplingdemoAudioProcessor::fullWaveData(float samples)
{
    samples *= rawInput;
    samples += 0.1;
    
    if (samples < 0.0)
    {
        samples *= -1.0;
    }
    
    samples -= 0.1;
    
    return softClipData(samples);
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
