/*
  ==============================================================================

    LV_EQ.h
    Created: 25 May 2021 5:40:30pm
    Author:  Landon Viator

  ==============================================================================
*/

#ifndef svfilter_h
#define svfilter_h

namespace viator_dsp
{
template <typename SampleType>
class SVFilter
{
public:
    
    /** Creates an uninitialised filter. Call prepare() before first use. */
    SVFilter();
    
    /** Initialises the filter. */
    void prepare(const juce::dsp::ProcessSpec& spec);
    
    /** Processes the input and output buffers supplied in the processing context. */
    template <typename ProcessContext>
    void process (const ProcessContext& context) noexcept
    {
        if (mGlobalBypass)
        {
            return;
        }
        
        auto&& inBlock  = context.getInputBlock();
        auto&& outBlock = context.getOutputBlock();

        jassert (inBlock.getNumChannels() == outBlock.getNumChannels());
        jassert (inBlock.getNumSamples() == outBlock.getNumSamples());

        auto len         = inBlock.getNumSamples();
        auto numChannels = inBlock.getNumChannels();
        
        for (size_t channel = 0; channel < numChannels; ++channel)
        {
            
            auto *input = inBlock.getChannelPointer(channel);
            auto* output = outBlock.getChannelPointer (channel);
            
            auto *leftInputData = inBlock.getChannelPointer(0);
            auto *rightInputData = inBlock.getChannelPointer(1);
            
            auto *leftOutputData = outBlock.getChannelPointer(0);
            auto *rightOutputData = outBlock.getChannelPointer(1);
            
            for (size_t sample = 0; sample < len; ++sample)
            {
                auto mid_x = 0.5 * (leftInputData[sample] + rightInputData[sample]);
                auto side_x = 0.5 * (leftInputData[sample] - rightInputData[sample]);
                
                switch (mStereoType)
                {
                    case StereoId::kStereo:
                    {
                        output[sample] = processSample(input[sample], channel);
                        break;
                    }
                        
                    case StereoId::kMids:
                    {
                        mid_x = processSample(mid_x, channel);
                        
                        auto newL = mid_x + side_x;
                        auto newR = mid_x - side_x;
                        
                        leftOutputData[sample] = newL;
                        rightOutputData[sample] = newR;
                        break;
                    }
                        
                    case StereoId::kSides:
                    {
                        side_x = processSample(side_x, channel);
                        
                        auto newL = mid_x + side_x;
                        auto newR = mid_x - side_x;
                        
                        leftOutputData[sample] = newL;
                        rightOutputData[sample] = newR;
                        break;
                    }
                }
            }
        }
    }
    
    /** Process an individual sample */
    SampleType processSample(SampleType input, SampleType ch) noexcept
    {
        
        if (mGlobalBypass)
        {
            return input;
        }
        
        const double sampleRate2X = mCurrentSampleRate * 2.0;
        const double halfSampleDuration = 1.0 / mCurrentSampleRate / 2.0;
        
        // prewarp the cutoff (for bilinear-transform filters)
        double wd = mCutoff * 6.28f;
        double wa = sampleRate2X * tan(wd * halfSampleDuration);
                
        //Calculate g (gain element of integrator)
        mGCoeff = wa * halfSampleDuration;
        
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
                
                break;
        }
        
        mRCoeff2 = mRCoeff * 2.0;
        mInversion = 1.0 / (1.0 + mRCoeff2 * mGCoeff + mGCoeff * mGCoeff);
        
        const auto z1 = mZ1[ch];
        const auto z2 = mZ2[ch];
            
        float x = input;
                
        const double HP = (x - mRCoeff2 * z1 - mGCoeff * z1 - z2) * mInversion;
        const double BP = HP * mGCoeff + z1;
        const double LP = BP * mGCoeff + z2;
        const double UBP = mRCoeff2 * BP;
        const double BShelf = x + UBP * mGain;
        const double LS = x + mGain * LP;
        const double HS = x + mGain * HP;
            
        //Main output code
        switch (mType)
        {
            case kBandShelf: x = BShelf; break;
            case kLowShelf: x = LS; break;
            case kHighShelf: x = HS; break;
            case kHighPass: x = HP; break;
            case kLowPass: x = LP; break;
        }
                
        // unit delay (state variable)
        mZ1[ch] = mGCoeff * HP + BP;
        mZ2[ch] = mGCoeff * BP + LP;
        
        return x;
    }
    
    
    /** The parameters of this module. */
    enum class ParameterId
    {
        kType,
        kCutoff,
        kQ,
        kGain,
        kQType,
        kSampleRate,
        kBypass
    };
        
    /** Different filter types*/
    enum FilterType
    {
        kLowShelf,
        kHighPass,
        kBandShelf,
        kLowPass,
        kHighShelf
    };
    
    /** Different filter Q-Factor types*/
    enum QType
    {
        kParametric,
        kProportional,
    };
    
    enum class StereoId
    {
        kStereo,
        kMids,
        kSides
    };
    
    /** One method to change any parameter. */
    void setParameter(ParameterId parameter, SampleType parameterValue);
    void setStereoType(StereoId newStereoType);
    
private:
    
    /** Member variables */
    float mCurrentSampleRate, mQ, mCutoff, mGain, mRawGain, twoPi;
    bool mGlobalBypass;
    
    float lsLevel = 0.0;
    float bsLevel = 0.0;
    float hsLevel = 0.0;
    float lpLevel = 0.0;
    float hpLevel = 0.0;
    
    float sampleRate2X = mCurrentSampleRate * 2.0;
    float halfSampleDuration = 1.0 / mCurrentSampleRate / 2.0;
    
     /** Variables for the Z filter equations */
    double mGCoeff, mRCoeff, mRCoeff2, mK, mInversion;
    
     /** Filter type switch */
    FilterType mType;
    
     /** Q mode switch */
    QType mQType;
    
    /** Stereo Type*/
    StereoId mStereoType;
    
     /** state variables (z^-1) */
    std::vector<double> mZ1, mZ2;
    
    /** Convert the gain if needed */
    void setGain(SampleType value);
    
    /** Get the different Q-Fators*/
    SampleType getShelfQ(SampleType value) const;
    SampleType getPeakQ(SampleType value) const;
};
}

#endif /* svfilter_h */
