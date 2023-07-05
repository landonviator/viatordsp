#include "Compressor.h"

namespace viator_dsp
{

template <typename SampleType>
void Compressor<SampleType>::reset()
{
    samplerate = viator_dsp::ModuleBase<SampleType>::getProcessSpec().sampleRate;
    
    hpFilter.prepare(viator_dsp::ModuleBase<SampleType>::getProcessSpec());
    hpFilter.setType(juce::dsp::LinkwitzRileyFilter<SampleType>::Type::highpass);
    hpFilter.setCutoffFrequency(hpCutoff);
}

template <typename SampleType>
void Compressor<SampleType>::setParameters(SampleType newThresh, SampleType newRatio, SampleType newAttack, SampleType newRelease, SampleType newKnee, SampleType hpf)
{
    threshold = newThresh;
    ratio = newRatio;
    attack = newAttack;
    release = newRelease;
    knee = newKnee;
    kneeScaled = std::tan(knee * (3.14 / 2.0));
    thresholdWithKnee = threshold - juce::Decibels::gainToDecibels(kneeScaled);
    hpCutoff = hpf;
    
    alphaAttack = std::exp(-std::log(9) / (samplerate * (attack / 1000.0f)));
    alphaRelease = std::exp(-std::log(9) / (samplerate * (release / 1000.0f)));
}

//==============================================================================
template class Compressor<float>;
template class Compressor<double>;

} // namespace viator_dsp
