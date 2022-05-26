#pragma once
#include <JuceHeader.h>

class SettingsButtonLAF : public juce::LookAndFeel_V4
{
public:
    SettingsButtonLAF();
    
    void drawButtonBackground (juce::Graphics& g,
                               juce::Button& button,
                                const juce::Colour& backgroundColour,
                                bool shouldDrawButtonAsHighlighted,
                                bool shouldDrawButtonAsDown) override;
};
