#ifndef BitCrusher_h
#define BitCrusher_h

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
                
//                auto rateDivide = static_cast<int> (_resample.getNextValue());
//
//                // Reduce bit depth
//                float totalQLevels = std::powf(2, _bitDepth.getNextValue());
//
//                // Wet signal
//                float _wetSignal = data[ch][sample];
//
//                _wetSignal = 0.5 * _wetSignal + 0.5;
//
//                _wetSignal = totalQLevels * _wetSignal;
//
//                _wetSignal = (std::round(_wetSignal) / totalQLevels) * 2.0 - 1.0;
//
//                float remainder = std::fmodf(_wetSignal, 1.0 / totalQLevels);
//
//                _wetSignal -= remainder;
//
//                if (rateDivide > 1.0)
//                {
//                    if (sample % rateDivide != 0.0)
//                    {
//                        _wetSignal = data[ch][sample - sample % rateDivide];
//                    }
//                }
                
                auto x = data[ch][sample];
                x = _bitDepth * (static_cast<int>(x / _bitDepth));
                x = _piDivisor * std::atan(x * _drive.getNextValue());
                data[ch][sample] = (1.0 - _mix.getNextValue()) * data[ch][sample] + x * _output.getNextValue() * _mix.getNextValue();
            }
        }
    }
    
    /** Process an individual sample */
    SampleType processSample(SampleType input, int ch, int sample) noexcept
    {
        setResampleRate(_resample.getNextValue() + (_currentSampleRate - _resample.getNextValue()));
        
        // Wet signal
        float _wetSignal = input;
        
        // Reduce bit depth
        float totalQLevels = std::powf(2, _bitDepth);
        
        _wetSignal = 0.5 * _wetSignal + 0.5;
        
        _wetSignal = totalQLevels * _wetSignal;
        
        _wetSignal = (std::round(_wetSignal) / totalQLevels) * 2 - 1;
        
        return _wetSignal;
    }
    
    void setBitDepth(SampleType newBitDepth);
    void setResampledRate(SampleType newResampleRate);
    void setMix(SampleType newMix);
    void setDrive(SampleType newDrive);
    void setVolume(SampleType newVolume);
    
private:
    juce::SmoothedValue<float> _drive;
    float _bitDepth;
    juce::SmoothedValue<float> _mix;
    juce::SmoothedValue<float> _output;
    juce::SmoothedValue<float> _resample;
    float _currentSampleRate;
    int _previousSample = 0;
    float _rateDivide;
    void setResampleRate(SampleType newResampleRate);
    static constexpr float _piDivisor = 2.0 / juce::MathConstants<float>::pi;
    
    juce::NormalisableRange<float> _bitRateRange;
};
}
#endif /* BitCrusher_hpp */
