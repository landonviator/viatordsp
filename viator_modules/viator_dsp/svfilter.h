/*
  ==============================================================================

    LV_EQ.h
    Created: 25 May 2021 5:40:30pm
    Author:  Landon Viator

  ==============================================================================
*/

#ifndef SVFilter_h
#define SVFilter_h

namespace viator_dsp
{
class SVFilter
{
public:
    
    /** Creates an uninitialised filter. Call prepare() before first use. */
    SVFilter();
    
    /** Initialises the filter. */
    void prepare(juce::dsp::ProcessSpec& spec);
    
    /** Processes the input and output buffers supplied in the processing context. */
    template <typename ProcessContext>
    void process (const ProcessContext& context) noexcept
    {
        auto&& inBlock  = context.getInputBlock();
        auto&& outBlock = context.getOutputBlock();

        jassert (inBlock.getNumChannels() == outBlock.getNumChannels());
        jassert (inBlock.getNumSamples() == outBlock.getNumSamples());

        auto len         = inBlock.getNumSamples();
        auto numChannels = inBlock.getNumChannels();

        if (mGlobalBypass)
        {
            if (context.usesSeparateInputAndOutputBlocks())
                outBlock.copyFrom (inBlock);

            return;
        }

        for (size_t sample = 0; sample < len; ++sample)
        {
            for (size_t channel = 0; channel < numChannels; ++channel)
            {
                auto* input = inBlock.getChannelPointer (channel);
                auto* output = outBlock.getChannelPointer (channel);
                
                auto x = input[sample];
                output[sample] = processSample(x, static_cast<int>(numChannels));
            }
        }
    }
    
    /** Process an individual sample */
    template <typename T>
    T processSample(T input, int numChannels)
    {
        return filterData(input, numChannels);
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
        kBypass,
        kClipOutput
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
    
    /** One method to change any parameter. */
    void setParameter(ParameterId parameter, float parameterValue);
    
private:
    
    /** Member variables */
    float mCurrentSampleRate, mQ, mCutoff, mGain, mRawGain, twoPi;
    bool mGlobalBypass, mClipOutput;
    
     /** Variables for the Z filter equations */
    double mGCoeff, mRCoeff, mRCoeff2, mK, mInversion;
    
     /** Filter type switch */
    FilterType mType;
    
     /** Q mode switch */
    QType mQType;
    
     /** state variables (z^-1) */
    std::vector<double> mZ1, mZ2;
    
    /** Generic method holding the DSP */
    float filterData(float dataToFilter, int numCh);
    
    /** Convert the gain if needed */
    void setGain(float value);
    
    /** Get the different Q-Fators*/
    float getShelfQ(float value) const;
    float getPeakQ(float value) const;
};
}

#endif /* SVFilter_h */
