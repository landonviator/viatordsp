#ifndef Tube_h
#define Tube_h

#include <JuceHeader.h>

namespace viator_dsp
{

template <typename SampleType>
class Tube
{
public:
    Tube();

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
    
    SampleType processSample(SampleType input, SampleType channel) noexcept;
    
    void setInputGain(SampleType newGain);
    void setOutputGain(SampleType newGain);
    void setDrive(SampleType newDrive);
    void setBias(SampleType newBias);
    void setMix(SampleType newMix);

private:
    juce::dsp::LinkwitzRileyFilter<double> dcFilter;
    juce::dsp::LinkwitzRileyFilter<double> millerFilter;
    viator_dsp::SVFilter<double> lowShelfFilter;
    
private:
    
    SampleType getValeGridConduction(SampleType input);
    SampleType getValeEmulation(SampleType input);
    
private:
    double sampleRate = 44100.0;
    
    // --- for emulation of LF shelf from cathod bypass cap
    double lowShelfCutoff = 100.0;
    double lowShelfGain = 1.0;
    
    // --- for emulation of output HPF for dc blocking
    double dcBlockerCutoff = 10.0;
    
    // --- for emulation of Miller cap that reduces HF
    double millerCutoff = 10000.0;
    
    // --- no idea
    double integratorFc = 5.0;
    
    // --- clip and threshold points
    double clipPositive = 4.0;
    double clipNegative = -1.5;
    double gridConductionThreshold = 0.25;
    
    // --- to scale dc offset amount
    double dcShiftCoeff = 0.0;
    
    // --- drive
    juce::SmoothedValue<float> saturation = 0.0;
    juce::SmoothedValue<float> rawSaturation = 0.0;
    
    // --- IO
    double inputGain = 1.5;
    double outputGain = 1.0;
    
    // --- return data???
    double dcOffsetDetected = 0.0;
    
    // --- effect mix
    double mix = 0.1;
    
    // --- bias
    double bias = 0.0;
    
    // --- diode coefficients
    float analogCoeffA {0.1};
    float analogCoeffB {8.0};
    float analogCoeffC {0.0253};
};

} // namespace viator_dsp

#endif /* Tube_h */
