#include "Compressor.h"

namespace viator_dsp
{

template <typename SampleType>
void Compressor<SampleType>::prepareModule (const juce::dsp::ProcessSpec& spec)
{
    samplerate = spec.sampleRate;
    
    hpFilter.prepare(spec);
    hpFilter.setType(juce::dsp::LinkwitzRileyFilter<SampleType>::Type::highpass);
    hpFilter.setCutoffFrequency(hpCutoff);
    
    inputGain.reset(samplerate, 0.02);
    outputGain.reset(samplerate, 0.02);
    mix.reset(samplerate, 0.02);
}

template <typename SampleType>
void Compressor<SampleType>::reset()
{

}

template <typename SampleType>
void Compressor<SampleType>::setParameters(SampleType newThresh, SampleType newRatio, SampleType newAttack, SampleType newRelease, SampleType newKnee, SampleType hpf)
{
    threshold = newThresh;
    ratio = newRatio;
    
    if (compressorType == CompressorType::kVca)
    {
        attack = newAttack;
        release = newRelease + 35.0;
    }

    else
    {
        attack = newAttack + 250.0;
        release = newRelease + 250.0;
    }
    
    knee = newKnee;
    kneeScaled = std::tanh(knee * (3.14 / 2.0));
    thresholdWithKnee = threshold - juce::Decibels::gainToDecibels(kneeScaled);
    hpCutoff = hpf;
    
    alphaAttack = std::exp(-std::log(9) / (samplerate * (attack / 1000.0f)));
    alphaRelease = std::exp(-std::log(9) / (samplerate * (release / 1000.0f)));
}

template <typename SampleType>
void Compressor<SampleType>::setInputGain(SampleType newGain)
{
    inputGain.setTargetValue(juce::Decibels::decibelsToGain(newGain));
}

template <typename SampleType>
void Compressor<SampleType>::setOutputGain(SampleType newGain)
{
    outputGain.setTargetValue(juce::Decibels::decibelsToGain(newGain));
}

template <typename SampleType>
void Compressor<SampleType>::setMix(SampleType newMix)
{
    newMix *= 0.01;
    mix.setTargetValue(newMix);
}

template <typename SampleType>
void Compressor<SampleType>::setCompressorType(CompressorType newCompressorType)
{
    compressorType = newCompressorType;
}

//==============================================================================
template class Compressor<float>;
template class Compressor<double>;

} // namespace viator_dsp
