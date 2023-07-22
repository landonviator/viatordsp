#include "Distortion.h"

template <typename SampleType>
viator_dsp::Distortion<SampleType>::Distortion() :
_globalEnabled(true), _thresh(1.0f), m_clipType(viator_dsp::Distortion<SampleType>::ClipType::kFuzz)
{
}

template <typename SampleType>
void viator_dsp::Distortion<SampleType>::prepare(const juce::dsp::ProcessSpec& spec) noexcept
{
    _currentSampleRate = spec.sampleRate;
    
    m_fuzzFilter.prepare(spec);
    m_fuzzFilter.setStereoType(viator_dsp::SVFilter<float>::StereoId::kStereo);
    m_fuzzFilter.setParameter(viator_dsp::SVFilter<float>::ParameterId::kType, viator_dsp::SVFilter<float>::FilterType::kLowShelf);
    m_fuzzFilter.setParameter(viator_dsp::SVFilter<float>::ParameterId::kQType, viator_dsp::SVFilter<float>::QType::kParametric);
    m_fuzzFilter.setParameter(viator_dsp::SVFilter<float>::ParameterId::kCutoff, 2000.0);
    m_fuzzFilter.setParameter(viator_dsp::SVFilter<float>::ParameterId::kGain, 9.0);
    
    m_lofiFilter.prepare(spec);
    m_lofiFilter.setStereoType(viator_dsp::SVFilter<float>::StereoId::kStereo);
    m_lofiFilter.setParameter(viator_dsp::SVFilter<float>::ParameterId::kType, viator_dsp::SVFilter<float>::FilterType::kLowPass);
    m_lofiFilter.setParameter(viator_dsp::SVFilter<float>::ParameterId::kQType, viator_dsp::SVFilter<float>::QType::kParametric);
    m_lofiFilter.setParameter(viator_dsp::SVFilter<float>::ParameterId::kCutoff, 20000.0);
    
    _dcFilter.prepare(spec);
    _dcFilter.setType(juce::dsp::LinkwitzRileyFilter<float>::Type::highpass);
    _dcFilter.setCutoffFrequency(10.0);
    
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
        _ceiling.reset(_currentSampleRate, 0.02);
        _ceiling.setTargetValue(1.0);
        _mix.reset(_currentSampleRate, 0.02);
        _mix.setTargetValue(1.0);
        _output.reset(_currentSampleRate, 0.02);
        _output.setTargetValue(0.0);
    }
}

template <typename SampleType>
void viator_dsp::Distortion<SampleType>::setDrive(SampleType newDrive)
{
    _gainDB.setTargetValue(newDrive);
    _rawGain.setTargetValue(juce::Decibels::decibelsToGain(newDrive));
    
    // Change high cut cutoff when drive changes
    auto cutoff = juce::jmap(static_cast<float>(newDrive), 0.0f, 20.0f, 20000.0f, 3000.0f);
    m_lofiFilter.setParameter(viator_dsp::SVFilter<float>::ParameterId::kCutoff, cutoff);
}

template <typename SampleType>
void viator_dsp::Distortion<SampleType>::setThresh(SampleType newThresh)
{
    _thresh.setTargetValue(newThresh);
}

template <typename SampleType>
void viator_dsp::Distortion<SampleType>::setCeiling(SampleType newCeiling)
{
    _ceiling.setTargetValue(newCeiling);
}

template <typename SampleType>
void viator_dsp::Distortion<SampleType>::setMix(SampleType newMix)
{
    _mix.setTargetValue(newMix);
}

template <typename SampleType>
void viator_dsp::Distortion<SampleType>::setOutput(SampleType newOutput)
{
   _output.setTargetValue(newOutput);
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
        case ClipType::kFuzz: m_clipType = viator_dsp::Distortion<SampleType>::ClipType::kFuzz; break;
        case ClipType::kTube: m_clipType = viator_dsp::Distortion<SampleType>::ClipType::kTube; break;
        case ClipType::kSaturation: m_clipType = viator_dsp::Distortion<SampleType>::ClipType::kSaturation; break;
        case ClipType::kLofi: m_clipType = viator_dsp::Distortion<SampleType>::ClipType::kLofi; break;
    }
}

template class viator_dsp::Distortion<float>;
template class viator_dsp::Distortion<double>;
