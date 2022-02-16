#ifndef HardClipper_h
#define HardClipper_h

#include "../Common/Common.h"

namespace viator_dsp
{
class HardClipper
{
public:
    
    /** Creates an uninitialised filter. Call prepare() before first use. */
    HardClipper();
    
    /** Initialises the filter. */
    void prepare(const juce::dsp::ProcessSpec& spec);
    
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
                
                auto x = input[sample] * viator_utils::utils::dbToGain(mRawGain.getNextValue());
                    
                if (std::abs(x) > 1.0)
                {
                    x *= 1.0 / std::abs(x);
                }
    
                output[sample] = x;
            }
        }
    }
    
    /** Process an individual sample */
    template <typename SampleType>
    SampleType processSample(SampleType input) noexcept
    {
        if (mGlobalBypass) return input;
        
        input *= viator_utils::utils::dbToGain(mRawGain.getNextValue());
        
        if (std::abs(input) > 1.0)
        {
            input *= 1.0 / std::abs(input);
        }
        
        return input;
    }
    
    /** The parameters of this module. */
    enum class ParameterId
    {
        kPreamp,
        kSampleRate,
        kBypass
    };
        
    /** One method to change any parameter. */
    void setParameter(ParameterId parameter, float parameterValue);
    
private:
    
    // Member variables
    float mCurrentSampleRate;
    juce::SmoothedValue<float> mRawGain;
    bool mGlobalBypass;
};
}

#endif /* HardClipper_h */
