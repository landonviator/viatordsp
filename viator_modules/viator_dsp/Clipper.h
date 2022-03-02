#ifndef Clipper_h
#define Clipper_h

#include "../Common/Common.h"

namespace viator_dsp
{
template <typename SampleType>
class Clipper
{
public:
    
    /** Creates an uninitialised clipper. Call prepare() before first use. */
    Clipper();
    
    /** Initialises the clipper. */
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
            for (size_t sample = 0; sample < len; ++sample)
            {
                auto* input = inBlock.getChannelPointer (channel);
                auto* output = outBlock.getChannelPointer (channel);
                
                auto x = input[sample] * viator_utils::utils::dbToGain(mRawGain.getNextValue());
                output[sample] = processSample(x);
            }
        }
    }
    
    /** Process an individual sample */
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
    
    /** Different clipper types*/
    enum class ClipType
    {
        kHard,
        kSoft,
        kDiode
    };
        
    /** One method to change any parameter. */
    void setParameter(ParameterId parameter, SampleType parameterValue);
    void setClipperType(ClipType clipType);
    
private:
    
    // Member variables
    bool mGlobalBypass;
    juce::SmoothedValue<float> mRawGain;
    float mCurrentSampleRate, mThresh, mPiDivisor, mGainDB;
    
    // Methods
    SampleType hardClipData(SampleType dataToClip, const float thresh);
    SampleType softClipData(SampleType dataToClip);
    SampleType diodeClipper(SampleType dataToClip);
    
    ClipType mClipType;
};
} // namespace viator_dsp

#endif /* Clipper_h */
