#include "Clipper.h"

template <typename SampleType>
viator_dsp::Clipper<SampleType>::Clipper() :
mGlobalBypass(false), mThresh(1.0f), mGainDB(1.0), mClipType(viator_dsp::Clipper<SampleType>::ClipType::kHard)
{
}

template <typename SampleType>
void viator_dsp::Clipper<SampleType>::prepare(const juce::dsp::ProcessSpec& spec)
{
    mCurrentSampleRate = spec.sampleRate;
    mRawGain.reset(mCurrentSampleRate, 0.02);
    mRawGain.setTargetValue(0.0);
}

template <typename SampleType>
void viator_dsp::Clipper<SampleType>::setParameter(ParameterId parameter, SampleType parameterValue)
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

template <typename SampleType>
void viator_dsp::Clipper<SampleType>::setClipperType(ClipType clipType)
{
    switch (clipType)
    {
        case ClipType::kHard: mClipType = viator_dsp::Clipper<SampleType>::ClipType::kHard; break;
        case ClipType::kSoft: mClipType = viator_dsp::Clipper<SampleType>::ClipType::kSoft; break;
        case ClipType::kDiode: mClipType = viator_dsp::Clipper<SampleType>::ClipType::kDiode; break;
    }
}


template class viator_dsp::Clipper<float>;
template class viator_dsp::Clipper<double>;
