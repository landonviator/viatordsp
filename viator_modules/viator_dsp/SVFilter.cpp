#include "SVFilter.h"
template <typename SampleType>
viator_dsp::SVFilter<SampleType>::SVFilter()
: mCurrentSampleRate (44100.0f), mQ (0.1f), mCutoff (1000.0f), mRawGain (0.0f), twoPi (juce::MathConstants<float>::twoPi)
, mGlobalBypass (false)
, mGCoeff (0.0), mRCoeff (0.0), mRCoeff2 (0.0), mK (1.0), mInversion (0.0)
, mType (FilterType::kLowPass), mQType (QType::kParametric), mStereoType(StereoId::kStereo)
{
    // This needs to be called at initialization or the filter breaks
    setParameter(ParameterId::kQ, mQ);
}

template <typename SampleType>
void viator_dsp::SVFilter<SampleType>::prepare(const juce::dsp::ProcessSpec& spec)
{
    mCurrentSampleRate = spec.sampleRate;
    setSampleRates();
    
    _output.reset(mCurrentSampleRate, 0.02);
    _output.setTargetValue(0.0);
    
    mZ1.assign(spec.numChannels, 0.0);
    mZ2.assign(spec.numChannels, 0.0);
}

template <typename SampleType>
void viator_dsp::SVFilter<SampleType>::setParameter(ParameterId parameter, SampleType parameterValue)
{
    switch (parameter)
    {
        // Filter Type
        case ParameterId::kType:
        {
            mType = (FilterType)parameterValue;
            setType();
            break;
        }
            
        // Filter Q Type
        case ParameterId::kQType:
        {
            mQType = (QType)parameterValue;
            
            //Calculate Zavalishin's damping parameter (Q)
//            switch (mQType)
//            {
//                case kParametric: mRCoeff = 1.0 - mQ; break;
//
//                case kProportional:
//                {
//                    if (mType == kBandShelf)
//                    {
//                        mRCoeff = 1.0 - getPeakQ(mRawGain);
//                        preWarp();
//                        break;
//                    }
//
//                    else
//                    {
//                        mRCoeff = 1.0 - getShelfQ(mRawGain);
//                        preWarp();
//                        break;
//                    }
//                }
//            }
            
            break;
        }
            
        // Filter Cutoff
        case ParameterId::kCutoff:
        {
            mCutoff = parameterValue;
            preWarp();
            break;
        }
            
        // Bandwidth
        case ParameterId::kQ:
        {
            mQ = parameterValue;
            
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
            
        // Filter Gain
        case ParameterId::kGain:
        {
            setGain(parameterValue);
            break;
        }
            
        // Filter samplerate
        case ParameterId::kSampleRate:
        {
            mCurrentSampleRate = parameterValue;
            setSampleRates();
            break;
        }
            
        // Filter Bypass
        case ParameterId::kBypass: mGlobalBypass = static_cast<bool>(parameterValue); break;
    }
}

template <typename SampleType>
void viator_dsp::SVFilter<SampleType>::setOutput(SampleType newOutput)
{
    _output.setTargetValue(newOutput);
}

template <typename SampleType>
void viator_dsp::SVFilter<SampleType>::setStereoType(StereoId newStereoID)
{
    switch (newStereoID)
    {
        case StereoId::kStereo: mStereoType = newStereoID; break;
        case StereoId::kMids: mStereoType = newStereoID; break;
        case StereoId::kSides: mStereoType = newStereoID; break;
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
    return viator_utils::utils::dbToGain(std::abs(value)) * 0.1f;
}

template <typename SampleType>
void viator_dsp::SVFilter<SampleType>::preWarp()
{
    // prewarp the cutoff (for bilinear-transform filters)
    wd = mCutoff * 6.28f;
    wa = sampleRate2X * std::tan(wd * halfSampleDuration);
            
    //Calculate g (gain element of integrator)
    mGCoeff = wa * halfSampleDuration;
            
    mRCoeff2 = mRCoeff * 2.0;
            
    mInversion = 1.0 / (1.0 + mRCoeff2 * mGCoeff + mGCoeff * mGCoeff);
}

template <typename SampleType>
void viator_dsp::SVFilter<SampleType>::setType()
{
    switch (mType)
    {
        case kLowShelf: lsLevel = 1.0; break;
        case kBandShelf: bsLevel = 1.0; break;
        case kHighShelf: hsLevel = 1.0; break;
        case kLowPass: lpLevel = 1.0; break;
        case kHighPass: hpLevel = 1.0; break;
    }
}

template <typename SampleType>
void viator_dsp::SVFilter<SampleType>::setSampleRates()
{
    sampleRate2X = mCurrentSampleRate * 2.0;
    halfSampleDuration = 1.0 / mCurrentSampleRate / 2.0;
}

template class viator_dsp::SVFilter<float>;
template class viator_dsp::SVFilter<double>;
//template class viator_dsp::SVFilter<juce::dsp::SIMDRegister<float>>;

