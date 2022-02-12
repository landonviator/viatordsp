/*
  ==============================================================================

    LV_Menu.h
    Created: 10 Oct 2021 1:42:17pm
    Author:  Landon Viator

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>
#include "../Widgets/StyleSheet.h"

namespace juce
{
    class LV_Menu : public ComboBox, private juce::Timer
    {
        
    public:
    
        LV_Menu()
        {
            setLookAndFeel(&customMenu);
            setColour(juce::ComboBox::ColourIds::backgroundColourId, juce::Colours::black.brighter(0.1f).withAlpha(0.0f));
            setColour(juce::ComboBox::ColourIds::outlineColourId, juce::Colours::whitesmoke.withAlpha(0.0f));
            setColour(juce::ComboBox::ColourIds::focusedOutlineColourId, juce::Colours::black.withAlpha(0.5f));
            setColour(juce::ComboBox::ColourIds::textColourId, juce::Colours::whitesmoke.withAlpha(0.5f));
            setColour(juce::ComboBox::ColourIds::arrowColourId, juce::Colours::skyblue.darker(0.5f));

            getLookAndFeel().setColour(juce::PopupMenu::backgroundColourId, juce::Colours::black.brighter(0.1f));
            getLookAndFeel().setColour(juce::PopupMenu::highlightedBackgroundColourId, juce::Colours::skyblue.withAlpha(0.1f));
            getLookAndFeel().setColour(juce::PopupMenu::textColourId, juce::Colours::whitesmoke.withAlpha(0.5f));
            getLookAndFeel().setColour(juce::PopupMenu::highlightedTextColourId, juce::Colours::skyblue);
        
            setJustificationType(juce::Justification::centred);
        }
        
        ~LV_Menu()
        {
            setLookAndFeel(nullptr);
        }
        
    private:
        
        void timerCallback() final
        {
            setColour(juce::ComboBox::ColourIds::backgroundColourId, juce::Colours::black.brighter(0.1f).withAlpha(0.0f));
        }
        
        void mouseEnter (const MouseEvent& event) override
        {
            setColour(juce::ComboBox::ColourIds::backgroundColourId, juce::Colours::whitesmoke.withAlpha(0.05f));
            startTimer(1000);
        }
        
        void mouseExit (const MouseEvent& event) override
        {
            setColour(juce::ComboBox::ColourIds::backgroundColourId, juce::Colours::black.brighter(0.1f).withAlpha(0.0f));
            stopTimer();
        }
        
        LV_Custom_Menu customMenu;
    };
}
