#include "Saturation.h"

template <typename SampleType>
viator_dsp::Saturation<SampleType>::Saturation() :
mGlobalBypass(false), mThresh(1.0f), mRawGain(1.0)
{
}

template <typename SampleType>
void viator_dsp::Saturation<SampleType>::prepare(const juce::dsp::ProcessSpec& spec)
{
    mCurrentSampleRate = spec.sampleRate;
    mRawGainDB.reset(mCurrentSampleRate, 0.02);
    mRawGainDB.setTargetValue(0.0);
    
    tapeFilter.prepare(spec);
    tapeFilter.setParameter(viator_dsp::SVFilter<float>::ParameterId::kType, viator_dsp::SVFilter<float>::FilterType::kLowShelf);
    tapeFilter.setParameter(viator_dsp::SVFilter<float>::ParameterId::kQType, viator_dsp::SVFilter<float>::QType::kParametric);
    tapeFilter.setParameter(viator_dsp::SVFilter<float>::ParameterId::kGain, mRawGainDB.getNextValue());
    tapeFilter.setParameter(viator_dsp::SVFilter<float>::ParameterId::kCutoff, 130);
    tapeFilter.setParameter(viator_dsp::SVFilter<float>::ParameterId::kQ, 0.69);
}

template <typename SampleType>
void viator_dsp::Saturation<SampleType>::setParameter(ParameterId parameter, SampleType parameterValue)
{
    switch (parameter)
    {
        case ParameterId::kPreamp:
        {
            mRawGainDB.setTargetValue(parameterValue);
            mRawGain = viator_utils::utils::dbToGain(mRawGainDB.getNextValue());
            
            // filter gain based on tape input drive
            tapeFilter.setParameter(viator_dsp::SVFilter<float>::ParameterId::kGain, mRawGainDB.getNextValue() * 0.075);
            break;
        }
            
        case ParameterId::kSampleRate: mCurrentSampleRate = parameterValue; break;
        case ParameterId::kThresh: mThresh = parameterValue; break;
        case ParameterId::kBypass: mGlobalBypass = static_cast<bool>(parameterValue);
    }
}

template <typename SampleType>
void viator_dsp::Saturation<SampleType>::setDistortionType(DistortionType distortionType)
{
    switch (distortionType)
    {
        case DistortionType::kHard: mDistortionType = Saturation<SampleType>::DistortionType::kHard; break;
        case DistortionType::kSaturation: mDistortionType = Saturation<SampleType>::DistortionType::kSaturation; break;
        case DistortionType::kTube: mDistortionType = Saturation<SampleType>::DistortionType::kTube; break;
        case DistortionType::kTape: mDistortionType = Saturation<SampleType>::DistortionType::kTape; break;

    }
}

template class viator_dsp::Saturation<float>;
template class viator_dsp::Saturation<double>;

