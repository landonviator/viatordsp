namespace viator_dsp
{

template <typename SampleType>
FilterBank<SampleType>::FilterBank()
{
    
}

template <typename SampleType>
void FilterBank<SampleType>::prepare(const juce::dsp::ProcessSpec& spec) noexcept
{
    _sampleRate = spec.sampleRate;
    _blockSize = spec.maximumBlockSize;
    
    _coefficient = juce::dsp::IIR::Coefficients<float>::makeLowPass(_sampleRate, 1000.0);
    _filter.reset(new juce::dsp::IIR::Filter<juce::dsp::SIMDRegister<float>>(_coefficient));

    _interleaved = juce::dsp::AudioBlock<juce::dsp::SIMDRegister<float>> (_interleavedBlockData, 1, _blockSize);
    _zero        = juce::dsp::AudioBlock<float> (_zeroData, juce::dsp::SIMDRegister<float>::size(), _blockSize);

    _zero.clear();
    
    auto monoSpec = spec;
    monoSpec.numChannels = 1;
    
    _filter->prepare (spec);
}

template class viator_dsp::FilterBank<float>;
template class viator_dsp::FilterBank<double>;

} // namespace

