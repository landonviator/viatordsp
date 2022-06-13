/*
  ==============================================================================

    PanelLAF.h
    Created: 9 Jun 2022 11:21:43pm
    Author:  Landon Viator

  ==============================================================================
*/

#pragma once
#include "JuceHeader.h"

/** Border Style*/
class CustomPanel : public juce::LookAndFeel_V2
{
    public:
    
    void drawGroupComponentOutline
    (
     juce::Graphics& g, int width, int height,
        const juce::String& text, const juce::Justification& position,
     juce::GroupComponent& group
     ) override;
};
