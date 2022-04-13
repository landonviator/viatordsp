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
class ClippertesterAudioProcessor  : public juce::AudioProcessor
, public juce::AudioProcessorValueTreeState::Listener
{
public:
    //==============================================================================
    ClippertesterAudioProcessor();
    ~ClippertesterAudioProcessor() override;

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
    
    /** Value Trees =====================================================*/
    juce::AudioProcessorValueTreeState treeState;
    
    float getBPM();

private:
    
    viator_dsp::Saturation<float> saturationModule;
    void updateSaturationParameters();
    float inputGainDB {0.0};
    
    viator_dsp::SVFilter<float> leftFilter;
    viator_dsp::SVFilter<float> rightFilter;
    void updateFilterParameters();
    
    viator_dsp::LFOGenerator leftLFO;
    viator_dsp::LFOGenerator rightLFO;
    
    /** Playhead position info */
    juce::AudioPlayHead* playHead;
    juce::AudioPlayHead::CurrentPositionInfo currentPositionInfo;
    float m_BPM = 0.0f;
    void setBPM(float newBPM);
    
    enum class Rhythm
    {
        kQuarter,
        kEighth,
        kTriplet,
        kSixteenth
    };
    
    void frequencyFromRhythm(Rhythm newRhythm);
    
    Rhythm rhythm = Rhythm::kQuarter;
    
    /** Parameters ======================================================*/
    juce::AudioProcessorValueTreeState::ParameterLayout createParameterLayout();
    void parameterChanged (const juce::String& parameterID, float newValue) override;
    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (ClippertesterAudioProcessor)
};
