/*
  ==============================================================================

    SettingsButtonLAF.h
    Created: 21 May 2022 10:17:02pm
    Author:  Landon Viator

  ==============================================================================
*/

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
