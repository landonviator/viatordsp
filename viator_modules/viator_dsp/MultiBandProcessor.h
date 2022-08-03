#ifndef MultiBandProcessor_h
#define MultiBandProcessor_h
#include "../Common/Common.h"

namespace viator_dsp
{
template <typename SampleType>
class MultiBandProcessor
{
public:
    
    MultiBandProcessor();
    void prepare(const juce::dsp::ProcessSpec& spec) noexcept;
    void reset() noexcept;
    
    void processSample(SampleType input, int ch)
    {
        _lowBandsFilter.processSample(ch, input, _lowBand, _lowMidBand);
        _midBandsFilter.processSample(ch, _lowMidBand, _lowMidBand, _midBand);
        _highBandsFilter.processSample(ch, _midBand, _midBand, _highBand);
    }
    
    SampleType getLowBand()
    {
        return _lowBand * _band1;
    }
    
    SampleType getLowMidBand()
    {
        return _lowMidBand * _band2;
    }
    
    SampleType getMidBand()
    {
        return _midBand * _band3;
    }
    
    SampleType getHighBand()
    {
        return _highBand * _band4;
    }
    
    void toggleBand1(bool bandOn);
    void toggleBand2(bool bandOn);
    void toggleBand3(bool bandOn);
    void toggleBand4(bool bandOn);
    
    void setLowCutoff(SampleType newCutoff);
    void setMidCutoff(SampleType newCutoff);
    void setHighCutoff(SampleType newCutoff);
    
private:
    
    // Member variables
    float _cutoff1;
    float _cutoff2;
    float _cutoff3;
    float _currentSampleRate;
    bool _band1 = true;
    bool _band2 = true;
    bool _band3 = true;
    bool _band4 = true;
    
    // Bands
    float _lowBand;
    float _lowMidBand;
    float _midBand;
    float _highBand;
    
    juce::dsp::LinkwitzRileyFilter<float> _lowBandsFilter;
    juce::dsp::LinkwitzRileyFilter<float> _midBandsFilter;
    juce::dsp::LinkwitzRileyFilter<float> _highBandsFilter;
};
}
#endif
