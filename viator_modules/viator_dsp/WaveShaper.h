
#ifndef WaveShaper_h
#define WaveShaper_h

#include "../Common/Common.h"

namespace viator_dsp
{
class WaveShaper
{
public:
    
    /** Creates an uninitialised clipper. Call prepare() before first use. */
    WaveShaper();
    
    /** Initialises the clipper. */
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
                
                auto x = input[sample];
                
                output[sample] = processSample(x);
            }
        }
    }
    
    /** Process an individual sample */
    template <typename SampleType>
    SampleType processSample(SampleType input) noexcept
    {
        return processCubicShaper(input * mGainDB, 5.0, 8.956, -5.37);
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
    bool mGlobalBypass;
    juce::SmoothedValue<float> mRawGain;
    float mCurrentSampleRate, mGainDB;
    
    // Methods
    float processCubicShaper(float dataToShape, int coeff3, int coeff2, int coeff1);
};
} // namespace viator_dsp

#endif /* Clipper_h */
