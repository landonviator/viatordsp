#include "BrickWallLPF.h"

viator_dsp::BrickWallLPF::BrickWallLPF()
{
}

void viator_dsp::BrickWallLPF::prepare(const juce::dsp::ProcessSpec& spec) noexcept
{
    _sampleRate = spec.sampleRate;
    
    _lpfCutoffFrequency = spec.sampleRate * 0.4;
    _lpfSignalLeftCoefficientsArray = juce::dsp::IIR::Coefficients<float>::makeLowPass(_sampleRate, _lpfCutoffFrequency);
    _lpfSignalRightCoefficientsArray = juce::dsp::IIR::Coefficients<float>::makeLowPass(_sampleRate, _lpfCutoffFrequency);
    
    // Aliasing filters
    //each L/R pair is 12dB/oct
    _lpfSignalLeft1.reset(new juce::dsp::IIR::Filter<juce::dsp::SIMDRegister<float>> (_lpfSignalLeftCoefficientsArray));
    _lpfSignalLeft2.reset(new juce::dsp::IIR::Filter<juce::dsp::SIMDRegister<float>> (_lpfSignalLeftCoefficientsArray));
    _lpfSignalLeft3.reset(new juce::dsp::IIR::Filter<juce::dsp::SIMDRegister<float>> (_lpfSignalLeftCoefficientsArray));
    _lpfSignalRight1.reset(new juce::dsp::IIR::Filter<juce::dsp::SIMDRegister<float>> (_lpfSignalRightCoefficientsArray));
    _lpfSignalRight2.reset(new juce::dsp::IIR::Filter<juce::dsp::SIMDRegister<float>> (_lpfSignalRightCoefficientsArray));
    _lpfSignalRight3.reset(new juce::dsp::IIR::Filter<juce::dsp::SIMDRegister<float>> (_lpfSignalRightCoefficientsArray));
    
    interleaved = juce::dsp::AudioBlock<juce::dsp::SIMDRegister<float>> (interleavedBlockData, 1, spec.maximumBlockSize);
    zero        = juce::dsp::AudioBlock<float> (zeroData, juce::dsp::SIMDRegister<float>::size(), spec.maximumBlockSize); // [6]

    zero.clear();
    
    auto monoSpec = spec;
    monoSpec.numChannels = 1;
    
    _lpfSignalLeft1->prepare(monoSpec);
    _lpfSignalLeft2->prepare(monoSpec);
    _lpfSignalLeft3->prepare(monoSpec);
    _lpfSignalRight1->prepare(monoSpec);
    _lpfSignalRight2->prepare(monoSpec);
    _lpfSignalRight3->prepare(monoSpec);
}

void viator_dsp::BrickWallLPF::updateCutoff(double newCutoff)
{
    //*_lpfSignalLeftCoefficientsArray = *juce::dsp::IIR::Coefficients<float>::makeLowPass(_sampleRate, newCutoff);
    //*_lpfSignalRightCoefficientsArray = *juce::dsp::IIR::Coefficients<float>::makeLowPass(_sampleRate, newCutoff);
}
