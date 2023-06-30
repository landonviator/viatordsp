#include "Tube.h"

namespace viator_dsp
{

template <typename SampleType>
Tube<SampleType>::Tube()
{
}

template <typename SampleType>
void Tube<SampleType>::prepare (const juce::dsp::ProcessSpec& spec)
{
    using lrFilter = juce::dsp::LinkwitzRileyFilter<double>;
    using svFilter = viator_dsp::SVFilter<double>;
    
    jassert (spec.sampleRate > 0);
    jassert (spec.numChannels > 0);
    
    sampleRate = spec.sampleRate;
    
    saturation.reset(sampleRate, 0.02);
    rawSaturation.reset(sampleRate, 0.02);
    
    dcFilter.reset();
    dcFilter.prepare(spec);
    dcFilter.setType(lrFilter::Type::highpass);
    dcFilter.setCutoffFrequency(dcBlockerCutoff);
    
    lowShelfFilter.prepare(spec);
    lowShelfFilter.setParameter(svFilter::ParameterId::kType, svFilter::FilterType::kLowShelf);
    lowShelfFilter.setParameter(svFilter::ParameterId::kQType, svFilter::QType::kParametric);
    lowShelfFilter.setParameter(svFilter::ParameterId::kCutoff, lowShelfCutoff);
    lowShelfFilter.setParameter(svFilter::ParameterId::kGain, lowShelfGain);
    lowShelfFilter.setParameter(svFilter::ParameterId::kQ, 0.7);
    
    millerFilter.reset();
    millerFilter.prepare(spec);
    millerFilter.setType(lrFilter::Type::lowpass);
    millerFilter.setCutoffFrequency(millerCutoff);
}

template <typename SampleType>
void Tube<SampleType>::reset()
{
}

template <typename SampleType>
SampleType Tube<SampleType>::processSample(SampleType input, SampleType channel) noexcept
{
    auto xn = input;
    auto yn = input * inputGain;
    
    //yn = millerFilter.processSample(channel, yn);
    
    yn = getValeGridConduction(yn);
    
    yn = getValeEmulation(yn);

    yn = dcFilter.processSample(channel, yn);
    
    //yn = lowShelfFilter.processSample(yn, channel);
    
    auto outputMix = (1.0 - mix) * xn + yn * mix;
    
    return outputMix * outputGain;
}

template <typename SampleType>
SampleType Tube<SampleType>::getValeGridConduction(SampleType input)
{
    auto xn = input;
    
    if (xn > 0.0)
    {
        auto clipDelta = xn - gridConductionThreshold;
        
        clipDelta = std::fmax(clipDelta, 0.0);
        
        auto compressionFactor = 0.4473253 + 0.541584 * std::exp(-0.3241584 * clipDelta);
        
        return compressionFactor * xn;
    }
    
    else
    {
        return xn;
    }
    
}

template <typename SampleType>
SampleType Tube<SampleType>::getValeEmulation(SampleType input)
{
    auto xn = input;
    
    xn += bias;

    if (xn > 0.0)
    {
        xn = std::tanh(saturation.getNextValue() * xn) / std::tanh(saturation.getNextValue());
    }

    xn -= bias;
    
    return xn * juce::Decibels::decibelsToGain(-rawSaturation.getNextValue());
}

template <typename SampleType>
void Tube<SampleType>::setDrive(SampleType newDrive)
{
    saturation.setTargetValue(juce::Decibels::decibelsToGain(newDrive));
    rawSaturation.setTargetValue(newDrive * 0.5);
}

template <typename SampleType>
void Tube<SampleType>::setInputGain(SampleType newGain)
{
    inputGain = juce::Decibels::decibelsToGain(newGain);
}

template <typename SampleType>
void Tube<SampleType>::setOutputGain(SampleType newGain)
{
    outputGain = juce::Decibels::decibelsToGain(newGain);
}

template <typename SampleType>
void Tube<SampleType>::setBias(SampleType newBias)
{
    bias = newBias;
}

template <typename SampleType>
void Tube<SampleType>::setMix(SampleType newMix)
{
    mix = newMix;
}

//==============================================================================
template class Tube<float>;
template class Tube<double>;

} // namespace viator_dsp
