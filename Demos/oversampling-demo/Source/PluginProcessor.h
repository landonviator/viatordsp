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
class OversamplingdemoAudioProcessor  : public juce::AudioProcessor, public juce::AudioProcessorValueTreeState::Listener
{
public:
    //==============================================================================
    OversamplingdemoAudioProcessor();
    ~OversamplingdemoAudioProcessor() override;

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
    
    bool osToggle {false};
    
    juce::dsp::Oversampling<float> oversamplingModule;
    
    // Distortion
    float dbInput {0.0};
    float rawInput {1.0};
    float bias {0.0};
    float cutoff {1000.0};
    
    enum class DisModels
    {
        kSoft,
        kHard,
        kTube,
        kHalfWave,
        kFullWave
    };
    
    DisModels disModel = DisModels::kSoft;
    
    float softClipData(float samples);
    float hardClipData(float samples);
    float halfWaveData(float samples);
    float fullWaveData(float samples);
    float cheapTubeData(float samples);
    
    static constexpr float piDivisor = 2.0 / juce::MathConstants<float>::pi;
    
    juce::dsp::LinkwitzRileyFilter<float> lowPassFilter;
    
    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (OversamplingdemoAudioProcessor)
};
