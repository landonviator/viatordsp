#include "BrickWallLPF.h"

template <typename SampleType>
viator_dsp::BrickWallLPF<SampleType>::BrickWallLPF()
{
}

template <typename SampleType>
void viator_dsp::BrickWallLPF<SampleType>::prepare(const juce::dsp::ProcessSpec& spec) noexcept
{
    _sampleRate = spec.sampleRate;
    
    // Aliasing filters
    //each L/R pair is 12dB/oct
    _lpfSignalLeft1.reset();
    _lpfSignalLeft2.reset();
    _lpfSignalLeft3.reset();
    _lpfSignalRight1.reset();
    _lpfSignalRight2.reset();
    _lpfSignalRight3.reset();
    
    _lpfSignalLeft1.prepare(spec);
    _lpfSignalLeft2.prepare(spec);
    _lpfSignalLeft3.prepare(spec);
    _lpfSignalRight1.prepare(spec);
    _lpfSignalRight2.prepare(spec);
    _lpfSignalRight3.prepare(spec);

    _lpfCutoffFrequency = spec.sampleRate * _cutoffMult;
    _lpfSignalLeftCoefficientsArray = juce::dsp::FilterDesign<float>::designIIRLowpassHighOrderButterworthMethod (_lpfCutoffFrequency, spec.sampleRate, 6);
    _lpfSignalRightCoefficientsArray = juce::dsp::FilterDesign<float>::designIIRLowpassHighOrderButterworthMethod (_lpfCutoffFrequency, spec.sampleRate, 6);

    //each L/R pair is 12dB/oct
    _lpfSignalLeft1.coefficients = _lpfSignalLeftCoefficientsArray.getObjectPointer(0);
    _lpfSignalLeft2.coefficients = _lpfSignalLeftCoefficientsArray.getObjectPointer(1);
    _lpfSignalLeft3.coefficients = _lpfSignalLeftCoefficientsArray.getObjectPointer(2);
    _lpfSignalRight1.coefficients = _lpfSignalRightCoefficientsArray.getObjectPointer(0);
    _lpfSignalRight2.coefficients = _lpfSignalRightCoefficientsArray.getObjectPointer(1);
    _lpfSignalRight3.coefficients = _lpfSignalRightCoefficientsArray.getObjectPointer(2);
}

template <typename SampleType>
void viator_dsp::BrickWallLPF<SampleType>::setCutoff(SampleType cutoff)
{
    _lpfSignalLeftCoefficientsArray = juce::dsp::FilterDesign<float>::designIIRLowpassHighOrderButterworthMethod (cutoff, _sampleRate, 6);
    _lpfSignalRightCoefficientsArray = juce::dsp::FilterDesign<float>::designIIRLowpassHighOrderButterworthMethod (cutoff, _sampleRate, 6);
}

template class viator_dsp::BrickWallLPF<float>;
template class viator_dsp::BrickWallLPF<double>;
