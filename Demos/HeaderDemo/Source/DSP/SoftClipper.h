/*
  ==============================================================================

    SoftClipper.h
    Created: 28 Apr 2022 6:08:28pm
    Author:  Landon Viator

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>

template <typename SampleType>
class SoftClipper
{
public:
    
    SoftClipper();
    
    void prepare(juce::dsp::ProcessSpec& spec) noexcept;
    
    void reset() noexcept;
    
    template <typename ProcessContext>
    void process(const ProcessContext& context) noexcept
    {
        auto&& inBlock  = context.getInputBlock();
        auto&& outBlock = context.getOutputBlock();

        jassert (inBlock.getNumChannels() == outBlock.getNumChannels());
        jassert (inBlock.getNumSamples() == outBlock.getNumSamples());

        auto len         = inBlock.getNumSamples();
        auto numChannels = inBlock.getNumChannels();
        
        for (size_t channel = 0; channel < numChannels; ++channel)
        {
            auto *input = inBlock.getChannelPointer(channel);
            auto *output = outBlock.getChannelPointer(channel);
            
            for (size_t sample = 0; sample < len; ++sample)
            {
                output[sample] = processSample(input[sample]);
            }
        }
    }
    
    SampleType processSample(SampleType newInput)
    {
        return piDivisor * std::atan(newInput * mDrive.getNextValue());
    }
    
    void setDrive(SampleType newDrive);
    
private:
    
    float mSampleRate;
    juce::SmoothedValue<float> mDrive;
    
    static constexpr float piDivisor = 2.0 / juce::MathConstants<float>::pi;
    
};
