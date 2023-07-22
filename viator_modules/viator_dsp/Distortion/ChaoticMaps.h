#ifndef ChaoticMaps_h
#define ChaoticMaps_h

#include "../../Common/Common.h"

namespace viator_dsp
{
template <typename SampleType>
class ChaoticMaps
{
public:
    
    /** Creates an uninitialised clipper. Call prepare() before first use. */
    ChaoticMaps();
    
    /** Initialises the clipper. */
    void prepare(const juce::dsp::ProcessSpec& spec) noexcept;
    
    void reset() noexcept;
    
    /** Processes the input and output buffers supplied in the processing context. */
    template <typename ProcessContext>
    void process (const ProcessContext& context) noexcept
    {
        const auto& inputBlock = context.getInputBlock();
        auto& outputBlock      = context.getOutputBlock();
        const auto numChannels = outputBlock.getNumChannels();
        const auto numSamples  = outputBlock.getNumSamples();

        jassert (inputBlock.getNumChannels() == numChannels);
        jassert (inputBlock.getNumSamples()  == numSamples);

        for (size_t channel = 0; channel < numChannels; ++channel)
        {
            auto* outputSamples = outputBlock.getChannelPointer (channel);
            
            for (size_t i = 0; i < numSamples; ++i)
            {
                outputSamples[i] = std::sin(x) * _volume;
                
                if (i % static_cast<int>(_chaosFrequency) == 0)
                {
                    const double new_x = y + 1 - a * (x * x);
                    const double new_y = b * x;
                    x = new_x;
                    y = new_y;
                }
            }
        }
    }
    
    void processMap (SampleType index) noexcept;
    void processBlock (juce::dsp::AudioBlock<float> &block) noexcept;
    
    void setChaosFrequency (SampleType newChaosFrequency) {_chaosFrequency = newChaosFrequency;};
    
    SampleType getCurrentChaosValue () {return std::sin(x);};
    
private:
    
    const double a = 1.4;      // Hénon map parameter
    const double b = 0.2;      // Hénon map parameter
    double x;                   // current x coordinate
    double y;                   // current y coordinate
    SampleType _chaosFrequency = 1;
    SampleType _volume = 0.01;
    
};
} // namespace viator_dsp

#endif /* ChaoticMaps_h */
