/*
  ==============================================================================

    Distortion.cpp
    Created: 26 Apr 2022 6:15:46pm
    Author:  Landon Viator

  ==============================================================================
*/

#include "Distortion.h"

Distortion::Distortion() : mDrive(1.0), mSampleRate(44100.0f)
{
    
}

void Distortion::prepare(juce::dsp::ProcessSpec &spec)
{
    mSampleRate = spec.sampleRate;
    reset();
}

void Distortion::reset()
{
    if (mSampleRate > 0)
    {
        mDrive.reset(mSampleRate, 0.02);
    }
}

void Distortion::processBlock(juce::dsp::AudioBlock<float> &block)
{
    for (int ch = 0; ch < block.getNumChannels(); ++ch)
    {
        float* data = block.getChannelPointer(ch);
                
        for (int sample = 0; sample < block.getNumSamples(); ++sample)
        {
            data[sample] = processSample(data[sample]);
        }
    }
}

float Distortion::processSample(float input)
{
    return piDivisor * std::atan(input * mDrive.getNextValue());
}

void Distortion::setDrive(float newDrive)
{
    mDrive.setTargetValue(juce::Decibels::decibelsToGain(newDrive));
}
