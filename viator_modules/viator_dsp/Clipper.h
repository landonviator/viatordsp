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
                
                output[sample] = processSample(input[sample] * viator_utils::utils::dbToGain(mRawGain.getNextValue()));
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
    
    /** Hard Clip */
    SampleType hardClipData(SampleType dataToClip, const float thresh)
    {
        /** Hard Clipping algorithim*/
        if (std::abs(dataToClip) > thresh)
        {
            dataToClip *= thresh / std::abs(dataToClip);
        }
        
        return dataToClip;
    }

    /** Soft Clip */
    SampleType softClipData(SampleType dataToClip)
    {
        /** Soft Clipping algorithim*/
        return = mPiDivisor * std::atan(dataToClip);
    }

    /** Diode Clip */
    SampleType diodeClipper(SampleType dataToClip)
    {
        /** Diode Clipping algorithim*/
        return = softClipData(0.315 * (juce::dsp::FastMathApproximations::exp(0.1 * dataToClip / (diodeTerm)) - 1.0));
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
    float mCurrentSampleRate, mThresh, mGainDB;
    
    // Expressions
    static constexpr float diodeTerm = 2.0 * 0.0253;
    static constexpr float mPiDivisor = 2.0 / juce::MathConstants<float>::pi;
    
    ClipType mClipType;
};
} // namespace viator_dsp

#endif /* Clipper_h */
