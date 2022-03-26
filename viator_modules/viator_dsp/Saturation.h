#ifndef Saturation_h
#define Saturation_h

#include "../Common/Common.h"

namespace viator_dsp
{
template <typename SampleType>
class Saturation
{
public:
    
    /** Creates an uninitialised clipper. Call prepare() before first use. */
    Saturation();
    
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
                
                output[sample] = processSample(input[sample]);
            }
        }
        
        if (mDistortionType == DistortionType::kTransformer)
        {
            tapeFilter.process(context);
        }
    }
    
    /** Process an individual sample */
    SampleType processSample(SampleType input) noexcept
    {
        switch(mDistortionType)
        {
            case DistortionType::kHard: return hardClipData(input); break;
            case DistortionType::kSaturation: return saturateData(input); break;
            case DistortionType::kTube: return tubeDistortion(input); break;
            case DistortionType::kTransformer: return tapeOverdrive(input); break;
        }
    }
    

    /** Hard Clip */
    SampleType hardClipData(SampleType dataToClip)
    {
        dataToClip *= viator_utils::utils::dbToGain(mRawGainDB.getNextValue());
                                                    
        if (std::abs(dataToClip) >= mThresh)
        {
            dataToClip *= mThresh / std::abs(dataToClip);
        }
            
        return dataToClip;
    }
    
    /** Saturation */
    SampleType saturateData(SampleType dataToSaturate)
    {
        auto x = dataToSaturate * viator_utils::utils::dbToGain(mRawGainDB.getNextValue());
                                                                
        auto saturation = x * (1.0 - std::abs(x) / 4.0);
        return saturation;
    }
    
    /** Soft Clip */
    SampleType softClipData(SampleType dataToClip)
    {
        return std::atan(dataToClip);
    }
    
    /** Tube Clip */
    SampleType tubeDistortion(SampleType dataToClip)
    {
        dataToClip *= viator_utils::utils::dbToGain(mRawGainDB.getNextValue());
                                                    
        dataToClip += 0.1;
                
        if (dataToClip < 0.0)
        {
            dataToClip = softClipData(dataToClip);
        }
                
        else
        {
            dataToClip = hardClipData(dataToClip);
        }
                
        dataToClip -= 0.1;
            
        return softClipData(dataToClip);
    }
    
    /** Tape Overdrive */
    SampleType tapeOverdrive(SampleType dataToClip)
    {
        dataToClip *= viator_utils::utils::dbToGain(mRawGainDB.getNextValue());
                                                    
        return piDivisor * std::tanh(dataToClip) * juce::Decibels::decibelsToGain(6.0 + -mRawGainDB.getNextValue() * 0.75);
    }
    
    /** Different clipper types*/
    enum class DistortionType
    {
        kHard,
        kSaturation,
        kTube,
        kTransformer
    };
    
    /** The parameters of this module. */
    enum class ParameterId
    {
        kPreamp,
        kSampleRate,
        kThresh,
        kBypass
    };
    
        
    void setParameter(ParameterId parameter, SampleType parameterValue);
    void setDistortionType(DistortionType distortionType);
    
private:
    
    // Member variables
    bool mGlobalBypass;
    juce::SmoothedValue<float> mRawGainDB;
    float mCurrentSampleRate, mThresh, mRawGain;
    
    DistortionType mDistortionType;
    
    // Expressions
    static constexpr float piDivisor = 2.0 / juce::MathConstants<float>::pi;
    
    // DSP
    viator_dsp::SVFilter<float> tapeFilter;
};
} // namespace viator_dsp

#endif /* Saturation.h */

