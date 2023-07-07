#pragma once

namespace viator_gui
{

class LedMeter  : public juce::Component
{
public:
    
    LedMeter (const juce::String& sliderName, const juce::Image& filmStrip);
    ~LedMeter() override;
    
    void paint (juce::Graphics&) override;
    void resized() override;
    
    juce::Slider& getVUMeter(){return vuMeter;};
    
    /**
     * @brief Updates the meter value with the current audio RMS, call periodically in a timer.
     * @author Landon Viator
     * @param newMeterValue The new value representing the audio RMS state.
     */
    template <typename SampleType>
    void setMeterValue(SampleType newMeterValue)
    {
        vuMeter.setValue(newMeterValue);
    }
    
private:
    
    juce::Image _filmStrip;
    const int _numFrames = 62;
    int frameWidth;
    int frameHeight;
    juce::Slider vuMeter;
    
    void mouseDown(const juce::MouseEvent&) override {}
    void mouseDrag(const juce::MouseEvent&) override {}
    void mouseUp(const juce::MouseEvent&) override {}
    
}; // class
}// namespace viator_gui
