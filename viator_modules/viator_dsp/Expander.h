#ifndef Expander_h
#define Expander_h

#include "../Common/Common.h"

namespace viator_dsp
{

template <typename SampleType>
class Expander
{
public:
    
    /** Constructor. */
    Expander();

    /** Sets the threshold in dB of the expander.*/
    void setThreshold (SampleType newThreshold);

    /** Sets the ratio of the expander (must be higher or equal to 1).*/
    void setRatio (SampleType newRatio);

    /** Sets the attack time in milliseconds of the expander.*/
    void setAttack (SampleType newAttack);

    /** Sets the release time in milliseconds of the expander.*/
    void setRelease (SampleType newRelease);

    /** Initialises the processor. */
    void prepare (const juce::dsp::ProcessSpec& spec);

    /** Resets the internal state variables of the processor. */
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
            auto* inputSamples  = inputBlock .getChannelPointer (channel);
            auto* outputSamples = outputBlock.getChannelPointer (channel);

            for (size_t i = 0; i < numSamples; ++i)
                outputSamples[i] = processSample ((int) channel, inputSamples[i]);
        }
    }

    /** Performs the processing operation on a single sample at a time. */
    SampleType processSample (int channel, SampleType inputValue);

private:
    juce::dsp::BallisticsFilter<SampleType> envelopeFilter;
    
private:
    void update();

private:
    SampleType threshold, thresholdInverse, ratioInverse;

    double sampleRate = 44100.0;
    
    SampleType thresholddB = 0.0, ratio = 1.0, attackTime = 1.0, releaseTime = 100.0;
};

} // namespace viator_dsp

#endif /* Expander_h */
