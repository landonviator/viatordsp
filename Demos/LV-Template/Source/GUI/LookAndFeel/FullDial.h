/*
  ==============================================================================

    FullDial.h
    Created: 11 Jun 2022 1:41:56pm
    Author:  Landon Viator

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>
class FullDialLAF : public juce::LookAndFeel_V4
{
    
public:
    
    void drawRotarySlider
    (
     juce::Graphics &g,
        int x,
        int y,
        int width,
        int height,
        float sliderPos,
        float rotaryStartAngle,
        float rotaryEndAngle,
     juce::Slider &slider
    ) override;
    
    void drawLabel (juce::Graphics& g, juce::Label& label) override;
    float sliderWidth;
    
private:
    juce::DropShadow shadowProperties;
    juce::DropShadowEffect dialShadow;

};
