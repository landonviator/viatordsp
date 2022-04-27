/*
  ==============================================================================

    Distortion.h
    Created: 26 Apr 2022 6:15:35pm
    Author:  Landon Viator

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>

class Distortion
{
  
public:
    
    Distortion();
    
    void prepare(juce::dsp::ProcessSpec& spec);
    
    void reset();
    
    void processBlock(juce::dsp::AudioBlock<float>& block);
    
    float processSample(float input);
    
    void setDrive(float newDrive);
    
private:
    
    juce::SmoothedValue<float> mDrive;
    float mSampleRate;
    
    static constexpr float piDivisor = 2.0 / juce::MathConstants<float>::pi;
    
};
