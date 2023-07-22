#ifndef Distortion_h
#define Distortion_h

#include "../../Common/Common.h"
#include "../Filter/SVFilter.h"

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
    
    void processBuffer(juce::AudioBuffer<float>& buffer)
    {
        auto data = buffer.getArrayOfWritePointers();
                
        for (int sample = 0; sample < buffer.getNumSamples(); ++sample)
        {
            for (int ch = 0; ch < buffer.getNumChannels(); ++ch)
            {
                {
                    data[ch][sample] = processSample(data[ch][sample], ch);
                    data[ch][sample] = _dcFilter.processSample(ch, data[ch][sample]);
                }
            }
        }
    }
    
    /** Process an individual sample */
    SampleType processSample(SampleType input, int ch) noexcept
    {
        switch(m_clipType)
        {
            case ClipType::kHard: return hardClipData(input, true, ch) * juce::Decibels::decibelsToGain(_output.getNextValue()); break;
            case ClipType::kSoft: return softClipData(input, true, ch) * juce::Decibels::decibelsToGain(_output.getNextValue()); break;
            case ClipType::kFuzz: return processFuzz(input, ch) * juce::Decibels::decibelsToGain(_output.getNextValue()); break;
            case ClipType::kTube: return processTube(input, ch) * juce::Decibels::decibelsToGain(_output.getNextValue()); break;
            case ClipType::kSaturation: return processSaturation(input, ch) * juce::Decibels::decibelsToGain(_output.getNextValue()); break;
            case ClipType::kLofi: return processLofi(input, ch) * juce::Decibels::decibelsToGain(_output.getNextValue()); break;
        }
    }
    
    /** Hard clip data */
    SampleType hardClipData(SampleType dataToClip, bool useDrive, int channel)
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
        
        // Volume compensation
        wetSignal *= juce::Decibels::decibelsToGain(-_gainDB.getNextValue() * 0.5);
        
        // Mix dry with wet
        auto mix = (1.0 - _mix.getNextValue()) * dataToClip + wetSignal * _mix.getNextValue();
        
        return mix;
    }

    /** Soft Clip */
    SampleType softClipData(SampleType dataToClip, bool useDrive, int channel)
    {
        // Soft algorithim
        auto wetSignal = dataToClip;
        
        if (useDrive)
        {
            wetSignal *= _rawGain.getNextValue();
        }
        
        wetSignal = _piDivisor * std::atan(wetSignal);
        
        if (useDrive)
        {
            wetSignal *= 2.0;
            
            wetSignal *= juce::Decibels::decibelsToGain(-_gainDB.getNextValue() * 0.5);
        }
        
        // Mix dry with wet
        auto mix = (1.0 - _mix.getNextValue()) * dataToClip + wetSignal * _mix.getNextValue();
        
        return mix;
    }

    /** Diode */
    SampleType processDiode(SampleType dataToClip, int channel)
    {
        // Diode algorithim
        auto wetSignal = dataToClip;
        wetSignal *= _rawGain.getNextValue();
        wetSignal = softClipData(0.315 * (juce::dsp::FastMathApproximations::exp(0.1 * dataToClip / (_diodeTerm)) - 1.0), false, channel);
        return (1.0 - _mix.getNextValue()) * dataToClip + hardClipData(wetSignal, false, channel) * _mix.getNextValue();
    }
    
    /** Tube */
    SampleType processTube(SampleType dataToClip, int channel)
    {
        // Tube algorithim
        auto wetSignal = dataToClip;
        
        wetSignal *= _rawGain.getNextValue();
        
        if (wetSignal >= 0.0)
        {
            wetSignal = hardClipData(wetSignal, true, channel);
        }
        
        else
        {
            wetSignal = softClipData(wetSignal, true, channel);
        }
        
        wetSignal *= juce::Decibels::decibelsToGain(-_gainDB.getNextValue() * 0.25);
        
        // Mix dry with wet
        auto mix = (1.0 - _mix.getNextValue()) * dataToClip + wetSignal * _mix.getNextValue();
        
        return mix;
    }
    
    /** Fuzz */
    SampleType processFuzz(SampleType dataToClip, int channel)
    {
        // Fuzz algorithim
        auto wetSignal = dataToClip;
        
        auto fuzz = processTube(wetSignal, channel);
        
        wetSignal = softClipData(m_fuzzFilter.processSample(fuzz, channel), true, channel);
        
        wetSignal *= 0.5;
        
        // Mix dry with wet
        auto mix = (1.0 - _mix.getNextValue()) * dataToClip + wetSignal * _mix.getNextValue();
        
        return mix;
    }
    
    
    /** Saturation */
    SampleType processSaturation(SampleType dataToClip, int channel)
    {
        auto wetSignal = dataToClip;
        
        auto bias = 0.15;
        
        wetSignal *= _rawGain.getNextValue() + bias;
        
        auto thresh = _thresh.getNextValue();
        
        // Saturation algorithim
        if (wetSignal > thresh)
        {
            wetSignal = thresh + (wetSignal - thresh) / (1.0 + std::pow((( wetSignal - 0.5 ) / thresh), 2.0));
        }
        
        wetSignal *= 1.5;
        
        wetSignal *= juce::Decibels::decibelsToGain(-_gainDB.getNextValue());
        
        // Mix dry with wet
        auto mix = (1.0 - _mix.getNextValue()) * dataToClip + softClipData(wetSignal - bias, false, channel) * _mix.getNextValue();
        
        return mix;
    }
    
    /** Lofi Distortion */
    SampleType processLofi(SampleType dataToClip, int channel)
    {
        // Bias
        auto wetSignal = dataToClip;
        
        // Lofi algorithim
        if (wetSignal < 0)
        {
            wetSignal *= juce::jmap(_gainDB.getNextValue(), 0.0f, 20.0f, 1.0f, -1.0f);
        }
        
        // Saturate signal
        wetSignal = softClipData(wetSignal, false, channel);
        
        // Volume compensation
        wetSignal *= juce::Decibels::decibelsToGain(_gainDB.getNextValue() * 0.25);
        
        // Over 0 protection
        wetSignal = hardClipData(m_lofiFilter.processSample(wetSignal, channel), false, channel);
        
        // Mix dry with wet
        auto mix = (1.0 - _mix.getNextValue()) * dataToClip + wetSignal * _mix.getNextValue();
        
        return mix;
    }
    
    /** The parameters of this module. */
    enum class ParameterId
    {
        kPreamp,
        kThresh,
        kCeiling,
        kMix,
        kOutput,
        kBypass
    };
    
    /** Different clipper types*/
    enum class ClipType
    {
        kHard,
        kSoft,
        kFuzz,
        kTube,
        kSaturation,
        kLofi
    };
        
    void setDrive(SampleType newDrive);
    void setThresh(SampleType newThresh);
    void setCeiling(SampleType newCeiling);
    void setMix(SampleType newMix);
    void setOutput(SampleType newOutput);
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
    juce::SmoothedValue<float> _output;
    float _currentSampleRate;
    
    // Expressions
    static constexpr float _diodeTerm = 2.0 * 0.0253;
    static constexpr float _piDivisor = 2.0 / juce::MathConstants<float>::pi;
    
    ClipType m_clipType;
    
    viator_dsp::SVFilter<float> m_fuzzFilter;
    viator_dsp::SVFilter<float> m_lofiFilter;
    juce::dsp::LinkwitzRileyFilter<float> _dcFilter;
};
} // namespace viator_dsp

#endif /* Distortion_h */
