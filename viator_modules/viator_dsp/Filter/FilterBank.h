#ifndef FilterBank_h
#define FilterBank_h

#if JUCE_USE_SIMD
 
namespace harvest_dsp
{
template <typename T>
static T* toBasePointer (juce::dsp::SIMDRegister<T>* r) noexcept
{
    return reinterpret_cast<T*> (r);
}
 
constexpr auto registerSize = juce::dsp::SIMDRegister<float>::size();

template <typename SampleType>
auto prepareChannelPointers (const juce::dsp::AudioBlock<SampleType>& block, juce::dsp::AudioBlock<float>& zero)
{
    std::array<SampleType*, registerSize> result {};

    for (size_t ch = 0; ch < result.size(); ++ch)
        result[ch] = (ch < block.getNumChannels() ? block.getChannelPointer (ch) : zero.getChannelPointer (ch));

    return result;
}

template <typename SampleType>
class FilterBank
{
public:
    
    FilterBank();
    
    void prepare(const juce::dsp::ProcessSpec& spec) noexcept;
    
    void reset() noexcept;
    
    void process (const juce::dsp::ProcessContextReplacing<float>& context)
    {
        jassert (context.getInputBlock().getNumSamples()  == context.getOutputBlock().getNumSamples());
        jassert (context.getInputBlock().getNumChannels() == context.getOutputBlock().getNumChannels());
 
        const auto& input  = context.getInputBlock(); // [9]
        const auto numSamples = (int) input.getNumSamples();
        
        inputModule.process(context);
 
        auto inChannels = prepareChannelPointers (input, _zero); // [10]
 
        using Format = juce::AudioData::Format<juce::AudioData::Float32, juce::AudioData::NativeEndian>;
 
        juce::AudioData::interleaveSamples (juce::AudioData::NonInterleavedSource<Format> { inChannels.data(),                                 registerSize, },
                                            juce::AudioData::InterleavedDest<Format>      { toBasePointer (_interleaved.getChannelPointer (0)), registerSize },
                                            numSamples); // [11]
 
        for (auto& filter : _filterBank)
        {
            filter->process (juce::dsp::ProcessContextReplacing<juce::dsp::SIMDRegister<float>> (_interleaved));
        }
 
        auto outChannels = prepareChannelPointers (context.getOutputBlock(), _zero); // [13]
 
        juce::AudioData::deinterleaveSamples (juce::AudioData::InterleavedSource<Format>  { toBasePointer (_interleaved.getChannelPointer (0)), registerSize },
                                              juce::AudioData::NonInterleavedDest<Format> { outChannels.data(),                                registerSize },
                                              numSamples); // [14]
        
        outputModule.process(context);
    }
    
    void updateFilter(int bandToUpdate, float newGain);
    int getNumFilters(){return 32;};
    float getCutoff(int index);
    void setInputGain(float newGain);
    void setOutputGain(float newGain);
    
private:
    float _sampleRate {0.0f};
    float _blockSize;
    
    juce::dsp::IIR::Coefficients<float>::Ptr
    _iirCoefficients1, _iirCoefficients2, _iirCoefficients3, _iirCoefficients4, _iirCoefficients5,
    _iirCoefficients6, _iirCoefficients7, _iirCoefficients8, _iirCoefficients9, _iirCoefficients10,
    _iirCoefficients11, _iirCoefficients12, _iirCoefficients13, _iirCoefficients14, _iirCoefficients15,
    _iirCoefficients16, _iirCoefficients17, _iirCoefficients18, _iirCoefficients19, _iirCoefficients20,
    _iirCoefficients21, _iirCoefficients22, _iirCoefficients23, _iirCoefficients24, _iirCoefficients25,
    _iirCoefficients26, _iirCoefficients27, _iirCoefficients28, _iirCoefficients29, _iirCoefficients30,
    _iirCoefficients31, _iirCoefficients32;
    
    std::vector<juce::dsp::IIR::Coefficients<float>::Ptr> _coefficients;
    
    std::unique_ptr<juce::dsp::IIR::Filter<juce::dsp::SIMDRegister<float>>>
    _band1, _band2, _band3, _band4, _band5, _band6, _band7, _band8, _band9, _band10,
    _band11, _band12, _band13, _band14, _band15, _band16, _band17, _band18, _band19, _band20,
    _band21, _band22, _band23, _band24, _band25, _band26, _band27, _band28, _band29, _band30,
    _band31, _band32;
    
    std::vector<std::unique_ptr<juce::dsp::IIR::Filter<juce::dsp::SIMDRegister<float>>>> _filterBank;
 
    juce::dsp::AudioBlock<juce::dsp::SIMDRegister<float>> _interleaved;
    juce::dsp::AudioBlock<float> _zero;
 
    juce::HeapBlock<char> _interleavedBlockData, _zeroData;
    
private:
    
    juce::dsp::Gain<float> inputModule;
    juce::dsp::Gain<float> outputModule;
    
    std::vector<float> _cutoffs
    {
        20.0f, 25.0f, 31.5f, 40.0f, 50.0f, 63.0f, 80.0, 88.0f, 100.0f, 125.0f,
        150.0f, 200.0f, 240.0f, 315.0f, 400.0f, 500.0f, 630.0, 750.0f, 920.0f, 1200.0f,
        1500.0f, 2200.0f, 2500.0f, 3100.0f, 4000.0f, 5000.0f, 6600.0f, 8000.0f, 10000.0, 12500.0f,
        15000.0f, 20000.0f
    };
};
}
#endif /* FilterBank_h */
#endif

