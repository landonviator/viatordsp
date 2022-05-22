/*
  ==============================================================================

    LabelLAF.h
    Created: 22 May 2022 2:05:56pm
    Author:  Landon Viator

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>

class LabelLAF : public juce::LookAndFeel_V2
{
public:
    LabelLAF();
    
    void drawLabel (juce::Graphics& g, juce::Label& label) override;
};
