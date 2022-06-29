/*
  ==============================================================================

    Buttons.h
    Created: 24 Jun 2022 8:54:30pm
    Author:  Landon Viator

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>

class ButtonStyle : public juce::LookAndFeel_V4
{
public:
    ButtonStyle();
    
    void drawButtonBackground (juce::Graphics& g,
                               juce::Button& button,
                                const juce::Colour& backgroundColour,
                                bool shouldDrawButtonAsHighlighted,
                                bool shouldDrawButtonAsDown) override;
};
