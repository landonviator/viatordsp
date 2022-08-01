#ifndef BitCrusher_hpp
#define BitCrusher_hpp

#include "../Common/Common.h"

namespace viator_dsp
{
template <typename SampleType>
class BitCrusher
{
public:
    
    /** Creates an uninitialised clipper. Call prepare() before first use. */
    BitCrusher();
    
    /** Initialises the clipper. */
    void prepare(const juce::dsp::ProcessSpec& spec) noexcept;
    
    void reset() noexcept;
    
    void processBuffer(juce::AudioBuffer<float>& buffer)
    {
        auto data = buffer.getArrayOfWritePointers();
                
        for (int sample = 0; sample < buffer.getNumSamples(); ++sample)
        {
            for (int ch = 0; ch < buffer.getNumChannels(); ++ch)
            {
                {
                    data[ch][sample] = processSample(data[ch][sample], ch);
                }
            }
        }
    }
    
    /** Process an individual sample */
    SampleType processSample(SampleType input, int ch) noexcept
    {
        return input * 2;
    }
    
private:
    juce::SmoothedValue<float> _drive;
    juce::SmoothedValue<float> _mix;
    juce::SmoothedValue<float> _output;
    float _currentSampleRate;
};
}
#endif /* BitCrusher_hpp */
