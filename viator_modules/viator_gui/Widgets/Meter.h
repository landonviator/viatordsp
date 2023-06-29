#pragma once

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

private:
    
    juce::Slider meter;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Meter)
}; // Meter

} // viator_gui
