#pragma once
#include "../LAF/MeterLAF.h"

namespace viator_gui
{

class Meter  : public juce::Component
{
public:
    Meter();
    ~Meter() override;

    void paint (juce::Graphics&) override;
    void resized() override;
    
    /**
     * @brief Updates the meter value with the current audio RMS, call periodically in a timer.
     * @author Landon Viator
     * @param newMeterValue The new value representing the audio RMS state.
     */
    template <typename SampleType>
    void setMeterValue(SampleType newMeterValue)
    {
        meter.setValue(newMeterValue);
    }
    
    juce::Slider& getRootSlider(){return meter;};

private:
    juce::Slider meter;
    CustomMeter meterLAF;
    
private:
    void paintSliderLabelTrack(juce::Graphics& g);
    
    void mouseDown(const juce::MouseEvent&) override {}
    void mouseDrag(const juce::MouseEvent&) override {}
    void mouseUp(const juce::MouseEvent&) override {}
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Meter)
}; // Meter

} // viator_gui
