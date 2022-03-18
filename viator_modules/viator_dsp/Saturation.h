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
                
                output[sample] = processSample(input[sample] * viator_utils::utils::dbToGain(mRawGain.getNextValue()));
            }
        }
    }
    
    /** Process an individual sample */
    SampleType processSample(SampleType input) noexcept
    {
        // Get the saturation and soft clip it with gain compensation
        return softClipData(saturateData(input)) * viator_utils::utils::dbToGain(mRawGain.getNextValue() * -0.5);
    }
    

    /** Saturation */
    SampleType saturateData(SampleType dataToSaturate)
    {
        // Saturation algorithim
        return ( 2.0 * dataToSaturate) / ( 1.0 + std::sqrt(1.0 + std::abs(4.0 * dataToSaturate)));
    }
    
    /** Soft Clip */
    SampleType softClipData(SampleType dataToClip)
    {
        // Soft clip with added gain compensation
        return std::atan(dataToClip) * 1.25;
    }

    /** The parameters of this module. */
    enum class ParameterId
    {
        kPreamp,
        kSampleRate,
        kThresh,
        kBypass
    };
    
        
    /** One method to change any parameter. */
    void setParameter(ParameterId parameter, SampleType parameterValue);
    
private:
    
    // Member variables
    bool mGlobalBypass;
    juce::SmoothedValue<float> mRawGain;
    float mCurrentSampleRate, mThresh, mGainDB;
    
    // Expressions
};
} // namespace viator_dsp

#endif /* Saturation.h */

