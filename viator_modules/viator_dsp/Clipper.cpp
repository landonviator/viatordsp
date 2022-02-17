#include "Clipper.h"

viator_dsp::Clipper::Clipper() :
mGlobalBypass(false), mThresh(1.0f), mClipType(viator_dsp::Clipper::ClipType::kHard)
{
    mPiDivisor = 2.0 / juce::MathConstants<float>::pi;
}

void viator_dsp::Clipper::prepare(const juce::dsp::ProcessSpec& spec)
{
    mCurrentSampleRate = spec.sampleRate;
    mRawGain.reset(mCurrentSampleRate, 0.02);
    mRawGain.setTargetValue(0.0);
}

void viator_dsp::Clipper::setParameter(ParameterId parameter, float parameterValue)
{
    switch (parameter)
    {
        case ParameterId::kPreamp: mRawGain.setTargetValue(parameterValue); break;
        case ParameterId::kSampleRate: mCurrentSampleRate = parameterValue; break;
        case ParameterId::kThresh: mThresh = parameterValue; break;
        case ParameterId::kBypass: mGlobalBypass = static_cast<bool>(parameterValue);
    }
}

void viator_dsp::Clipper::setClipperType(ClipType clipType)
{
    switch (clipType)
    {
        case ClipType::kHard: mClipType = viator_dsp::Clipper::ClipType::kHard; break;
        case ClipType::kSoft: mClipType = viator_dsp::Clipper::ClipType::kSoft; break;
        case ClipType::kDiode: mClipType = viator_dsp::Clipper::ClipType::kDiode; break;
        case ClipType::kRectifier: mClipType = viator_dsp::Clipper::ClipType::kRectifier; break;
    }
}

float viator_dsp::Clipper::hardClipData(float dataToClip, const float thresh)
{
    /** Don't do anything if the module is off*/
    if (mGlobalBypass) return dataToClip;
    
    /** Works well with input * dB range of [0...20]*/
    dataToClip *= viator_utils::utils::dbToGain(mRawGain.getNextValue());
    
    /** Hard Clipping algorithim*/
    if (std::abs(dataToClip) > thresh)
    {
        dataToClip *= thresh / std::abs(dataToClip);
    }
    
    return dataToClip;
}

float viator_dsp::Clipper::softClipData(float dataToClip)
{
    /** Don't do anything if the module is off*/
    if (mGlobalBypass) return dataToClip;
    
    /** Works well with input * dB range of [0...20]*/
    dataToClip *= viator_utils::utils::dbToGain(mRawGain.getNextValue());
    
    /** Soft Clipping algorithim*/
    return mPiDivisor * std::atan(dataToClip);
}
