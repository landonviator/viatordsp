#ifndef Denoiser_h
#define Denoiser_h

#include <JuceHeader.h>

namespace viator_dsp
{

template <typename SampleType>
class Denoiser
{
public:
    Denoiser();

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
        
        calculateRMS(inputBlock);
        auto level = levelGain.getNextValue() * noiseReduction;
        midCompressorModule.setThreshold(level);
        
        for (size_t channel = 0; channel < numChannels; ++channel)
        {
            for (size_t sample = 0; sample < numSamples; ++sample)
            {
                auto* input = inputBlock.getChannelPointer (channel);
                auto* output = outputBlock.getChannelPointer (channel);
                
                mbModule.processSample(input[sample], static_cast<int>(channel));
                output[sample] = processSample(input[sample], channel);
            }
        }
        
        expanderModule.process(context);
        volumeModule.process(context);
    }
    
    SampleType processSample(SampleType input, SampleType channel) noexcept;
    
    void setMBBands(SampleType lowCutoff, SampleType midCutoff, SampleType highCutoff);
    
    SampleType getCompressedBand(SampleType input, SampleType channel);
    void setCompressorParams(SampleType newRatio, SampleType newThresh, SampleType newAttack, SampleType newRelease);
    
    void setNoiseReduction(SampleType newNoiseReduction);
    void setNoiseRelease(SampleType newNoiseRelease);
    
    void setVolume(SampleType newVolume);

private:
    juce::AudioBuffer<float> rmsBuffer;
    viator_dsp::MultiBandProcessor<float> mbModule;
    juce::dsp::Compressor<float> midCompressorModule;
    viator_dsp::Expander<float> expanderModule;
    juce::dsp::Gain<float> volumeModule;
    
private:
    void calculateRMS(const juce::dsp::AudioBlock<const float>& block);
    
private:
    double sampleRate = 44100.0;
    double noiseReduction = 4.0;
    double currentRMS = 0.0;
    double noiseRelease = 1.0;
    juce::SmoothedValue<double> levelGain = -60.0;
};

} // namespace viator_dsp

#endif /* Denoiser_h */
