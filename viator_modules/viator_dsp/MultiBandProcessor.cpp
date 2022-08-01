#include "MultiBandProcessor.h"

template <typename SampleType>
viator_dsp::MultiBandProcessor<SampleType>::MultiBandProcessor()
{
}

template <typename SampleType>
void viator_dsp::MultiBandProcessor<SampleType>::prepare(const juce::dsp::ProcessSpec& spec) noexcept
{
    _currentSampleRate = spec.sampleRate;
    
    _lowBandsFilter.prepare(spec);
    _lowBandsFilter.setCutoffFrequency(100.0);
    
    _midBandsFilter.prepare(spec);
    _midBandsFilter.setCutoffFrequency(500.0);
    
    _highBandsFilter.prepare(spec);
    _highBandsFilter.setCutoffFrequency(5000.0);
    
    reset();
}

template <typename SampleType>
void viator_dsp::MultiBandProcessor<SampleType>::reset() noexcept
{
    if (_currentSampleRate > 0)
    {
        _cutoff1.reset(_currentSampleRate, 0.02);
        _cutoff1.setTargetValue(100.0);
        _cutoff2.reset(_currentSampleRate, 0.02);
        _cutoff2.setTargetValue(500.0);
        _cutoff3.reset(_currentSampleRate, 0.02);
        _cutoff3.setTargetValue(5000.0);
    }
}

template <typename SampleType>
void viator_dsp::MultiBandProcessor<SampleType>::toggleBand1(bool bandOn)
{
    _band1 = bandOn;
}

template <typename SampleType>
void viator_dsp::MultiBandProcessor<SampleType>::toggleBand2(bool bandOn)
{
    _band2 = bandOn;
}

template <typename SampleType>
void viator_dsp::MultiBandProcessor<SampleType>::toggleBand3(bool bandOn)
{
    _band3 = bandOn;
}

template <typename SampleType>
void viator_dsp::MultiBandProcessor<SampleType>::toggleBand4(bool bandOn)
{
    _band4 = bandOn;
}

template <typename SampleType>
void viator_dsp::MultiBandProcessor<SampleType>::setLowCutoff(SampleType newCutoff)
{
    _cutoff1.setTargetValue(newCutoff);
}

template <typename SampleType>
void viator_dsp::MultiBandProcessor<SampleType>::setMidCutoff(SampleType newCutoff)
{
    _cutoff2.setTargetValue(newCutoff);
}

template <typename SampleType>
void viator_dsp::MultiBandProcessor<SampleType>::setHighCutoff(SampleType newCutoff)
{
    _cutoff3.setTargetValue(newCutoff);
}

template class viator_dsp::MultiBandProcessor<float>;
template class viator_dsp::MultiBandProcessor<double>;
