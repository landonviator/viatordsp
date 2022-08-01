#include "BitCrusher.h"

template <typename SampleType>
viator_dsp::BitCrusher<SampleType>::BitCrusher()
{
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
        _mix.reset(_currentSampleRate, 0.02);
        _mix.setTargetValue(1.0);
        _output.reset(_currentSampleRate, 0.02);
        _output.setTargetValue(0.0);
    }
}

template class viator_dsp::BitCrusher<float>;
template class viator_dsp::BitCrusher<double>;
