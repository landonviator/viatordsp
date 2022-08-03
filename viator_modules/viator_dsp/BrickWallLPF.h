#ifndef BrickWallLPF_h
#define BrickWallLPF_h

#include "../Common/Common.h"

namespace viator_dsp
{
template <typename SampleType>
class BrickWallLPF
{
public:
    
    BrickWallLPF();
    
    void prepare(const juce::dsp::ProcessSpec& spec) noexcept;
    
    void processBuffer(juce::AudioBuffer<float>& buffer)
    {
        auto channelBuffers = buffer.getArrayOfWritePointers();
            
        for (auto sample {0}; sample < buffer.getNumSamples(); sample++)
        {
            for (auto channel {0}; channel < buffer.getNumChannels(); channel++)
            {
                if (channel == 0)
                {
                    channelBuffers[channel][sample] = _lpfSignalLeft1.processSample(channelBuffers[channel][sample]);
                    channelBuffers[channel][sample] = _lpfSignalLeft2.processSample(channelBuffers[channel][sample]);
                    channelBuffers[channel][sample] = _lpfSignalLeft3.processSample(channelBuffers[channel][sample]);
                }

                if (channel == 1)
                {
                    channelBuffers[channel][sample] = _lpfSignalRight1.processSample(channelBuffers[channel][sample]);
                    channelBuffers[channel][sample] = _lpfSignalRight2.processSample(channelBuffers[channel][sample]);
                    channelBuffers[channel][sample] = _lpfSignalRight3.processSample(channelBuffers[channel][sample]);
                }
            }
        }
    }
    
    SampleType processSample(SampleType input, int channel)
    {
        _lpfSignalLeftCoefficientsArray = juce::dsp::FilterDesign<float>::designIIRLowpassHighOrderButterworthMethod (_cutoff.getNextValue(), _sampleRate, 6);
        _lpfSignalRightCoefficientsArray = juce::dsp::FilterDesign<float>::designIIRLowpassHighOrderButterworthMethod (_cutoff.getNextValue(), _sampleRate, 6);
        
        if (channel == 0)
        {
            float leftSignal;
            leftSignal = _lpfSignalLeft1.processSample(input);
            leftSignal = _lpfSignalLeft2.processSample(leftSignal);
            leftSignal = _lpfSignalLeft3.processSample(leftSignal);
            return leftSignal;
        }

        else if (channel == 1)
        {
            float rightSignal;
            rightSignal = _lpfSignalRight1.processSample(input);
            rightSignal = _lpfSignalRight2.processSample(rightSignal);
            rightSignal = _lpfSignalRight3.processSample(rightSignal);
            return rightSignal;
        }
        
        else
        {
            return input;
        }
    }
    
    void setCutoff(SampleType cutoff);
    
private:
    double _lpfCutoffFrequency;
    float _sampleRate;
    juce::dsp::IIR::Filter<float> _lpfSignalLeft1;
    juce::dsp::IIR::Filter<float> _lpfSignalLeft2;
    juce::dsp::IIR::Filter<float> _lpfSignalLeft3;
    juce::dsp::IIR::Filter<float> _lpfSignalRight1;
    juce::dsp::IIR::Filter<float> _lpfSignalRight2;
    juce::dsp::IIR::Filter<float> _lpfSignalRight3;
    juce::ReferenceCountedArray<juce::dsp::IIR::Coefficients<float>> _lpfSignalLeftCoefficientsArray;
    juce::ReferenceCountedArray<juce::dsp::IIR::Coefficients<float>> _lpfSignalRightCoefficientsArray;
    float _cutoffMult = 0.45;
    
    juce::SmoothedValue<float> _cutoff;
};
}

#endif /* BrickWallLPF_hpp */
