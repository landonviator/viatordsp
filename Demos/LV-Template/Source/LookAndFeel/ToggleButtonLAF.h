#pragma once
#include <JuceHeader.h>

class ToggleButtonLAF : public juce::LookAndFeel_V4
{
public:
    ToggleButtonLAF();
    
    void drawButtonBackground (juce::Graphics& g,
                               juce::Button& button,
                                const juce::Colour& backgroundColour,
                                bool shouldDrawButtonAsHighlighted,
                                bool shouldDrawButtonAsDown) override;
    
    void drawTickBox (juce::Graphics& g, juce::Component& component,
                      float x, float y, float w, float h,
                      const bool ticked,
                      const bool isEnabled,
                      const bool shouldDrawButtonAsHighlighted,
                      const bool shouldDrawButtonAsDown) override;
};
