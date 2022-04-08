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
class MeterDemoAudioProcessor  : public juce::AudioProcessor
{
public:
    //==============================================================================
    MeterDemoAudioProcessor();
    ~MeterDemoAudioProcessor() override;

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
    
    double getLeftLevel();
    double getRightLevel();
    void setMeterType(bool newstate);
    
    float sampleValue = 0.0;
    int timerCount = 0;

private:
    
    juce::SmoothedValue<double> leftLevel = -60.0;
    juce::SmoothedValue<double>  rightLevel = -60.0;
    double leftDB, rightDB;
    bool isRMS = false;
    
    void setLevelForMeter(juce::AudioBuffer<float> &theBuffer);
    void levelSmoothLogic();
    
    
    
    
    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MeterDemoAudioProcessor)
};
