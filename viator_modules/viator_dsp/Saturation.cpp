#include "Saturation.h"

template <typename SampleType>
viator_dsp::Saturation<SampleType>::Saturation() :
mGlobalBypass(false), mThresh(1.0f), mGainDB(1.0)
{
}

template <typename SampleType>
void viator_dsp::Saturation<SampleType>::prepare(const juce::dsp::ProcessSpec& spec)
{
    mCurrentSampleRate = spec.sampleRate;
    mRawGain.reset(mCurrentSampleRate, 0.02);
    mRawGain.setTargetValue(0.0);
}

template <typename SampleType>
void viator_dsp::Saturation<SampleType>::setParameter(ParameterId parameter, SampleType parameterValue)
{
    switch (parameter)
    {
        case ParameterId::kPreamp:
        {
            mRawGain.setTargetValue(parameterValue); break;
            mGainDB = viator_utils::utils::dbToGain(mRawGain.getNextValue());
        }
        case ParameterId::kSampleRate: mCurrentSampleRate = parameterValue; break;
        case ParameterId::kThresh: mThresh = parameterValue; break;
        case ParameterId::kBypass: mGlobalBypass = static_cast<bool>(parameterValue);
    }
}

template class viator_dsp::Saturation<float>;
template class viator_dsp::Saturation<double>;

