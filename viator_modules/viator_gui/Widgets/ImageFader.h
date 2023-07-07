#pragma once

namespace viator_gui
{

class ImageFader  : public juce::Component
{
public:
    
    ImageFader (int numFrames, const juce::Image& filmStrip);
    ~ImageFader() override;
    
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
    int _numFrames = 62;
    int frameWidth;
    int frameHeight;
    juce::Slider vuMeter;
}; // class
}// namespace viator_gui
