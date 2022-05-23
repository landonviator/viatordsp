/*
  ==============================================================================

    ColorButtonLAF.h
    Created: 22 May 2022 9:34:10pm
    Author:  Landon Viator

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>

class ColorButtonLAF : public juce::LookAndFeel_V4
{
public:
    ColorButtonLAF();
    
    void drawButtonBackground (juce::Graphics& g,
                               juce::Button& button,
                                const juce::Colour& backgroundColour,
                                bool shouldDrawButtonAsHighlighted,
                                bool shouldDrawButtonAsDown) override;
};
