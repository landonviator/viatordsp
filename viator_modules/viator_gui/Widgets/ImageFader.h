#pragma once
#include "../LAF/DialLAF.h"

namespace viator_gui
{

class ImageFader  : public juce::Slider
{
public:
    
    ImageFader ();
    ~ImageFader() override;
    
    void paint (juce::Graphics&) override;
    void resized() override;
    
    juce::Slider& getFaderSlider(){return _fader;};
    
    /**
     * @brief Exactly what it says. Sets the image film strip and num frames to use.
     * @author Landon Viator
     * @param main The main film strip image.
     * @param numFrames The number of frames in the film strip.
     */
    void setFaderImageAndNumFrames(const juce::Image main, const int numFrames);
    
    /**
     * @brief Updates the meter value with the current audio RMS, call periodically in a timer.
     * @author Landon Viator
     * @param newMeterValue The new value representing the audio RMS state.
     */
    template <typename SampleType>
    void setMeterValue(SampleType newMeterValue)
    {
        _fader.setValue(newMeterValue);
    }
    
    void setSliderTextBoxWidth(const float newWidth)
    {
        setTextBoxStyle(juce::Slider::TextBoxBelow, false, newWidth, newWidth);
    }
    
    void setDialValueType(viator_gui::CustomDialLabel::ValueType newValueType);
    
    void setViatorTooltip(const juce::String newTooltip) {_tooltip = newTooltip;};
    juce::String getViatorTooltip(){return _tooltip;};
    
    void setIsReversed(bool reverse){_customSliderLabel.setIsReversed(reverse); repaint();};
    
private:
    
    viator_gui::CustomDialLabel _customSliderLabel;
    
    juce::Image _mainImage;
    juce::Image _auxImage;
    int _numFrames = 0;
    int _frameWidth;
    int _frameHeight;
    juce::Slider _fader;
    
    juce::String _tooltip {""};
    
}; // class

} // namespace viator_gui
