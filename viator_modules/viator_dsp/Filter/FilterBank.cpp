namespace harvest_dsp
{

template <typename SampleType>
FilterBank<SampleType>::FilterBank()
{
    _filterBank.push_back(std::move(_band1));
    _filterBank.push_back(std::move(_band2));
    _filterBank.push_back(std::move(_band3));
    _filterBank.push_back(std::move(_band4));
    _filterBank.push_back(std::move(_band5));
    _filterBank.push_back(std::move(_band6));
    _filterBank.push_back(std::move(_band7));
    _filterBank.push_back(std::move(_band8));
    _filterBank.push_back(std::move(_band9));
    _filterBank.push_back(std::move(_band10));
    
    _filterBank.push_back(std::move(_band11));
    _filterBank.push_back(std::move(_band12));
    _filterBank.push_back(std::move(_band13));
    _filterBank.push_back(std::move(_band14));
    _filterBank.push_back(std::move(_band15));
    _filterBank.push_back(std::move(_band16));
    _filterBank.push_back(std::move(_band17));
    _filterBank.push_back(std::move(_band18));
    _filterBank.push_back(std::move(_band19));
    _filterBank.push_back(std::move(_band20));
    
    _filterBank.push_back(std::move(_band21));
    _filterBank.push_back(std::move(_band22));
    _filterBank.push_back(std::move(_band23));
    _filterBank.push_back(std::move(_band24));
    _filterBank.push_back(std::move(_band25));
    _filterBank.push_back(std::move(_band26));
    _filterBank.push_back(std::move(_band27));
    _filterBank.push_back(std::move(_band28));
    _filterBank.push_back(std::move(_band29));
    _filterBank.push_back(std::move(_band30));
    
    _filterBank.push_back(std::move(_band31));
    _filterBank.push_back(std::move(_band32));
    
    _coefficients.push_back(std::move(_iirCoefficients1));
    _coefficients.push_back(std::move(_iirCoefficients2));
    _coefficients.push_back(std::move(_iirCoefficients3));
    _coefficients.push_back(std::move(_iirCoefficients4));
    _coefficients.push_back(std::move(_iirCoefficients5));
    _coefficients.push_back(std::move(_iirCoefficients6));
    _coefficients.push_back(std::move(_iirCoefficients7));
    _coefficients.push_back(std::move(_iirCoefficients8));
    _coefficients.push_back(std::move(_iirCoefficients9));
    _coefficients.push_back(std::move(_iirCoefficients10));
    
    _coefficients.push_back(std::move(_iirCoefficients11));
    _coefficients.push_back(std::move(_iirCoefficients12));
    _coefficients.push_back(std::move(_iirCoefficients13));
    _coefficients.push_back(std::move(_iirCoefficients14));
    _coefficients.push_back(std::move(_iirCoefficients15));
    _coefficients.push_back(std::move(_iirCoefficients16));
    _coefficients.push_back(std::move(_iirCoefficients17));
    _coefficients.push_back(std::move(_iirCoefficients18));
    _coefficients.push_back(std::move(_iirCoefficients19));
    _coefficients.push_back(std::move(_iirCoefficients20));
    
    _coefficients.push_back(std::move(_iirCoefficients21));
    _coefficients.push_back(std::move(_iirCoefficients22));
    _coefficients.push_back(std::move(_iirCoefficients23));
    _coefficients.push_back(std::move(_iirCoefficients24));
    _coefficients.push_back(std::move(_iirCoefficients25));
    _coefficients.push_back(std::move(_iirCoefficients26));
    _coefficients.push_back(std::move(_iirCoefficients27));
    _coefficients.push_back(std::move(_iirCoefficients28));
    _coefficients.push_back(std::move(_iirCoefficients29));
    _coefficients.push_back(std::move(_iirCoefficients30));
    
    _coefficients.push_back(std::move(_iirCoefficients31));
    _coefficients.push_back(std::move(_iirCoefficients32));
}

template <typename SampleType>
void FilterBank<SampleType>::prepare(const juce::dsp::ProcessSpec& spec) noexcept
{
    _sampleRate = spec.sampleRate;
    _blockSize = spec.maximumBlockSize;
    
    inputModule.prepare(spec);
    inputModule.setRampDurationSeconds(0.02);
    outputModule.prepare(spec);
    outputModule.setRampDurationSeconds(0.02);
    
    for (int i = 0; i < _filterBank.size(); ++i)
    {
        _coefficients[i] = juce::dsp::IIR::Coefficients<float>::makePeakFilter(_sampleRate, _cutoffs[i], 0.1f, 1.0f);
        _filterBank[i].reset (new juce::dsp::IIR::Filter<juce::dsp::SIMDRegister<float>> (_coefficients[i]));
    }

    _interleaved = juce::dsp::AudioBlock<juce::dsp::SIMDRegister<float>> (_interleavedBlockData, 1, _blockSize);
    _zero        = juce::dsp::AudioBlock<float> (_zeroData, juce::dsp::SIMDRegister<float>::size(), _blockSize);

    _zero.clear();

    auto monoSpec = spec;
    monoSpec.numChannels = 1;
    
    for (auto& filter : _filterBank)
    {
        filter->prepare (spec);
    }
}

template <typename SampleType>
void FilterBank<SampleType>::reset() noexcept
{

}

template <typename SampleType>
void FilterBank<SampleType>::updateFilter(int bandToUpdate, float newGain)
{
    if (_sampleRate == 0.0f)
        return;
    
    if (_coefficients[bandToUpdate] == nullptr)
        return;
    
    jassert(bandToUpdate > -1 && bandToUpdate < 33);
    
    auto gain = juce::Decibels::decibelsToGain(newGain);
    
    *_coefficients[bandToUpdate] = *juce::dsp::IIR::Coefficients<float>::makePeakFilter(_sampleRate, _cutoffs[bandToUpdate], 0.7, gain);
}

template <typename SampleType>
float FilterBank<SampleType>::getCutoff(int index)
{
    return _cutoffs[index];
}

template <typename SampleType>
void FilterBank<SampleType>::setInputGain(float newGain)
{
    inputModule.setGainDecibels(newGain);
}

template <typename SampleType>
void FilterBank<SampleType>::setOutputGain(float newGain)
{
    outputModule.setGainDecibels(newGain);
}

} // namespace

template class harvest_dsp::FilterBank<float>;
template class harvest_dsp::FilterBank<double>;
