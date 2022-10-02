/*
  ==============================================================================

    PushButton.h
    Created: 24 Oct 2021 8:30:03pm
    Author:  Landon Viator

  ==============================================================================
*/

#pragma once
#include "../LAF/TextButtonLAF.h"

namespace viator_gui
{

    class PushButton : public juce::TextButton
    {
        
    public:
    
        PushButton()
        {
            setClickingTogglesState(true);
            setColour(juce::TextButton::ColourIds::buttonColourId, juce::Colour::fromRGB(24, 24, 24));
            setColour(juce::TextButton::ColourIds::buttonOnColourId, juce::Colour::fromRGB(50, 50, 50));
            setColour(juce::TextButton::ColourIds::textColourOnId, juce::Colour::fromRGB(90, 182, 223));
            setColour(juce::TextButton::ColourIds::textColourOffId, juce::Colour::fromRGB(90, 182, 223));
            setColour(juce::ComboBox::ColourIds::outlineColourId, juce::Colour::fromRGB(54, 54, 54));
            setLookAndFeel(&customButton);
        }
        
        ~PushButton()
        {
            setLookAndFeel(nullptr);
        }
        
    private:
        juce::viator_gui::CustomTextButton customButton;
    };
}
