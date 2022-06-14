#include "Distortion.h"

template <typename SampleType>
viator_dsp::Distortion<SampleType>::Distortion() :
_globalEnabled(true), _thresh(1.0f), m_clipType(viator_dsp::Distortion<SampleType>::ClipType::kHard)
{
}

template <typename SampleType>
void viator_dsp::Distortion<SampleType>::prepare(const juce::dsp::ProcessSpec& spec) noexcept
{
    _currentSampleRate = spec.sampleRate;
    reset();
}

template <typename SampleType>
void viator_dsp::Distortion<SampleType>::reset() noexcept
{
    if (_currentSampleRate > 0)
    {
        _rawGain.reset(_currentSampleRate, 0.02);
        _rawGain.setTargetValue(1.0);
        _gainDB.reset(_currentSampleRate, 0.02);
        _gainDB.setTargetValue(0.0);
        _thresh.reset(_currentSampleRate, 0.02);
        _thresh.setTargetValue(1.0);
    }
}

template <typename SampleType>
void viator_dsp::Distortion<SampleType>::setDrive(SampleType newDrive)
{
    _rawGain.setTargetValue(newDrive);
    _gainDB.setTargetValue(viator_utils::utils::dbToGain(newDrive));
}

template <typename SampleType>
void viator_dsp::Distortion<SampleType>::setThresh(SampleType newThresh)
{
    _thresh.setTargetValue(newThresh);
}

template <typename SampleType>
void viator_dsp::Distortion<SampleType>::setEnabled(SampleType isEnabled)
{
    _globalEnabled = isEnabled;
}

template <typename SampleType>
void viator_dsp::Distortion<SampleType>::setClipperType(ClipType clipType)
{
    switch (clipType)
    {
        case ClipType::kHard: m_clipType = viator_dsp::Distortion<SampleType>::ClipType::kHard; break;
        case ClipType::kSoft: m_clipType = viator_dsp::Distortion<SampleType>::ClipType::kSoft; break;
        case ClipType::kDiode: m_clipType = viator_dsp::Distortion<SampleType>::ClipType::kDiode; break;
    }
}

template class viator_dsp::Distortion<float>;
template class viator_dsp::Distortion<double>;
