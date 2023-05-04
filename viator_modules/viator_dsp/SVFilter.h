#ifndef SVFilter_h
#define SVFilter_h

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
        if (mRawGain == 0.0)
        {
            if (mType != kHighPass && mType != kLowPass)
            {
                return;
            }
        }
        
        if (mType == kHighPass && mCutoff == 20.0) return;
        if (mType == kLowPass && mCutoff == 20000.0) return;
        
        
        if (mGlobalBypass) return;
        
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
            auto *leftOutputData = outBlock.getChannelPointer(0);
            
            for (size_t sample = 0; sample < len; ++sample)
            {
                if (inBlock.getNumChannels() == 2)
                {
                        
                    auto *rightInputData = inBlock.getChannelPointer(1);
                    auto *rightOutputData = outBlock.getChannelPointer(1);
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
                    
                else
                {
                    output[sample] = processSample(input[sample], channel);
                }
            }
        }
    }
    
    /** Process an individual sample */
    SampleType processSample(SampleType input, SampleType ch) noexcept
    {
        
        
        const auto z1 = mZ1[ch];
        const auto z2 = mZ2[ch];
                                
        const double HP = (input - mRCoeff2 * z1 - mGCoeff * z1 - z2) * mInversion;
        const double BP = HP * mGCoeff + z1;
        const double LP = BP * mGCoeff + z2;
        const double UBP = mRCoeff2 * BP;
        const double BShelf = input + UBP * mGain;
        const double LS = input + mGain * LP;
        const double HS = input + mGain * HP;
                    
        //Main output code
        input = BShelf * bsLevel + LS * lsLevel + HS * hsLevel + HP * hpLevel + LP * lpLevel;
                   
        // unit delay (state variable)
        mZ1[ch] = mGCoeff * HP + BP;
        mZ2[ch] = mGCoeff * BP + LP;

        return input * juce::Decibels::decibelsToGain(_output.getNextValue());
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
    void setOutput(SampleType newOutput);
    void setStereoType(StereoId newStereoType);
    
private:
    
    /** Member variables */
    float mCurrentSampleRate, mQ, mCutoff, mGain, mRawGain, twoPi;
    bool mGlobalBypass;
    
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
    
    float lsLevel = 0.0;
    float bsLevel = 0.0;
    float hsLevel = 0.0;
    float lpLevel = 0.0;
    float hpLevel = 0.0;
    
    juce::SmoothedValue<float> _output;
    
    double sampleRate2X;
    double halfSampleDuration;
    
    double wd;
    double wa;
    
    void preWarp();
    void setType();
    void setSampleRates();
};
}

#endif /* SVFilter_h */
