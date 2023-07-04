#include "Compressor.h"

namespace viator_dsp
{

template <typename SampleType>
void Compressor<SampleType>::reset()
{
    samplerate = viator_dsp::ModuleBase<SampleType>::getSampleRate();
}

template <typename SampleType>
void Compressor<SampleType>::setParameters(SampleType newThresh, SampleType newRatio, SampleType newAttack, SampleType newRelease, SampleType newKnee)
{
    threshold = newThresh;
    ratio = newRatio;
    attack = newAttack;
    release = newRelease;
    knee = newKnee;
    kneeScaled = 2.0 / 3.14 * std::atan(knee);
    thresholdWithKnee = threshold - juce::Decibels::gainToDecibels(kneeScaled);
    
    alphaAttack = std::exp(-std::log(9) / (samplerate * attack));
    alphaRelease = std::exp(-std::log(9) / (samplerate * release));
}

//==============================================================================
template class Compressor<float>;
template class Compressor<double>;

} // namespace viator_dsp
