/*
  ==============================================================================

    SoftClipper.cpp
    Created: 28 Apr 2022 6:08:38pm
    Author:  Landon Viator

  ==============================================================================
*/

#include "SoftClipper.h"

template <typename SampleType>
SoftClipper<SampleType>::SoftClipper() : mSampleRate(44100.0f), mDrive(1.0)
{
    
}

template <typename SampleType>
void SoftClipper<SampleType>::prepare(juce::dsp::ProcessSpec &spec) noexcept
{
    mSampleRate = spec.sampleRate;
    reset();
}

template <typename SampleType>
void SoftClipper<SampleType>::reset() noexcept
{
    if (mSampleRate > 0)
    {
        mDrive.reset(mSampleRate, 0.02);
    }
}

template <typename SampleType>
void SoftClipper<SampleType>::setDrive(SampleType newDrive)
{
    mDrive.setTargetValue(juce::Decibels::decibelsToGain(newDrive));
}

template class SoftClipper<float>;
template class SoftClipper<double>;
