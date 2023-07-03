#ifndef ModuleBase_h
#define ModuleBase_h

#include <JuceHeader.h>

namespace viator_dsp
{

template <typename SampleType>
class ModuleBase
{
public:
    ModuleBase(){};
    virtual ~ModuleBase(){};

    void prepare (const juce::dsp::ProcessSpec& spec);

    void reset();

    /** Processes the input and output samples supplied in the processing context. */
    template <typename ProcessContext>
    void process (const ProcessContext& context) noexcept
    {
        const auto& inputBlock = context.getInputBlock();
        auto& outputBlock      = context.getOutputBlock();
        const auto numChannels = outputBlock.getNumChannels();
        const auto numSamples  = outputBlock.getNumSamples();

        jassert (inputBlock.getNumChannels() == numChannels);
        jassert (inputBlock.getNumSamples()  == numSamples);

        if (context.isBypassed)
        {
            outputBlock.copyFrom (inputBlock);
            return;
        }
        
        for (size_t channel = 0; channel < numChannels; ++channel)
        {
            for (size_t sample = 0; sample < numSamples; ++sample)
            {
                auto* input = inputBlock.getChannelPointer (channel);
                auto* output = outputBlock.getChannelPointer (channel);
                
                output[sample] = processSample(input[sample], channel);
            }
        }
    }
    
    virtual SampleType processSample(SampleType input) = 0;
    
    void setInputGain(SampleType newGain);
    void setOutputGain(SampleType newGain);
    void setMix(SampleType newMix);

private:
    float sampleRate = 44100.0f;
    juce::SmoothedValue<SampleType> inputGain = 1.0;
    juce::SmoothedValue<SampleType> outputGain = 1.0;
    juce::SmoothedValue<SampleType> mix = 0.0;
};

} // namespace viator_dsp

#endif /* Tube_h */
