#include "BitCrusher.h"

template <typename SampleType>
viator_dsp::BitCrusher<SampleType>::BitCrusher()
{
    _bitRateRange = juce::NormalisableRange<float>(1.0f, 450.0f, 0.1f, 0.2f);
    _resample.setTargetValue(_bitRateRange.convertFrom0to1(25.0f / 100.0f));
}

template <typename SampleType>
void viator_dsp::BitCrusher<SampleType>::prepare(const juce::dsp::ProcessSpec& spec) noexcept
{
    _currentSampleRate = spec.sampleRate;
    
    
    reset();
}

template <typename SampleType>
void viator_dsp::BitCrusher<SampleType>::reset() noexcept
{
    if (_currentSampleRate > 0)
    {
        _drive.reset(_currentSampleRate, 0.02);
        _drive.setTargetValue(1.0);
        _resample.reset(_currentSampleRate, 0.02);
        _resample.setTargetValue(44100.0);
        _mix.reset(_currentSampleRate, 0.02);
        _mix.setTargetValue(1.0);
        _output.reset(_currentSampleRate, 0.02);
        _output.setTargetValue(1.0);
    }
}

template <typename SampleType>
void viator_dsp::BitCrusher<SampleType>::setBitDepth(SampleType newBitDepth)
{
    auto reversed = juce::jmap(static_cast<float>(newBitDepth), 1.0f, 16.0f, 16.0f, 3.0f);
    auto quantizedBD = 2.0 / (std::pow(2.0, reversed) - 1.0);
    _bitDepth = quantizedBD;
}

template <typename SampleType>
void viator_dsp::BitCrusher<SampleType>::setResampleRate(SampleType newResampleRate)
{
    // Reverse range to make more sense to the user.
    DBG(_resample.getNextValue());
    auto tempValue = juce::jmap<float>(newResampleRate, 0.0f, _currentSampleRate, 51.0f, 0.0f);
    _rateDivide = _bitRateRange.convertFrom0to1(tempValue / 100.0f);
}

template <typename SampleType>
void viator_dsp::BitCrusher<SampleType>::setMix(SampleType newMix)
{
    _mix.setTargetValue(newMix * 0.01);
}

template <typename SampleType>
void viator_dsp::BitCrusher<SampleType>::setDrive(SampleType newDrive)
{
    _drive.setTargetValue(juce::Decibels::decibelsToGain(newDrive));
}

template <typename SampleType>
void viator_dsp::BitCrusher<SampleType>::setVolume(SampleType newVolume)
{
    _output.setTargetValue(juce::Decibels::decibelsToGain(newVolume));
}

template <typename SampleType>
void viator_dsp::BitCrusher<SampleType>::setResampledRate(SampleType newResampleRate)
{
    _resample.setTargetValue(newResampleRate);
}

template class viator_dsp::BitCrusher<float>;
template class viator_dsp::BitCrusher<double>;
