/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
SIMDTestAudioProcessor::SIMDTestAudioProcessor()
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
    treeState.addParameterListener("filter gain", this);
}

SIMDTestAudioProcessor::~SIMDTestAudioProcessor()
{
    treeState.removeParameterListener("filter gain", this);
}

juce::AudioProcessorValueTreeState::ParameterLayout SIMDTestAudioProcessor::createParameterLayout()
{
    std::vector <std::unique_ptr<juce::RangedAudioParameter>> params;
        
    auto pFilterGainParam = std::make_unique<juce::AudioParameterFloat>("filter gain", "Filter Gain", -12.0f, 12.0f, 0.0f);
    
    params.push_back(std::move(pFilterGainParam));
    
    return { params.begin(), params.end() };
    
}

void SIMDTestAudioProcessor::parameterChanged(const juce::String &parameterID, float newValue)
{
}

//==============================================================================
const juce::String SIMDTestAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool SIMDTestAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool SIMDTestAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool SIMDTestAudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double SIMDTestAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int SIMDTestAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int SIMDTestAudioProcessor::getCurrentProgram()
{
    return 0;
}

void SIMDTestAudioProcessor::setCurrentProgram (int index)
{
}

const juce::String SIMDTestAudioProcessor::getProgramName (int index)
{
    return {};
}

void SIMDTestAudioProcessor::changeProgramName (int index, const juce::String& newName)
{
}

//==============================================================================
void SIMDTestAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    // Initialize spec for dsp modules
    juce::dsp::ProcessSpec spec;
    spec.maximumBlockSize = samplesPerBlock;
    spec.sampleRate = sampleRate;
    spec.numChannels = getTotalNumOutputChannels();
    
    iirCoefficients = juce::dsp::IIR::Coefficients<float>::makeNotch(sampleRate, 1000.0f);
    
    for(auto& filter : filters)
    {
        filter.reset (new juce::dsp::IIR::Filter<juce::dsp::SIMDRegister<float>> (iirCoefficients));
    }
    
    interleaved = juce::dsp::AudioBlock<juce::dsp::SIMDRegister<float>> (interleavedBlockData, 1, spec.maximumBlockSize);
    zero        = juce::dsp::AudioBlock<float> (zeroData, juce::dsp::SIMDRegister<float>::size(), spec.maximumBlockSize); // [6]

    zero.clear();

    auto monoSpec = spec;
    monoSpec.numChannels = 1;
    
    for(auto& filter : filters)
    {
        filter->prepare (monoSpec);
    }
}

void SIMDTestAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool SIMDTestAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
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

void SIMDTestAudioProcessor::processBlock (juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiMessages)
{
    juce::ScopedNoDenormals noDenormals;
    
    juce::dsp::AudioBlock<float> audioBlock {buffer};
    
    process(juce::dsp::ProcessContextReplacing<float>(audioBlock));
}

template <typename SampleType>
auto SIMDTestAudioProcessor::prepareChannelPointers (const juce::dsp::AudioBlock<SampleType>& block)
{
    std::array<SampleType*, registerSize> result {};
    
    for (size_t ch = 0; ch < result.size(); ++ch)
        result[ch] = (ch < block.getNumChannels() ? block.getChannelPointer (ch) : zero.getChannelPointer (ch));
    
    return result;
}

void SIMDTestAudioProcessor::process(const juce::dsp::ProcessContextReplacing<float> &context)
{
    jassert (context.getInputBlock().getNumSamples()  == context.getOutputBlock().getNumSamples());
    jassert (context.getInputBlock().getNumChannels() == context.getOutputBlock().getNumChannels());
     
    const auto& input  = context.getInputBlock(); // [9]
    const auto numSamples = (int) input.getNumSamples();
     
    auto inChannels = prepareChannelPointers (input); // [10]
     
    using Format = juce::AudioData::Format<juce::AudioData::Float32, juce::AudioData::NativeEndian>;
     
    juce::AudioData::interleaveSamples (juce::AudioData::NonInterleavedSource<Format> { inChannels.data(),                                 registerSize, },
                                        juce::AudioData::InterleavedDest<Format>      { toBasePointer (interleaved.getChannelPointer (0)), registerSize },
                                          numSamples); // [11]
     
    for(auto& filter : filters)
    {
        filter->process (juce::dsp::ProcessContextReplacing<juce::dsp::SIMDRegister<float>> (interleaved)); // [12]
    }
     
    auto outChannels = prepareChannelPointers (context.getOutputBlock()); // [13]
     
    juce::AudioData::deinterleaveSamples (juce::AudioData::InterleavedSource<Format>  { toBasePointer (interleaved.getChannelPointer (0)), registerSize },
                                          juce::AudioData::NonInterleavedDest<Format> { outChannels.data(),                                registerSize },
                                            numSamples); // [14]
}


//==============================================================================
bool SIMDTestAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

juce::AudioProcessorEditor* SIMDTestAudioProcessor::createEditor()
{
    //return new SIMDTestAudioProcessorEditor (*this);
    return new juce::GenericAudioProcessorEditor (*this);
}

//==============================================================================
void SIMDTestAudioProcessor::getStateInformation (juce::MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
}

void SIMDTestAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
}

//==============================================================================
// This creates new instances of the plugin..
juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new SIMDTestAudioProcessor();
}
