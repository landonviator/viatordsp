#pragma once
#include <JuceHeader.h>

class MenuSliderLAF : public juce::LookAndFeel_V4
{
public:
    
    MenuSliderLAF();
    
    void drawLinearSlider (juce::Graphics& g, int x, int y, int width, int height,
                                           float sliderPos,
                                           float minSliderPos,
                                           float maxSliderPos,
                                           const juce::Slider::SliderStyle style,
                                           juce::Slider& slider) override;
};
