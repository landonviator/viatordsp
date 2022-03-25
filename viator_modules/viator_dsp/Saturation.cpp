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
}

template <typename SampleType>
void viator_dsp::Saturation<SampleType>::setParameter(ParameterId parameter, SampleType parameterValue)
{
    switch (parameter)
    {
        case ParameterId::kPreamp:
        {
            mRawGainDB.setTargetValue(parameterValue); break;
            mRawGain = viator_utils::utils::dbToGain(mRawGainDB.getNextValue());
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
        case DistortionType::kTransformer: mDistortionType = Saturation<SampleType>::DistortionType::kTransformer; break;

    }
}

template class viator_dsp::Saturation<float>;
template class viator_dsp::Saturation<double>;

