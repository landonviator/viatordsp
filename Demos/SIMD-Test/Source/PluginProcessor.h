/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

//==============================================================================
/**
*/
class SIMDTestAudioProcessor  : public juce::AudioProcessor, public juce::AudioProcessorValueTreeState::Listener
{
public:
    //==============================================================================
    SIMDTestAudioProcessor();
    ~SIMDTestAudioProcessor() override;

    //==============================================================================
    void prepareToPlay (double sampleRate, int samplesPerBlock) override;
    void releaseResources() override;

   #ifndef JucePlugin_PreferredChannelConfigurations
    bool isBusesLayoutSupported (const BusesLayout& layouts) const override;
   #endif

    void processBlock (juce::AudioBuffer<float>&, juce::MidiBuffer&) override;

    //==============================================================================
    juce::AudioProcessorEditor* createEditor() override;
    bool hasEditor() const override;

    //==============================================================================
    const juce::String getName() const override;

    bool acceptsMidi() const override;
    bool producesMidi() const override;
    bool isMidiEffect() const override;
    double getTailLengthSeconds() const override;

    //==============================================================================
    int getNumPrograms() override;
    int getCurrentProgram() override;
    void setCurrentProgram (int index) override;
    const juce::String getProgramName (int index) override;
    void changeProgramName (int index, const juce::String& newName) override;

    //==============================================================================
    void getStateInformation (juce::MemoryBlock& destData) override;
    void setStateInformation (const void* data, int sizeInBytes) override;
    
    juce::AudioProcessorValueTreeState treeState;

private:
    juce::AudioProcessorValueTreeState::ParameterLayout createParameterLayout();
    void parameterChanged (const juce::String& parameterID, float newValue) override;
    
    /** SIMD */
    juce::dsp::IIR::Coefficients<float>::Ptr iirCoefficients;
    std::array<std::unique_ptr<juce::dsp::IIR::Filter<juce::dsp::SIMDRegister<float>>>, 100> filters;
    
    juce::dsp::AudioBlock<juce::dsp::SIMDRegister<float>> interleaved;
    juce::dsp::AudioBlock<float> zero;
    juce::HeapBlock<char> interleavedBlockData, zeroData;
    
    void process (const juce::dsp::ProcessContextReplacing<float>& context);
    
    template <typename SampleType>
    auto prepareChannelPointers (const juce::dsp::AudioBlock<SampleType>& block);
    
    template <typename T>
    static T* toBasePointer (juce::dsp::SIMDRegister<T>* r) noexcept
    {
        return reinterpret_cast<T*> (r);
    }
    
    static const auto registerSize = juce::dsp::SIMDRegister<float>::size();
    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (SIMDTestAudioProcessor)
};
