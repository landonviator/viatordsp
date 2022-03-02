#include "Clipper.h"

template <typename SampleType>
viator_dsp::Clipper<SampleType>::Clipper() :
mGlobalBypass(false), mThresh(1.0f), mGainDB(1.0), mClipType(viator_dsp::Clipper<SampleType>::ClipType::kHard)
{
    mPiDivisor = 2.0 / juce::MathConstants<float>::pi;
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

template <typename SampleType>
SampleType viator_dsp::Clipper<SampleType>::hardClipData(SampleType dataToClip, const float thresh)
{
    /** Don't do anything if the module is off*/
    if (mGlobalBypass) return dataToClip;
    
    /** Hard Clipping algorithim*/
    if (std::abs(dataToClip) > thresh)
    {
        dataToClip *= thresh / std::abs(dataToClip);
    }
    
    return dataToClip;
}

template <typename SampleType>
SampleType viator_dsp::Clipper<SampleType>::softClipData(SampleType dataToClip)
{
    /** Don't do anything if the module is off*/
    if (mGlobalBypass) return dataToClip;
    
    /** Soft Clipping algorithim*/
    auto softClipper = mPiDivisor * std::atan(dataToClip) * 2.0;
    
    /** Auto gain stage the soft clipper*/
    softClipper *= viator_utils::utils::dbToGain(-mRawGain.getNextValue() * 0.25);
    
    return softClipper;
}

template <typename SampleType>
SampleType viator_dsp::Clipper<SampleType>::diodeClipper(SampleType dataToClip)
{
    /** Don't do anything if the module is off*/
    if (mGlobalBypass) return dataToClip;
    
    /** Diode Clipping algorithim*/
    auto diode = 0.105 * (juce::dsp::FastMathApproximations::exp(0.1 * dataToClip / (2.0 * 0.0253)) - 1.0);
    diode -= 0.28;
    diode *= 3.0;
    
    return softClipData(diode);
}
template class viator_dsp::Clipper<float>;
template class viator_dsp::Clipper<double>;
