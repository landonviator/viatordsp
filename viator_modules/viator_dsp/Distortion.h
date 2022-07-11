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
        auto wetSignal = dataToClip;
        
        if (useDrive)
        {
            wetSignal *= _rawGain.getNextValue();
        }
        
        auto ceiling = _ceiling.getNextValue();
        
        // Hard algorithim
        if (std::abs(wetSignal) >= ceiling)
        {
            wetSignal *= ceiling / std::abs(wetSignal);
        }
        
        return (1.0 - _mix.getNextValue()) * dataToClip + wetSignal * _mix.getNextValue();
    }

    /** Soft Clip */
    SampleType softClipData(SampleType dataToClip)
    {
        // Soft algorithim
        auto wetSignal = dataToClip;
        wetSignal *= _rawGain.getNextValue();
        wetSignal = _piDivisor * std::atan(wetSignal);
        return (1.0 - _mix.getNextValue()) * dataToClip + hardClipData(wetSignal, false) * _mix.getNextValue();
    }

    /** Diode */
    SampleType processDiode(SampleType dataToClip)
    {
        // Diode algorithim
        auto wetSignal = dataToClip;
        wetSignal *= _rawGain.getNextValue();
        wetSignal = softClipData(0.315 * (juce::dsp::FastMathApproximations::exp(0.1 * dataToClip / (_diodeTerm)) - 1.0));
        return (1.0 - _mix.getNextValue()) * dataToClip + hardClipData(wetSignal, false) * _mix.getNextValue();
    }
    
    /** Tube */
    SampleType processTube(SampleType dataToClip)
    {
        // Tube algorithim
        auto wetSignal = dataToClip;
        
        wetSignal *= _rawGain.getNextValue();
        
        if (wetSignal >= 0.0)
        {
            wetSignal = hardClipData(wetSignal, false);
        }
        
        else
        {
            wetSignal = softClipData(wetSignal);
        }
        
        return (1.0 - _mix.getNextValue()) * dataToClip + hardClipData(wetSignal, false) * _mix.getNextValue();
    }
    
    /** Fuzz */
    SampleType processFuzz(SampleType dataToClip, int channel)
    {
        // Fuzz algorithim
        auto wetSignal = dataToClip;
        auto fuzz = processTube(wetSignal);
        wetSignal = softClipData(m_fuzzFilter.processSample(fuzz, channel));
        return (1.0 - _mix.getNextValue()) * dataToClip + hardClipData(wetSignal, false) * _mix.getNextValue();
    }
    
    
    /** Saturation */
    SampleType processSaturation(SampleType dataToClip, bool light)
    {
        auto wetSignal = dataToClip;
        
        light ? wetSignal *= _rawGain.getNextValue() * 0.1 : wetSignal *= _rawGain.getNextValue();
        
        auto thresh = _thresh.getNextValue();
        
        // Saturation algorithim
        if (wetSignal > thresh)
        {
            wetSignal = thresh + (wetSignal - thresh) / (1.0 + std::pow((( wetSignal - 0.5 ) / thresh), 2.0));
        }
        
        // Mix dry with wet
        return (1.0 - _mix.getNextValue()) * dataToClip + softClipData(wetSignal) * _mix.getNextValue();
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
