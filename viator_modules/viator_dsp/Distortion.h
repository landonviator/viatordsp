#ifndef Clipper_h
#define Clipper_h

#include "../Common/Common.h"

namespace viator_dsp
{
template <typename SampleType>
class Distortion
{
public:
    
    /** Creates an uninitialised clipper. Call prepare() before first use. */
    Distortion();
    
    /** Initialises the clipper. */
    void prepare(const juce::dsp::ProcessSpec& spec) noexcept;
    
    void reset() noexcept;
    
    /** Processes the input and output buffers supplied in the processing context. */
    template <typename ProcessContext>
    void process (const ProcessContext& context) noexcept
    {
        if (!_globalEnabled)
        {
            return;
        }
        
        auto&& inBlock  = context.getInputBlock();
        auto&& outBlock = context.getOutputBlock();

        jassert (inBlock.getNumChannels() == outBlock.getNumChannels());
        jassert (inBlock.getNumSamples() == outBlock.getNumSamples());

        auto len         = inBlock.getNumSamples();
        auto numChannels = inBlock.getNumChannels();


        for (size_t channel = 0; channel < numChannels; ++channel)
        {
            for (size_t sample = 0; sample < len; ++sample)
            {
                auto* input = inBlock.getChannelPointer (channel);
                auto* output = outBlock.getChannelPointer (channel);
                
                output[sample] = processSample(input[sample]);
            }
        }
    }
    
    /** Process an individual sample */
    SampleType processSample(SampleType input) noexcept
    {
        switch(m_clipType)
        {
            case ClipType::kHard: return hardClipData(input, _thresh.getNextValue()); break;
            case ClipType::kSoft: return softClipData(input); break;
            case ClipType::kDiode: return diodeClipper(input); break;
            case ClipType::kFuzz: return processFuzz(input); break;
        }
    }
    
    /** Hard clip data */
    SampleType hardClipData(SampleType dataToClip, SampleType thresh = 1.0)
    {
        dataToClip *= _rawGain.getNextValue();
        
        if (std::abs(dataToClip) >= 1.0)
        {
            dataToClip *= 1.0 / std::abs(dataToClip);
        }
        
        return dataToClip;
    }

    /** Soft Clip */
    SampleType softClipData(SampleType dataToClip)
    {
        /** Soft Clipping algorithim*/
        dataToClip *= _rawGain.getNextValue();
        return _piDivisor * std::atan(dataToClip);
    }

    /** Diode Clip */
    SampleType diodeClipper(SampleType dataToClip)
    {
        /** Diode Clipping algorithim*/
        dataToClip *= _rawGain.getNextValue();
        return softClipData(0.315 * (juce::dsp::FastMathApproximations::exp(0.1 * dataToClip / (_diodeTerm)) - 1.0));
    }
    
    /** Fuzz Clip */
    SampleType processFuzz(SampleType dataToClip)
    {
        /** Fuzz algorithim*/
        auto input = dataToClip;
        
        auto fuzz = input / std::abs(input) * (1.0 - std::pow(juce::MathConstants<float>::euler, (_rawGain.getNextValue() * (input * input)) / std::abs(input)));
        
        return dataToClip * 0.5 + softClipData(fuzz) * 0.5;
    }
    
    /** The parameters of this module. */
    enum class ParameterId
    {
        kPreamp,
        kThresh,
        kBypass
    };
    
    /** Different clipper types*/
    enum class ClipType
    {
        kHard,
        kSoft,
        kDiode,
        kFuzz
        //kTube,
        //kSaturation
    };
        
    /** One method to change any parameter. */
    void setDrive(SampleType newDrive);
    void setThresh(SampleType newThresh);
    void setEnabled(SampleType isEnabled);
    void setClipperType(ClipType clipType);
    
private:
    
    // Member variables
    bool _globalEnabled;
    juce::SmoothedValue<float> _rawGain;
    juce::SmoothedValue<float> _gainDB;
    juce::SmoothedValue<float> _thresh;
    float _currentSampleRate;
    
    // Expressions
    static constexpr float _diodeTerm = 2.0 * 0.0253;
    static constexpr float _piDivisor = 2.0 / juce::MathConstants<float>::pi;
    
    ClipType m_clipType;
};
} // namespace viator_dsp

#endif /* Clipper_h */
