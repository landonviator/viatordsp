#ifndef Compressor_h
#define Compressor_h

#include <JuceHeader.h>

namespace viator_dsp
{

template <typename SampleType>
class Compressor : public ModuleBase<SampleType>
{
public:
    Compressor(){};
    ~Compressor(){};

    void reset();
    
    SampleType processSample(SampleType input, SampleType channel) override
    {
        hpFilter.setCutoffFrequency(hpCutoff);
        
        auto xUni = abs(input);
        auto xDB = juce::Decibels::gainToDecibels(xUni);

        if (xDB < -96.0)
        {
            xDB = -96.0;
        }
        
        auto hpSignal = hpFilter.processSample(channel, xUni);
        auto filteredXDB = juce::Decibels::gainToDecibels(std::abs(hpSignal));
        
        if (filteredXDB > threshold)
        {
            if (filteredXDB > thresholdWithKnee)
            {
                gainChange = threshold + (xDB - threshold) / ratio;
            }
        }

        else
        {
            gainChange = xDB;
        }

        gainChangeDB = gainChange - xDB;

        if (gainChangeDB < gainSmoothPrevious)
        {
            gainSmooth = ((1 - alphaAttack) * gainChangeDB) + (alphaAttack * gainSmoothPrevious);
            currentSignal = gainSmooth;
        }

        else
        {
            gainSmooth = ((1 - alphaRelease) * gainChangeDB) + (alphaRelease * gainSmoothPrevious);
            currentSignal = gainSmooth;
        }
        
        gainSmoothPrevious = gainSmooth;
        
        return input * juce::Decibels::decibelsToGain(gainSmooth);
    }
    
    void setParameters(SampleType newThresh, SampleType newRatio, SampleType newAttack, SampleType newRelease, SampleType newKnee, SampleType hpf);
    
private:
    float samplerate = 44100.0f;
    float threshold = 0.0f;
    float ratio = 2.0f;
    float attack = 5.0f;
    float release = 5.0f;
    float knee = 0.0f;
    float kneeScaled = 0.0f;
    float thresholdWithKnee = 0.0f;
    
    float alphaAttack = 0.0f;
    float alphaRelease = 0.0f;
    
    float gainSmoothPrevious = 0.0f;
    float gainChangeDB = 0.0f;
    
    float gainChange, gainSmooth, currentSignal;
    
    juce::dsp::LinkwitzRileyFilter<SampleType> hpFilter;
    float hpCutoff = 20.0f;
};

} // namespace viator_dsp

#endif /* Compressor_h */
