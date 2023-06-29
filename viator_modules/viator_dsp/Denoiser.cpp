#include "Denoiser.h"

namespace viator_dsp
{

template <typename SampleType>
Denoiser<SampleType>::Denoiser()
{
}

template <typename SampleType>
void Denoiser<SampleType>::prepare (const juce::dsp::ProcessSpec& spec)
{
    jassert (spec.sampleRate > 0);
    jassert (spec.numChannels > 0);
    
    sampleRate = spec.sampleRate;
    
    levelGain.reset(sampleRate, 0.02);
    
    mbModule.prepare(spec);
    mbModule.setLowCutoff(200.0);
    mbModule.setMidCutoff(6000.0);
    mbModule.setHighCutoff(10000.0);
    
    midCompressorModule.prepare(spec);
    midCompressorModule.setRatio(2.0f);
    midCompressorModule.setAttack(5.0f);
    midCompressorModule.setRelease(5.0f);
    midCompressorModule.setThreshold(0.0f);
    
    expanderModule.prepare(spec);
    expanderModule.setThreshold(0.0);
    expanderModule.setAttack(50.0);
    expanderModule.setRelease(150.0);
    
    volumeModule.prepare(spec);
    volumeModule.setRampDurationSeconds(0.02);
    volumeModule.setGainDecibels(0.0f);
}

template <typename SampleType>
void Denoiser<SampleType>::reset()
{
}

template <typename SampleType>
void Denoiser<SampleType>::setNoiseReduction(SampleType newNoiseThresh)
{
    noiseReduction = newNoiseThresh;
}

template <typename SampleType>
void Denoiser<SampleType>::setMBBands(SampleType lowCutoff, SampleType midCutoff, SampleType highCutoff)
{
    mbModule.setLowCutoff(lowCutoff);
    mbModule.setMidCutoff(midCutoff);
    mbModule.setHighCutoff(highCutoff);
}

template <typename SampleType>
void Denoiser<SampleType>::setCompressorParams(SampleType newRatio, SampleType newThresh, SampleType newAttack, SampleType newRelease)
{
    midCompressorModule.setRatio(newRatio);
    midCompressorModule.setThreshold(newThresh);
    midCompressorModule.setAttack(newAttack);
    midCompressorModule.setRelease(newRelease);
}

template <typename SampleType>
void Denoiser<SampleType>::setNoiseRelease(SampleType newNoiseStrength)
{
    expanderModule.setRatio(newNoiseStrength);
}

template <typename SampleType>
void Denoiser<SampleType>::setVolume(SampleType newVolume)
{
    volumeModule.setGainDecibels(newVolume);
}

template <typename SampleType>
SampleType Denoiser<SampleType>::processSample(SampleType input, SampleType channel) noexcept
{
    auto xn = mbModule.getLowMidBand();

    xn = getCompressedBand(xn, channel);

    return mbModule.getLowBand() + xn + mbModule.getMidBand() + mbModule.getHighBand();
}

template <typename SampleType>
SampleType Denoiser<SampleType>::getCompressedBand(SampleType input, SampleType channel)
{
    return midCompressorModule.processSample(channel, input);
}

template <typename SampleType>
void Denoiser<SampleType>::calculateRMS(const juce::dsp::AudioBlock<const float>& block)
{
    int channelLen = static_cast<int>(block.getNumChannels());
    int sampleLen = static_cast<int>(block.getNumSamples());
    
    rmsBuffer.setSize(channelLen, sampleLen);
    block.copyTo(rmsBuffer);
    
    auto rms = rmsBuffer.getRMSLevel(0, 0, rmsBuffer.getNumSamples());
    auto rmsDB = juce::Decibels::gainToDecibels(rms);
    
    if (rmsDB < levelGain.getCurrentValue())
    {
        levelGain.setTargetValue(rmsDB);
    }

    else
    {
        levelGain.setCurrentAndTargetValue(rmsDB);
    }
    
    currentRMS = levelGain.getNextValue();
}

//==============================================================================
template class Denoiser<float>;
template class Denoiser<double>;

} // namespace viator_dsp
