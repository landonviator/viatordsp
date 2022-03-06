#include "SVFilter.h"
template <typename SampleType>
viator_dsp::SVFilter<SampleType>::SVFilter()
: mCurrentSampleRate (44100.0f), mQ (0.1f), mCutoff (1000.0f), mRawGain (0.0f), twoPi (juce::MathConstants<float>::twoPi)
, mGlobalBypass (false), mClipOutput (false)
, mGCoeff (0.0), mRCoeff (0.0), mRCoeff2 (0.0), mK (1.0), mInversion (0.0)
, mType (FilterType::kLowPass), mQType (QType::kParametric)
{
    
}

template <typename SampleType>
void viator_dsp::SVFilter<SampleType>::prepare(juce::dsp::ProcessSpec& spec)
{
    mCurrentSampleRate = spec.sampleRate;
    sampleRate2X = mCurrentSampleRate * 2.0;
    halfSampleDuration = 1.0 / mCurrentSampleRate / 2.0;
    
    mZ1.assign(spec.numChannels, 0.0);
    mZ2.assign(spec.numChannels, 0.0);
}

//template <typename SampleType>
//float viator_dsp::SVFilter<SampleType>::processSample(SampleType input, int ch)
//{
//    if (mGlobalBypass)
//        return 1.0;
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
//    // prewarp the cutoff (for bilinear-transform filters)
//    double wd = mCutoff * 6.28f;
//    double wa = sampleRate2X * tan(wd * halfSampleDuration);
//                
//    //Calculate g (gain element of integrator)
//    mGCoeff = wa * halfSampleDuration;
//                
//    //Calculate Zavalishin's damping parameter (Q)
//    switch (mQType)
//    {
//        case kParametric: mRCoeff = 1.0 - mQ; break;
//        case kProportional:
//                
//        if (mType == kBandShelf)
//        {
//            mRCoeff = 1.0 - getPeakQ(mRawGain); break;
//        }
//            
//        else
//        {
//            mRCoeff = 1.0 - getShelfQ(mRawGain); break;
//        }
//    }
//        
//    mRCoeff2 = mRCoeff * 2.0;
//                
//    mInversion = 1.0 / (1.0 + mRCoeff2 * mGCoeff + mGCoeff * mGCoeff);
//            
//    const auto z1 = mZ1[ch];
//    const auto z2 = mZ2[ch];
//                            
//    const double HP = (input - mRCoeff2 * z1 - mGCoeff * z1 - z2) * mInversion;
//    const double BP = HP * mGCoeff + z1;
//    const double LP = BP * mGCoeff + z2;
//    const double UBP = mRCoeff2 * BP;
//    const double BShelf = input + UBP * mGain;
//    const double LS = input + mGain * LP;
//    const double HS = input + mGain * HP;
//                
//    //Main output code
//    input = BShelf * bsLevel + LS * lsLevel + HS * hsLevel + HP * hpLevel + LP * lpLevel;
//               
//    // unit delay (state variable)
//    mZ1[ch] = mGCoeff * HP + BP;
//    mZ2[ch] = mGCoeff * BP + LP;
//
//    return input;
//}

template <typename SampleType>
void viator_dsp::SVFilter<SampleType>::setParameter(ParameterId parameter, SampleType parameterValue)
{
    switch (parameter)
    {
        case ParameterId::kType:
            
        {
            mType = (FilterType)parameterValue;
            
            switch (mType)
            {
                case kLowShelf:
                {
                    bsLevel = 0.0;
                    hsLevel = 0.0;
                    lpLevel = 0.0;
                    hpLevel = 0.0;
                    lsLevel = 1.0; break;
                }
                    
                case kBandShelf:
                {
                    hsLevel = 0.0;
                    lpLevel = 0.0;
                    hpLevel = 0.0;
                    lsLevel = 0.0;
                    bsLevel = 1.0; break;
                }
                    
                case kHighShelf:
                {
                    bsLevel = 0.0;
                    lpLevel = 0.0;
                    hpLevel = 0.0;
                    lsLevel = 0.0;
                    hsLevel = 1.0; break;
                }
                    
                case kLowPass:
                {
                    bsLevel = 0.0;
                    hsLevel = 0.0;
                    hpLevel = 0.0;
                    lsLevel = 0.0;
                    lpLevel = 1.0; break;
                }
                    
                case kHighPass:
                {
                    bsLevel = 0.0;
                    hsLevel = 0.0;
                    lpLevel = 0.0;
                    lsLevel = 0.0;
                    hpLevel = 1.0;break;
                }
            }
            
            break;
        }
            
        case ParameterId::kQType: mQType = (QType)parameterValue; break;
        case ParameterId::kCutoff: mCutoff = parameterValue; break;
        case ParameterId::kQ:
        {
            mQ = parameterValue;
            
            //Calculate Zavalishin's damping parameter (Q)
            switch (mQType)
            {
                case kParametric: mRCoeff = 1.0 - mQ; break;
                case kProportional:
                    
                    if (mType == kBandShelf)
                    {
                        mRCoeff = 1.0 - getPeakQ(mRawGain); break;
                    }
                    
                    else
                    {
                        mRCoeff = 1.0 - getShelfQ(mRawGain); break;
                    }
            }
            
            mRCoeff2 = mRCoeff * 2.0;
                    
            mInversion = 1.0 / (1.0 + mRCoeff2 * mGCoeff + mGCoeff * mGCoeff);
            
            break;
        }
        case ParameterId::kGain: setGain(parameterValue); break;
            
        case ParameterId::kSampleRate:
        {
            mCurrentSampleRate = parameterValue;
            sampleRate2X = mCurrentSampleRate * 2.0;
            halfSampleDuration = 1.0 / mCurrentSampleRate / 2.0;
            break;
        }
        case ParameterId::kBypass: mGlobalBypass = static_cast<bool>(parameterValue);
        case ParameterId::kClipOutput: mClipOutput = static_cast<bool>(parameterValue);
    }
}

template <typename SampleType>
void viator_dsp::SVFilter<SampleType>::setGain(SampleType value)
{
    mGain = pow(10, value * 0.05) - 1.f;
    mRawGain = value;
}

template <typename SampleType>
SampleType viator_dsp::SVFilter<SampleType>::getShelfQ(SampleType value) const
{
    return viator_utils::utils::dbToGain(std::abs(value)) * 0.25f - 0.24f;
}

template <typename SampleType>
SampleType viator_dsp::SVFilter<SampleType>::getPeakQ(SampleType value) const
{
    return viator_utils::utils::dbToGain(std::abs(value)) * 0.2f;
}

template class viator_dsp::SVFilter<float>;
template class viator_dsp::SVFilter<double>;
