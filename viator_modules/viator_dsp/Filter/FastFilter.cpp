namespace viator_dsp
{

template <typename SampleType>
FastFilter<SampleType>::FastFilter()
{
    
}

template <typename SampleType>
void FastFilter<SampleType>::prepare(const juce::dsp::ProcessSpec& spec) noexcept
{
    _sampleRate = spec.sampleRate;
    _blockSize = spec.maximumBlockSize;
    
    _coefficient = juce::dsp::IIR::Coefficients<float>::makeLowPass(_sampleRate, 1000.0);
    _filter.reset(new juce::dsp::IIR::Filter<juce::dsp::SIMDRegister<float>>(_coefficient));

    _interleaved = juce::dsp::AudioBlock<juce::dsp::SIMDRegister<float>> (_interleavedBlockData, 1, _blockSize);
    _zero        = juce::dsp::AudioBlock<float> (_zeroData, juce::dsp::SIMDRegister<float>::size(), _blockSize);

    _interleaved.clear();
    _zero.clear();
    
    auto monoSpec = spec;
    monoSpec.numChannels = 1;
    
    _filter->prepare (spec);
}

template <typename SampleType>
void FastFilter<SampleType>::updateParameters(SampleType newCutoff, SampleType newQ, SampleType newGain)
{
    *_coefficient = *juce::dsp::IIR::Coefficients<float>::makeLowPass(_sampleRate, newCutoff);
}

template class viator_dsp::FastFilter<float>;
template class viator_dsp::FastFilter<double>;

} // namespace

