#include "Compressor.h"

namespace viator_dsp
{

template <typename SampleType>
void Compressor<SampleType>::reset()
{
    samplerate = viator_dsp::ModuleBase<SampleType>::getSampleRate();
}

template <typename SampleType>
void Compressor<SampleType>::setParameters(SampleType newThresh, SampleType newRatio, SampleType newAttack, SampleType newRelease)
{
    threshold = newThresh;
    ratio = newRatio;
    attack = newAttack;
    release = newRelease;
    
    alphaAttack = std::exp(-std::log(9) / (samplerate * attack));
    alphaRelease = std::exp(-std::log(9) / (samplerate * release));
}

//==============================================================================
template class Compressor<float>;
template class Compressor<double>;

} // namespace viator_dsp
