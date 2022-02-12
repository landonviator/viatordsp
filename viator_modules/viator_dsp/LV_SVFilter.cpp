///*
//  ==============================================================================
//
//    LV_EQ.cpp
//    Created: 25 May 2021 5:40:30pm
//    Author:  Landon Viator
//
//  ==============================================================================
//*/
//
//#include "LV_SVFilter.h"
//
//void LV_SVFilter::reset()
//{
//
//}
////==============================================================================
//
//void LV_SVFilter::prepare(juce::dsp::ProcessSpec& spec)
//{
//    mCurrentSampleRate = spec.sampleRate;
//    mZ1.assign(spec.numChannels, 0.0);
//    mZ2.assign(spec.numChannels, 0.0);
//}
////==============================================================================
//
//void LV_SVFilter::setParameter(ParameterId parameter, float parameterValue)
//{
//    switch (parameter)
//    {
//        case ParameterId::kType: mType = (FilterType)parameterValue; break;
//        case ParameterId::kQType: mQType = (QType)parameterValue; break;
//        case ParameterId::kCutoff: mCutoff = parameterValue; break;
//        case ParameterId::kQ: mQ = parameterValue; break;
//        case ParameterId::kGain: setGain(parameterValue); break;
//        case ParameterId::kSampleRate: mCurrentSampleRate = parameterValue; break;
//        case ParameterId::kBypass: mGlobalBypass = static_cast<bool>(parameterValue);
//        case ParameterId::kClipOutput: mClipOutput = static_cast<bool>(parameterValue);
//    }
//}
////==============================================================================
//
//void LV_SVFilter::setGain(float value)
//{
//    constexpr double inversion = 1.0 / 20.0;
//    mGain = pow(10, value * inversion) - 1.f;
//    mRawGain = value;
//}
////==============================================================================
//
//float LV_SVFilter::getShelfQ(float value) const
//{
//    return std::pow(10.0f, std::abs(value) / 20.0f) * 0.25f - 0.24f;
//}
////==============================================================================
//
//float LV_SVFilter::getPeakQ(float value) const
//{
//    return std::pow(10.0f, std::abs(value) / 20.0f) * 0.2f;
//}
////==============================================================================
//
//void LV_SVFilter::processBlock(juce::dsp::AudioBlock<float>& block)
//{
//    if (mGlobalBypass) return;
//
//    float lsLevel = 0.0;
//    float bsLevel = 0.0;
//    float hsLevel = 0.0;
//    float lpLevel = 0.0;
//    float hpLevel = 0.0;
//
//    switch (mType)
//    {
//        case kLowShelf: lsLevel = 1.0; break;
//        case kBandShelf: bsLevel = 1.0; break;
//        case kHighShelf: hsLevel = 1.0; break;
//        case kLowPass: lpLevel = 1.0; break;
//        case kHighPass: hpLevel = 1.0; break;
//    }
//
//    const double sampleRate2X = mCurrentSampleRate * 2.0;
//    const double halfSampleDuration = 1.0 / mCurrentSampleRate / 2.0;
//
//    for (int sample = 0; sample < block.getNumSamples(); ++sample)
//    {
//        // prewarp the cutoff (for bilinear-transform filters)
//        double wd = mCutoff * 6.28f;
//        double wa = sampleRate2X * tan(wd * halfSampleDuration);
//
//        //Calculate g (gain element of integrator)
//        mGCoeff = wa * halfSampleDuration;
//
//        //Calculate Zavalishin's damping parameter (Q)
//        switch (mQType)
//        {
//            case kParametric: mRCoeff = 1.0 - mQ; break;
//            case kProportional:
//
//            if (mType == kBandShelf)
//            {
//                mRCoeff = 1.0 - getPeakQ(mRawGain); break;
//            }
//
//            else
//            {
//                mRCoeff = 1.0 - getShelfQ(mRawGain); break;
//            }
//        }
//
//        mRCoeff2 = mRCoeff * 2.0;
//
//        mInversion = 1.0 / (1.0 + mRCoeff2 * mGCoeff + mGCoeff * mGCoeff);
//
//        for (int ch = 0; ch < block.getNumChannels(); ++ch)
//        {
//            const auto z1 = mZ1[ch];
//            const auto z2 = mZ2[ch];
//
//            float* data = block.getChannelPointer(ch);
//
//            const float x = data[sample];
//
//            const double HP = (x - mRCoeff2 * z1 - mGCoeff * z1 - z2) * mInversion;
//            const double BP = HP * mGCoeff + z1;
//            const double LP = BP * mGCoeff + z2;
//            const double UBP = mRCoeff2 * BP;
//            const double BShelf = x + UBP * mGain;
//            const double LS = x + mGain * LP;
//            const double HS = x + mGain * HP;
//
//            data[sample] = BShelf * bsLevel + LS * lsLevel + HS * hsLevel + HP * hpLevel + LP * lpLevel;
//
//            if (mClipOutput && std::abs(data[sample]) > 1.0)
//            {
//                data[sample] *= 1.0 / std::abs(data[sample]);
//            }
//
//            // unit delay (state variable)
//            mZ1[ch] = mGCoeff * HP + BP;
//            mZ2[ch] = mGCoeff * BP + LP;
//
//        }
//    }
//}
