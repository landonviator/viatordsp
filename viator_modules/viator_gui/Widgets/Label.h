/*
  ==============================================================================

    Label.h
    Created: 1 Aug 2021 1:17:17am
    Author:  landon viator

  ==============================================================================
*/

#pragma once

namespace viator_gui
{

class Label : public juce::Label
{
public:
    
    Label()
    {
        setColour(0x1000280, juce::Colour::fromFloatRGBA(0, 0, 0, 0));
        setColour(0x1000281, juce::Colours::whitesmoke.withAlpha(0.36f));
        setColour(0x1000282, juce::Colour::fromFloatRGBA(0, 0, 0, 0));
        
        const juce::Font font (juce::Font ("Helvetica", 16.0f, juce::Font::FontStyleFlags::bold));
        setFont(font);
    }
    
private:
    
};
}
