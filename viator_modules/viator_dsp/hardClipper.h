#ifndef HardClipper_h
#define HardClipper_h

#include "viator_dsp.h"

namespace viator_dsp
{
class HardClipper
{
public:
    
    HardClipper()
    : mCurrentSampleRate (44100.0f), mGlobalBypass (false)
    {
        mRawGain.setTargetValue(0.0);
    }
    
    void prepare(const juce::dsp::ProcessSpec& spec)
    {
        mCurrentSampleRate = spec.sampleRate;
        mRawGain.reset(mCurrentSampleRate, 0.02);
    }
    
    void processBlock(const juce::dsp::AudioBlock<float>& block)
    {
        for (int sample = 0; sample < block.getNumSamples(); ++sample)
        {
            for (int ch = 0; ch < block.getNumChannels(); ++ch)
            {
                float* data = block.getChannelPointer(ch);
                float input = data[sample] * viator_utils::utils::dbToGain(mRawGain.getNextValue());
                
                if (!type)
                {
                    if (std::abs(input) > 1.0)
                    {
                        input *= 1.0 / std::abs(input);
                    }
                }
                
                else
                {
                    if (std::abs(input) > 1.0)
                    {
                        input = 1.0;
                    }
                }
                
                data[sample] = input;
            }
        }
    }
    
    template <typename T>
    T processSample(T input)
    {
        if (std::abs(input) > 1.0)
        {
            input *= 1.0 / std::abs(input);
        }
        
        return input;
    }
    
    enum class ParameterId
    {
        kPreamp,
        kSampleRate,
        kType,
        kBypass
    };
        
    void setParameter(ParameterId parameter, float parameterValue)
    {
        switch (parameter)
        {
            case ParameterId::kPreamp: mRawGain.setTargetValue(parameterValue); break;
            case ParameterId::kSampleRate: mCurrentSampleRate = parameterValue; break;
            case ParameterId::kType: type = parameterValue; break;
            case ParameterId::kBypass: mGlobalBypass = static_cast<bool>(parameterValue);
        }
    }
    
private:
    
    // Member variables
    float mCurrentSampleRate;
    juce::SmoothedValue<float> mRawGain;
    bool mGlobalBypass;
    bool type = false;
};
}

#endif /* svfilter_h */
