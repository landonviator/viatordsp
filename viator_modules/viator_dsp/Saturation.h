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
                
                output[sample] = processSample(input[sample] * viator_utils::utils::dbToGain(mRawGainDB.getNextValue()));
            }
        }
    }
    
    /** Process an individual sample */
    SampleType processSample(SampleType input) noexcept
    {
        // Get the saturation and soft clip it with gain compensation
        switch(mDistortionType)
        {
            case DistortionType::kHard: return hardClipData(input); break;
            case DistortionType::kSaturation: return saturateData(input); break;
            case DistortionType::kTube: return tubeDistortion(input); break;
            case DistortionType::kTransformer: return transformerDis(input); break;
        }
    }
    

    /** Hard Clip */
    SampleType hardClipData(SampleType dataToClip)
    {
        /** Hard Clipping algorithim*/
        if (std::abs(dataToClip) >= mThresh)
        {
            dataToClip *= mThresh / std::abs(dataToClip);
        }
            
        return dataToClip;
    }
    
    /** Saturation */
    SampleType saturateData(SampleType dataToSaturate)
    {
        /** preamp param needs to be between 0 dB and 6 dB for this saturation algorithm*/
        const float newGain = juce::jmap(mRawGainDB.getNextValue(), 0.0f, 20.0f, 0.0f, 6.0f);
        
        float next_drive = dataToSaturate * juce::Decibels::decibelsToGain(newGain);
        
        if (next_drive < 0.5)
        {
            next_drive = 0.5;
        }
        
        const float x_n = dataToSaturate * next_drive;
        
        const auto saturation = 2.0 * x_n / (1.0 + x_n * x_n);
        
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
    
    /** Transformer Clip */
    SampleType transformerDis(SampleType dataToClip)
    {
        /** TODO */
        // add proportional lowshelf that is driven by the input drive
        
        return piDivisor * std::atan(dataToClip);
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
};
} // namespace viator_dsp

#endif /* Saturation.h */

