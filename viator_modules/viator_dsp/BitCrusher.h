#ifndef BitCrusher_h
#define BitCrusher_h

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
                
                auto rateDivide = static_cast<int> (_resample.getNextValue());
                
                // Reduce bit depth
                float totalQLevels = std::powf(2, _bitDepth.getNextValue());
                
                // Wet signal
                float _wetSignal = data[ch][sample];
                
                _wetSignal = 0.5 * _wetSignal + 0.5;
                
                _wetSignal = totalQLevels * _wetSignal;
                
                _wetSignal = (std::round(_wetSignal) / totalQLevels) * 2 - 1;
                
                float remainder = std::fmodf(_wetSignal, 1.0 / totalQLevels);
                
                _wetSignal -= remainder;
                
                if (rateDivide > 1)
                {
                    if (sample % rateDivide != 0)
                    {
                        _wetSignal = data[ch][sample - sample % rateDivide];
                    }
                }
                
                data[ch][sample] = _wetSignal;
            }
        }
    }
    
    /** Process an individual sample */
    SampleType processSample(SampleType input, int ch, int sample) noexcept
    {
        setResampleRate(_resample.getNextValue() + (_currentSampleRate - _resample.getNextValue()));
        
        // Dry signal
        float _drySignal = input;
        
        // Wet signal
        float _wetSignal = input;
        
        // Reduce bit depth
        float totalQLevels = std::powf(2, _bitDepth.getNextValue());
        
        _wetSignal = 0.5 * _wetSignal + 0.5;
        
        _wetSignal = totalQLevels * _wetSignal;
        
        _wetSignal = (std::round(_wetSignal) / totalQLevels) * 2 - 1;
        
        return _wetSignal;
    }
    
    void setBitDepth(SampleType newBitDepth);
    void setResampledRate(SampleType newResampleRate);
    
private:
    juce::SmoothedValue<float> _drive;
    juce::SmoothedValue<float> _bitDepth;
    juce::SmoothedValue<float> _mix;
    juce::SmoothedValue<float> _output;
    juce::SmoothedValue<float> _resample;
    float _currentSampleRate;
    int _previousSample = 0;
    float _rateDivide;
    void setResampleRate(SampleType newResampleRate);
    
    juce::NormalisableRange<float> _bitRateRange;
};
}
#endif /* BitCrusher_hpp */
