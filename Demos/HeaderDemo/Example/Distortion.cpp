#include "Distortion.h"

template <typename SampleType>
Distortion<SampleType>::Distortion() : mDrive(1.0), mSampleRate(44100.0f)
{
}

template <typename SampleType>
void Distortion<SampleType>::prepare(juce::dsp::ProcessSpec &spec)
{
    mSampleRate = spec.sampleRate;
    reset();
}

template <typename SampleType>
void Distortion<SampleType>::reset()
{
    if (mSampleRate > 0)
    {
        mDrive.reset(mSampleRate, 0.02);
    }
}

template <typename SampleType>
void Distortion<SampleType>::setDrive(SampleType newDrive)
{
    mDrive.setTargetValue(juce::Decibels::decibelsToGain(newDrive));
}

template class Distortion<float>;
template class Distortion<double>;