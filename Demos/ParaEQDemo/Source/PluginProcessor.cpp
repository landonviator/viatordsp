/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
ParaEQDemoAudioProcessor::ParaEQDemoAudioProcessor()
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
forwardFFT (fftOrder),
window (fftSize, juce::dsp::WindowingFunction<float>::hann, true)
#endif
{
    /** Band 1*/
    treeState.addParameterListener("band1Gain", this);
    treeState.addParameterListener("band1Cutoff", this);
    treeState.addParameterListener("band1Q", this);
    
    /** Band 2*/
    treeState.addParameterListener("band2Gain", this);
    treeState.addParameterListener("band2Cutoff", this);
    treeState.addParameterListener("band2Q", this);
    
    /** Band 3*/
    treeState.addParameterListener("band3Gain", this);
    treeState.addParameterListener("band3Cutoff", this);
    treeState.addParameterListener("band3Q", this);
    
    /** Band 4*/
    treeState.addParameterListener("band4Gain", this);
    treeState.addParameterListener("band4Cutoff", this);
    treeState.addParameterListener("band4Q", this);
    
    /** Band 5*/
    treeState.addParameterListener("band5Gain", this);
    treeState.addParameterListener("band5Cutoff", this);
    treeState.addParameterListener("band5Q", this);
    
    /** Band 6*/
    treeState.addParameterListener("band6Gain", this);
    treeState.addParameterListener("band6Cutoff", this);
    treeState.addParameterListener("band6Q", this);
    
    /** Band 7*/
    treeState.addParameterListener("band7Gain", this);
    treeState.addParameterListener("band7Cutoff", this);
    treeState.addParameterListener("band7Q", this);
}

ParaEQDemoAudioProcessor::~ParaEQDemoAudioProcessor()
{
    /** Band 1 */
    treeState.removeParameterListener("band1Gain", this);
    treeState.removeParameterListener("band1Cutoff", this);
    treeState.removeParameterListener("band1Q", this);
    
    /** Band 2 */
    treeState.removeParameterListener("band2Gain", this);
    treeState.removeParameterListener("band2Cutoff", this);
    treeState.removeParameterListener("band2Q", this);
    
    /** Band 3 */
    treeState.removeParameterListener("band3Gain", this);
    treeState.removeParameterListener("band3Cutoff", this);
    treeState.removeParameterListener("band3Q", this);
    
    /** Band 4 */
    treeState.removeParameterListener("band4Gain", this);
    treeState.removeParameterListener("band4Cutoff", this);
    treeState.removeParameterListener("band4Q", this);
    
    /** Band 5 */
    treeState.removeParameterListener("band5Gain", this);
    treeState.removeParameterListener("band5Cutoff", this);
    treeState.removeParameterListener("band5Q", this);
    
    /** Band 6 */
    treeState.removeParameterListener("band6Gain", this);
    treeState.removeParameterListener("band6Cutoff", this);
    treeState.removeParameterListener("band6Q", this);
    
    /** Band 7 */
    treeState.removeParameterListener("band7Gain", this);
    treeState.removeParameterListener("band7Cutoff", this);
    treeState.removeParameterListener("band7Q", this);
}

juce::AudioProcessorValueTreeState::ParameterLayout ParaEQDemoAudioProcessor::createParameterLayout()
{
    std::vector <std::unique_ptr<juce::RangedAudioParameter>> params;
        
    /** Band 1 */
    auto pBand1Gain = std::make_unique<juce::AudioParameterFloat>("band1Gain", "Band1Gain", -15.0f, 15.0f, 0.0f);
    auto pBand1Cutoff = std::make_unique<juce::AudioParameterFloat>("band1Cutoff", "Band1Cutoff", 20.0f, 250.0f, 100.0f);
    auto pBand1Q = std::make_unique<juce::AudioParameterFloat>("band1Q", "Band1Q", 0.36f, 0.8f, 0.5f);
    
    /** Band 2 */
    auto pBand2Gain = std::make_unique<juce::AudioParameterFloat>("band2Gain", "Band2Gain", -15.0f, 15.0f, 0.0f);
    auto pBand2Cutoff = std::make_unique<juce::AudioParameterFloat>("band2Cutoff", "Band2Cutoff", juce::NormalisableRange<float>(20.0f, 20000.0f, 1.0f, 0.2f), 250.0f);
    auto pBand2Q = std::make_unique<juce::AudioParameterFloat>("band2Q", "Band2Q", juce::NormalisableRange<float>(0.15f, 10.0f, 0.01f, 0.25f), 0.5f);
    
    /** Band 3 */
    auto pBand3Gain = std::make_unique<juce::AudioParameterFloat>("band3Gain", "Band3Gain", -15.0f, 15.0f, 0.0f);
    auto pBand3Cutoff = std::make_unique<juce::AudioParameterFloat>("band3Cutoff", "Band3Cutoff", juce::NormalisableRange<float>(20.0f, 20000.0f, 1.0f, 0.2f), 500.0f);
    auto pBand3Q = std::make_unique<juce::AudioParameterFloat>("band3Q", "Band3Q", juce::NormalisableRange<float>(0.15f, 10.0f, 0.01f, 0.25f), 0.5f);
    
    /** Band 4 */
    auto pBand4Gain = std::make_unique<juce::AudioParameterFloat>("band4Gain", "Band4Gain", -15.0f, 15.0f, 0.0f);
    auto pBand4Cutoff = std::make_unique<juce::AudioParameterFloat>("band4Cutoff", "Band4Cutoff", juce::NormalisableRange<float>(20.0f, 20000.0f, 1.0f, 0.2f), 1000.0f);
    auto pBand4Q = std::make_unique<juce::AudioParameterFloat>("band4Q", "Band4Q", juce::NormalisableRange<float>(0.15f, 10.0f, 0.01f, 0.25f), 0.5f);
    
    /** Band 5 */
    auto pBand5Gain = std::make_unique<juce::AudioParameterFloat>("band5Gain", "Band5Gain", -15.0f, 15.0f, 0.0f);
    auto pBand5Cutoff = std::make_unique<juce::AudioParameterFloat>("band5Cutoff", "Band5Cutoff", juce::NormalisableRange<float>(20.0f, 20000.0f, 1.0f, 0.2f), 4000.0f);
    auto pBand5Q = std::make_unique<juce::AudioParameterFloat>("band5Q", "Band5Q", juce::NormalisableRange<float>(0.15f, 10.0f, 0.01f, 0.25f), 0.5f);
    
    /** Band 6 */
    auto pBand6Gain = std::make_unique<juce::AudioParameterFloat>("band6Gain", "Band6Gain", -15.0f, 15.0f, 0.0f);
    auto pBand6Cutoff = std::make_unique<juce::AudioParameterFloat>("band6Cutoff", "Band6Cutoff", juce::NormalisableRange<float>(20.0f, 20000.0f, 1.0f, 0.2f), 8000.0f);
    auto pBand6Q = std::make_unique<juce::AudioParameterFloat>("band6Q", "Band6Q", juce::NormalisableRange<float>(0.15f, 10.0f, 0.01f, 0.25f), 0.5f);
    
    /** Band 7 */
    auto pBand7Gain = std::make_unique<juce::AudioParameterFloat>("band7Gain", "Band7Gain", -15.0f, 15.0f, 0.0f);
    auto pBand7Cutoff = std::make_unique<juce::AudioParameterFloat>("band7Cutoff", "Band7Cutoff", 5000.0f, 20000.0f, 5000.0f);
    auto pBand7Q = std::make_unique<juce::AudioParameterFloat>("band7Q", "Band7Q", 0.36f, 0.8f, 0.5f);
    
    /** Band 1 */
    params.push_back(std::move(pBand1Gain));
    params.push_back(std::move(pBand1Cutoff));
    params.push_back(std::move(pBand1Q));
    
    /** Band 2 */
    params.push_back(std::move(pBand2Gain));
    params.push_back(std::move(pBand2Cutoff));
    params.push_back(std::move(pBand2Q));
    
    /** Band 3 */
    params.push_back(std::move(pBand3Gain));
    params.push_back(std::move(pBand3Cutoff));
    params.push_back(std::move(pBand3Q));
    
    /** Band 4 */
    params.push_back(std::move(pBand4Gain));
    params.push_back(std::move(pBand4Cutoff));
    params.push_back(std::move(pBand4Q));
    
    /** Band 5 */
    params.push_back(std::move(pBand5Gain));
    params.push_back(std::move(pBand5Cutoff));
    params.push_back(std::move(pBand5Q));
    
    /** Band 6 */
    params.push_back(std::move(pBand6Gain));
    params.push_back(std::move(pBand6Cutoff));
    params.push_back(std::move(pBand6Q));
    
    /** Band 7 */
    params.push_back(std::move(pBand7Gain));
    params.push_back(std::move(pBand7Cutoff));
    params.push_back(std::move(pBand7Q));
    
    return { params.begin(), params.end() };
    
}

void ParaEQDemoAudioProcessor::parameterChanged(const juce::String &parameterID, float newValue)
{
    updateParameters();
}

void ParaEQDemoAudioProcessor::updateParameters()
{
    updateBand1(treeState.getRawParameterValue("band1Gain")->load(), treeState.getRawParameterValue("band1Cutoff")->load(), treeState.getRawParameterValue("band1Q")->load());
    updateBand2(treeState.getRawParameterValue("band2Gain")->load(), treeState.getRawParameterValue("band2Cutoff")->load(), treeState.getRawParameterValue("band2Q")->load());
    updateBand3(treeState.getRawParameterValue("band3Gain")->load(), treeState.getRawParameterValue("band3Cutoff")->load(), treeState.getRawParameterValue("band3Q")->load());
    updateBand4(treeState.getRawParameterValue("band4Gain")->load(), treeState.getRawParameterValue("band4Cutoff")->load(), treeState.getRawParameterValue("band4Q")->load());
    updateBand5(treeState.getRawParameterValue("band5Gain")->load(), treeState.getRawParameterValue("band5Cutoff")->load(), treeState.getRawParameterValue("band5Q")->load());
    updateBand6(treeState.getRawParameterValue("band6Gain")->load(), treeState.getRawParameterValue("band6Cutoff")->load(), treeState.getRawParameterValue("band6Q")->load());
    updateBand7(treeState.getRawParameterValue("band7Gain")->load(), treeState.getRawParameterValue("band7Cutoff")->load(), treeState.getRawParameterValue("band7Q")->load());
}

//==============================================================================
const juce::String ParaEQDemoAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool ParaEQDemoAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool ParaEQDemoAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool ParaEQDemoAudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double ParaEQDemoAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int ParaEQDemoAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int ParaEQDemoAudioProcessor::getCurrentProgram()
{
    return 0;
}

void ParaEQDemoAudioProcessor::setCurrentProgram (int index)
{
}

const juce::String ParaEQDemoAudioProcessor::getProgramName (int index)
{
    return {};
}

void ParaEQDemoAudioProcessor::changeProgramName (int index, const juce::String& newName)
{
}

//==============================================================================
void ParaEQDemoAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    // Initialize spec for dsp modules
    juce::dsp::ProcessSpec spec;
    spec.maximumBlockSize = samplesPerBlock;
    spec.sampleRate = sampleRate;
    spec.numChannels = getTotalNumOutputChannels();
    
    /** Prepare */
    band1.prepare(spec);
    band2.prepare(spec);
    band3.prepare(spec);
    band4.prepare(spec);
    band5.prepare(spec);
    band6.prepare(spec);
    band7.prepare(spec);
    updateParameters();
}

void ParaEQDemoAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool ParaEQDemoAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
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

void ParaEQDemoAudioProcessor::processBlock (juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiMessages)
{
    juce::ScopedNoDenormals noDenormals;
    auto totalNumInputChannels  = getTotalNumInputChannels();
    auto totalNumOutputChannels = getTotalNumOutputChannels();

    juce::dsp::AudioBlock<float> audioBlock {buffer};
    band1.process(juce::dsp::ProcessContextReplacing<float>(audioBlock));
    band2.process(juce::dsp::ProcessContextReplacing<float>(audioBlock));
    band3.process(juce::dsp::ProcessContextReplacing<float>(audioBlock));
    band4.process(juce::dsp::ProcessContextReplacing<float>(audioBlock));
    band5.process(juce::dsp::ProcessContextReplacing<float>(audioBlock));
    band6.process(juce::dsp::ProcessContextReplacing<float>(audioBlock));
    band7.process(juce::dsp::ProcessContextReplacing<float>(audioBlock));
    
    if (buffer.getNumChannels() > 0)
    {
        auto* channelData = buffer.getWritePointer(0);
     
        for (auto i = 0; i < buffer.getNumSamples(); ++i)
        {
            pushNextSampleIntoFifo (channelData[i]);
        }
    }
}

void ParaEQDemoAudioProcessor::updateBand1(float gain, float cutoff, float q)
{
    *band1.state = *juce::dsp::IIR::Coefficients<float>::makeLowShelf(getSampleRate(), cutoff, q, juce::Decibels::decibelsToGain(gain));
}

void ParaEQDemoAudioProcessor::updateBand2(float gain, float cutoff, float q)
{
    *band2.state = *juce::dsp::IIR::Coefficients<float>::makePeakFilter(getSampleRate(), cutoff, q, juce::Decibels::decibelsToGain(gain));
}

void ParaEQDemoAudioProcessor::updateBand3(float gain, float cutoff, float q)
{
    *band3.state = *juce::dsp::IIR::Coefficients<float>::makePeakFilter(getSampleRate(), cutoff, q, juce::Decibels::decibelsToGain(gain));
}

void ParaEQDemoAudioProcessor::updateBand4(float gain, float cutoff, float q)
{
    *band4.state = *juce::dsp::IIR::Coefficients<float>::makePeakFilter(getSampleRate(), cutoff, q, juce::Decibels::decibelsToGain(gain));
}

void ParaEQDemoAudioProcessor::updateBand5(float gain, float cutoff, float q)
{
    *band5.state = *juce::dsp::IIR::Coefficients<float>::makePeakFilter(getSampleRate(), cutoff, q, juce::Decibels::decibelsToGain(gain));
}

void ParaEQDemoAudioProcessor::updateBand6(float gain, float cutoff, float q)
{
    *band6.state = *juce::dsp::IIR::Coefficients<float>::makePeakFilter(getSampleRate(), cutoff, q, juce::Decibels::decibelsToGain(gain));
}

void ParaEQDemoAudioProcessor::updateBand7(float gain, float cutoff, float q)
{
    *band7.state = *juce::dsp::IIR::Coefficients<float>::makeHighShelf(getSampleRate(), cutoff, q, juce::Decibels::decibelsToGain(gain));
}

void ParaEQDemoAudioProcessor::pushNextSampleIntoFifo (float sample) noexcept
{
    // if the fifo contains enough data, set a flag to say
    // that the next frame should now be rendered..
    if (fifoIndex == fftSize)               // [11]
    {
        if (! nextFFTBlockReady)            // [12]
        {
            juce::zeromem (fftData, sizeof (fftData));
            memcpy (fftData, fifo, sizeof (fifo));
            nextFFTBlockReady = true;
        }

        fifoIndex = 0;
    }

    fifo[fifoIndex++] = sample;             // [12]
}

void ParaEQDemoAudioProcessor::drawNextFrameOfSpectrum()
{
    // first apply a windowing function to our data
    window.multiplyWithWindowingTable (fftData, fftSize);       // [1]

    // then render our FFT data..
    forwardFFT.performFrequencyOnlyForwardTransform (fftData);  // [2]

    auto mindB = -100.0f;
    auto maxdB =    0.0f;

    for (int i = 0; i < scopeSize; ++i)                         // [3]
    {
        auto skewedProportionX = 0.99 - std::exp (std::log2 (1.0f - (float) i /
                                                             (float) scopeSize) * 0.15);
        auto fftDataIndex = juce::jlimit (0, fftSize / 2, (int) (skewedProportionX * (float) fftSize * 0.5));
        auto level = juce::jmap (juce::jlimit (mindB, maxdB, juce::Decibels::gainToDecibels (fftData[fftDataIndex])
                                                           - juce::Decibels::gainToDecibels ((float) fftSize)),
                                 mindB, maxdB, 0.0f, 1.0f);

        scopeData[i] = level;                                   // [4]
    }
}

//==============================================================================
bool ParaEQDemoAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

juce::AudioProcessorEditor* ParaEQDemoAudioProcessor::createEditor()
{
    return new ParaEQDemoAudioProcessorEditor (*this);
    //return new juce::GenericAudioProcessorEditor (*this);
}

//==============================================================================
void ParaEQDemoAudioProcessor::getStateInformation (juce::MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
}

void ParaEQDemoAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
}

//==============================================================================
// This creates new instances of the plugin..
juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new ParaEQDemoAudioProcessor();
}
