#include "Expander.h"

namespace viator_dsp
{

template <typename SampleType>
Expander<SampleType>::Expander()
{
    update();
}

template <typename SampleType>
void Expander<SampleType>::prepare (const juce::dsp::ProcessSpec& spec)
{
    jassert (spec.sampleRate > 0);
    jassert (spec.numChannels > 0);

    sampleRate = spec.sampleRate;

    envelopeFilter.prepare (spec);

    update();
    reset();
}

template <typename SampleType>
void Expander<SampleType>::reset()
{
    envelopeFilter.reset();
}

template <typename SampleType>
SampleType Expander<SampleType>::processSample (int channel, SampleType inputValue)
{
    // Ballistics filter with peak rectifier
    auto env = envelopeFilter.processSample (channel, inputValue);

    // VCA
    auto gain = (env < threshold) ? std::pow (env * thresholdInverse, ratioInverse - static_cast<SampleType> (1.0))
                                  : std::pow (env * thresholdInverse, ratioInverse);

    // Output
    return gain * inputValue;
}

template <typename SampleType>
void Expander<SampleType>::update()
{
    threshold = juce::Decibels::decibelsToGain (thresholddB, static_cast<SampleType> (-200.0));
    thresholdInverse = static_cast<SampleType> (1.0) / threshold;
    ratioInverse     = static_cast<SampleType> (1.0) / ratio;

    envelopeFilter.setAttackTime (attackTime);
    envelopeFilter.setReleaseTime (releaseTime);
}

#pragma mark Setters
template <typename SampleType>
void Expander<SampleType>::setThreshold (SampleType newThreshold)
{
    thresholddB = newThreshold;
    update();
}

template <typename SampleType>
void Expander<SampleType>::setRatio (SampleType newRatio)
{
    jassert (newRatio <= static_cast<SampleType> (1.0));

    ratio = newRatio;
    update();
}

template <typename SampleType>
void Expander<SampleType>::setAttack (SampleType newAttack)
{
    attackTime = newAttack;
    update();
}

template <typename SampleType>
void Expander<SampleType>::setRelease (SampleType newRelease)
{
    releaseTime = newRelease;
    update();
}

} // namespace viator_dsp

template class viator_dsp::Expander<float>;
template class viator_dsp::Expander<double>;
