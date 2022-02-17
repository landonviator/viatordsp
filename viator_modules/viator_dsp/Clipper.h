#ifndef Clipper_h
#define Clipper_h

#include "../Common/Common.h"

namespace viator_dsp
{
class Clipper
{
public:
    
    /** Creates an uninitialised filter. Call prepare() before first use. */
    Clipper();
    
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
                output[sample] = processSample(x);
            }
        }
    }
    
    /** Process an individual sample */
    template <typename SampleType>
    SampleType processSample(SampleType input) noexcept
    {
        switch(mClipType)
        {
            case ClipType::kHard: return hardClipData(input * mGainDB, mThresh); break;
            case ClipType::kSoft: return softClipData(input * mGainDB); break;
            case ClipType::kDiode: return diodeClipper(input * mGainDB); break;
        }
    }
    
    /** The parameters of this module. */
    enum class ParameterId
    {
        kPreamp,
        kSampleRate,
        kThresh,
        kBypass
    };
    
    enum class ClipType
    {
        kHard,
        kSoft,
        kDiode
    };
        
    /** One method to change any parameter. */
    void setParameter(ParameterId parameter, float parameterValue);
    void setClipperType(ClipType clipType);
    
private:
    
    // Member variables
    bool mGlobalBypass;
    juce::SmoothedValue<float> mRawGain;
    float mCurrentSampleRate, mThresh, mPiDivisor, mGainDB;
    
    // Methods
    float hardClipData(float dataToClip, const float thresh);
    float softClipData(float dataToClip);
    float diodeClipper(float dataToClip);
    
    ClipType mClipType;
};
}

#endif /* Clipper_h */
