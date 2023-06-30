#ifndef BrickWallLPF_h
#define BrickWallLPF_h

#include "../Common/Common.h"

namespace viator_dsp
{
class BrickWallLPF
{
public:
    
    BrickWallLPF();
    
    void prepare(const juce::dsp::ProcessSpec& spec) noexcept;
    
    template <typename SampleType>
    auto prepareChannelPointers (const juce::dsp::AudioBlock<SampleType>& block)
    {
        std::array<SampleType*, registerSize> result {};
        
        for (size_t ch = 0; ch < result.size(); ++ch)
            result[ch] = (ch < block.getNumChannels() ? block.getChannelPointer (ch) : zero.getChannelPointer (ch));
        
        return result;
    }
    
    void process(const juce::dsp::ProcessContextReplacing<float> &context)
    {
        jassert (context.getInputBlock().getNumSamples()  == context.getOutputBlock().getNumSamples());
        jassert (context.getInputBlock().getNumChannels() == context.getOutputBlock().getNumChannels());
         
        const auto& input  = context.getInputBlock(); // [9]
        const auto numSamples = (int) input.getNumSamples();
         
        auto inChannels = prepareChannelPointers (input); // [10]
         
        using Format = juce::AudioData::Format<juce::AudioData::Float32, juce::AudioData::NativeEndian>;
         
        juce::AudioData::interleaveSamples (juce::AudioData::NonInterleavedSource<Format> { inChannels.data(),                                 registerSize, },
                                            juce::AudioData::InterleavedDest<Format>      { toBasePointer (interleaved.getChannelPointer (0)), registerSize },
                                              numSamples); // [11]
         
        _lpfSignalLeft1->process (juce::dsp::ProcessContextReplacing<juce::dsp::SIMDRegister<float>> (interleaved));
        _lpfSignalLeft2->process (juce::dsp::ProcessContextReplacing<juce::dsp::SIMDRegister<float>> (interleaved));
        _lpfSignalLeft3->process (juce::dsp::ProcessContextReplacing<juce::dsp::SIMDRegister<float>> (interleaved));
        _lpfSignalRight1->process (juce::dsp::ProcessContextReplacing<juce::dsp::SIMDRegister<float>> (interleaved));
        _lpfSignalRight2->process (juce::dsp::ProcessContextReplacing<juce::dsp::SIMDRegister<float>> (interleaved));
        _lpfSignalRight3->process (juce::dsp::ProcessContextReplacing<juce::dsp::SIMDRegister<float>> (interleaved));
         
        auto outChannels = prepareChannelPointers (context.getOutputBlock()); // [13]
         
        juce::AudioData::deinterleaveSamples (juce::AudioData::InterleavedSource<Format>  { toBasePointer (interleaved.getChannelPointer (0)), registerSize },
                                              juce::AudioData::NonInterleavedDest<Format> { outChannels.data(),                                registerSize },
                                                numSamples); // [14]
    }
    
    void updateCutoff(double newCutoff);
    
private:
    double _lpfCutoffFrequency;
    float _sampleRate;
    std::unique_ptr<juce::dsp::IIR::Filter<juce::dsp::SIMDRegister<float>>> _lpfSignalLeft1;
    std::unique_ptr<juce::dsp::IIR::Filter<juce::dsp::SIMDRegister<float>>> _lpfSignalLeft2;
    std::unique_ptr<juce::dsp::IIR::Filter<juce::dsp::SIMDRegister<float>>> _lpfSignalLeft3;
    std::unique_ptr<juce::dsp::IIR::Filter<juce::dsp::SIMDRegister<float>>> _lpfSignalRight1;
    std::unique_ptr<juce::dsp::IIR::Filter<juce::dsp::SIMDRegister<float>>> _lpfSignalRight2;
    std::unique_ptr<juce::dsp::IIR::Filter<juce::dsp::SIMDRegister<float>>> _lpfSignalRight3;
    juce::dsp::IIR::Coefficients<float>::Ptr _lpfSignalLeftCoefficientsArray;
    juce::dsp::IIR::Coefficients<float>::Ptr _lpfSignalRightCoefficientsArray;
    float _cutoffMult = 0.45;
    
    juce::dsp::AudioBlock<juce::dsp::SIMDRegister<float>> interleaved;
    juce::dsp::AudioBlock<float> zero;
    juce::HeapBlock<char> interleavedBlockData, zeroData;
    
    template <typename T>
    static T* toBasePointer (juce::dsp::SIMDRegister<T>* r) noexcept
    {
        return reinterpret_cast<T*> (r);
    }
    
    static const auto registerSize = juce::dsp::SIMDRegister<float>::size();
};
}

#endif /* BrickWallLPF_hpp */
