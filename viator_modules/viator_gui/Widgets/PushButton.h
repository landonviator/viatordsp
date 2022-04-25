/*
  ==============================================================================

    PushButton.h
    Created: 24 Oct 2021 8:30:03pm
    Author:  Landon Viator

  ==============================================================================
*/

#pragma once

namespace viator_gui
{

    class PushButton : public juce::TextButton
    {
        
    public:
    
        PushButton()
        {
            setClickingTogglesState(true);
            setColour(0x1000100, juce::Colours::black.brighter(0.1));
            setColour(0x1000c00, juce::Colours::whitesmoke.withAlpha(0.06f));
            setColour(0x1000101, juce::Colours::lightgoldenrodyellow.darker(0.2f));
            setColour(0x1000102, juce::Colours::whitesmoke.withAlpha(0.5f));
            setColour(0x1000103, juce::Colours::black.brighter(0.1).withAlpha(0.85f));
            setLookAndFeel(&customButton);
        }
        
        ~PushButton()
        {
            setLookAndFeel(nullptr);
        }
        
    private:
        juce::CustomPushButton customButton;
        
    };
}
