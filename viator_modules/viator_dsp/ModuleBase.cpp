#include "ModuleBase.h"

namespace viator_dsp
{

template <typename SampleType>
void ModuleBase<SampleType>::prepareModule (const juce::dsp::ProcessSpec& spec)
{
    _spec = spec;
    sampleRate = spec.sampleRate;
    
    inputGain.reset(sampleRate, 0.02);
    outputGain.reset(sampleRate, 0.02);
    mix.reset(sampleRate, 0.02);
}

template <typename SampleType>
void ModuleBase<SampleType>::setInputGain(SampleType newGain)
{
    inputGain.setTargetValue(juce::Decibels::decibelsToGain(newGain));
}

template <typename SampleType>
void ModuleBase<SampleType>::setOutputGain(SampleType newGain)
{
    outputGain.setTargetValue(juce::Decibels::decibelsToGain(newGain));
}

template <typename SampleType>
void ModuleBase<SampleType>::setMix(SampleType newMix)
{
    newMix *= 0.01;
    mix.setTargetValue(newMix);
}

//==============================================================================
template class ModuleBase<float>;
template class ModuleBase<double>;

} // namespace viator_dsp
