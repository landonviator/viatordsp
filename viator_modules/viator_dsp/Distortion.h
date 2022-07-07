#ifndef Distortion_h
#define Distortion_h

#include "../Common/Common.h"
#include "SVFilter.h"

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
                
                output[sample] = processSample(input[sample], channel);
            }
        }
    }
    
    /** Process an individual sample */
    SampleType processSample(SampleType input, int ch) noexcept
    {
        switch(m_clipType)
        {
            case ClipType::kHard: return hardClipData(input, true); break;
            case ClipType::kSoft: return softClipData(input); break;
            case ClipType::kDiode: return processDiode(input); break;
            case ClipType::kFuzz: return processFuzz(input, ch); break;
            case ClipType::kTube: return processTube(input); break;
            case ClipType::kSaturation: return processSaturation(input, false); break;
            case ClipType::kLofi: return processLofi(input, ch); break;
        }
    }
    
    /** Hard clip data */
    SampleType hardClipData(SampleType dataToClip, bool useDrive)
    {
        if (useDrive)
        {
            dataToClip *= _rawGain.getNextValue();
        }
        
        auto ceiling = _ceiling.getNextValue();
        
        // Hard algorithim
        if (std::abs(dataToClip) >= ceiling)
        {
            dataToClip *= ceiling / std::abs(dataToClip);
        }
        
        return dataToClip;
    }

    /** Soft Clip */
    SampleType softClipData(SampleType dataToClip)
    {
        // Soft algorithim
        dataToClip *= _rawGain.getNextValue();
        return _piDivisor * std::atan(dataToClip);
    }

    /** Diode */
    SampleType processDiode(SampleType dataToClip)
    {
        // Diode algorithim
        dataToClip *= _rawGain.getNextValue();
        return softClipData(0.315 * (juce::dsp::FastMathApproximations::exp(0.1 * dataToClip / (_diodeTerm)) - 1.0));
    }
    
    /** Tube */
    SampleType processTube(SampleType dataToClip)
    {
        // Tube algorithim
        dataToClip *= _rawGain.getNextValue();
        
        if (dataToClip >= 0.0)
        {
            dataToClip = hardClipData(dataToClip, false);
        }
        
        else
        {
            dataToClip = softClipData(dataToClip);
        }
        
        return dataToClip;
    }
    
    /** Fuzz */
    SampleType processFuzz(SampleType dataToClip, int channel)
    {
        // Fuzz algorithim
        auto input = m_fuzzFilter.processSample(dataToClip, channel);
        
        auto fuzz = input / std::abs(input) * (1.0 - std::pow(juce::MathConstants<float>::euler, (_rawGain.getNextValue() * (input * input)) / std::abs(input)));
        
        return processTube(fuzz);
    }
    
    
    /** Saturation */
    SampleType processSaturation(SampleType dataToClip, bool light)
    {
        light ? dataToClip *= _rawGain.getNextValue() * 0.1 : dataToClip *= _rawGain.getNextValue();
        
        auto thresh = _thresh.getNextValue();
        
        // Saturation algorithim
        if (dataToClip > thresh)
        {
            dataToClip = thresh + (dataToClip - thresh) / (1.0 + std::pow((( dataToClip - 0.5 ) / thresh), 2.0));
        }
        
        return softClipData(dataToClip);
    }
    
    /** Lofi Distortion */
    SampleType processLofi(SampleType dataToClip, int channel)
    {
        // Bias
        auto bias = 0.05;
        auto wetSignal = dataToClip += bias;
        
        // Lofi algorithim
        if (wetSignal < 0)
        {
            wetSignal *= juce::jmap(_gainDB.getNextValue(), 0.0f, 20.0f, 1.0f, -1.0f);
        }
        
        // Saturate signal
        wetSignal = processSaturation(wetSignal, true);
        
        // Volume compensation
        wetSignal *= 15.0 * juce::Decibels::decibelsToGain(-_gainDB.getNextValue() * 1.5);
        
        // Over 0 protection
        wetSignal = hardClipData(m_lofiFilter.processSample(wetSignal, channel), false);
        
        // Bias
        wetSignal -= bias;
        
        // Mix dry with wet
        return (1.0 - _mix.getNextValue()) * dataToClip + wetSignal * _mix.getNextValue();
    }
    
    /** The parameters of this module. */
    enum class ParameterId
    {
        kPreamp,
        kThresh,
        kCeiling,
        kMix,
        kBypass
    };
    
    /** Different clipper types*/
    enum class ClipType
    {
        kHard,
        kSoft,
        kDiode,
        kFuzz,
        kTube,
        kSaturation,
        kLofi
    };
        
    /** One method to change any parameter. */
    void setDrive(SampleType newDrive);
    void setThresh(SampleType newThresh);
    void setCeiling(SampleType newCeiling);
    void setMix(SampleType newMix);
    void setEnabled(SampleType isEnabled);
    void setClipperType(ClipType clipType);
    
private:
    
    // Member variables
    bool _globalEnabled;
    juce::SmoothedValue<float> _rawGain;
    juce::SmoothedValue<float> _gainDB;
    juce::SmoothedValue<float> _thresh;
    juce::SmoothedValue<float> _ceiling;
    juce::SmoothedValue<float> _mix;
    float _currentSampleRate;
    
    // Expressions
    static constexpr float _diodeTerm = 2.0 * 0.0253;
    static constexpr float _piDivisor = 2.0 / juce::MathConstants<float>::pi;
    
    ClipType m_clipType;
    
    viator_dsp::SVFilter<float> m_fuzzFilter;
    viator_dsp::SVFilter<float> m_lofiFilter;
};
} // namespace viator_dsp

#endif /* Distortion_h */
