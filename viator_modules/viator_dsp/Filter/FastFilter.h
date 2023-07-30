#ifndef FilterBank_h
#define FilterBank_h

#if JUCE_USE_SIMD
 
namespace viator_dsp
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
class FastFilter
{
public:
    
    FastFilter();
    
    void prepare(const juce::dsp::ProcessSpec& spec) noexcept;
    
    void process (const juce::dsp::ProcessContextReplacing<float>& context)
    {
        jassert (context.getInputBlock().getNumSamples()  == context.getOutputBlock().getNumSamples());
        jassert (context.getInputBlock().getNumChannels() == context.getOutputBlock().getNumChannels());
 
        const auto& input  = context.getInputBlock(); // [9]
        const auto numSamples = (int) input.getNumSamples();
        
        auto inChannels = prepareChannelPointers (input, _zero); // [10]
 
        using Format = juce::AudioData::Format<juce::AudioData::Float32, juce::AudioData::NativeEndian>;
 
        juce::AudioData::interleaveSamples (juce::AudioData::NonInterleavedSource<Format> { inChannels.data(),                                 registerSize, },
                                            juce::AudioData::InterleavedDest<Format>      { toBasePointer (_interleaved.getChannelPointer (0)), registerSize },
                                            numSamples); // [11]
 
        _filter->process (juce::dsp::ProcessContextReplacing<juce::dsp::SIMDRegister<float>> (_interleaved));
 
        auto outChannels = prepareChannelPointers (context.getOutputBlock(), _zero); // [13]
 
        juce::AudioData::deinterleaveSamples (juce::AudioData::InterleavedSource<Format>  { toBasePointer (_interleaved.getChannelPointer (0)), registerSize },
                                              juce::AudioData::NonInterleavedDest<Format> { outChannels.data(),                                registerSize },
                                              numSamples); // [14]
    }
    
    void updateParameters(SampleType newCutoff, SampleType newQ, SampleType newGain);
    
private:
    float _sampleRate {0.0f};
    float _blockSize;
    
    juce::dsp::IIR::Coefficients<float>::Ptr _coefficient;
    std::unique_ptr<juce::dsp::IIR::Filter<juce::dsp::SIMDRegister<float>>> _filter;
 
    juce::dsp::AudioBlock<juce::dsp::SIMDRegister<float>> _interleaved;
    juce::dsp::AudioBlock<float> _zero;
 
    juce::HeapBlock<char> _interleavedBlockData, _zeroData;
    
private:
    
};
}
#endif /* FilterBank_h */
#endif

