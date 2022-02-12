/*
  ==============================================================================

    LV_Toggle.h
    Created: 21 Aug 2021 2:06:36am
    Author:  Landon Viator

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>
#include "StyleSheet.h"

namespace juce
{

    class LV_Toggle : public ToggleButton
    {
        
    public:
    
        LV_Toggle()
        {
            setClickingTogglesState(true);
            setColour(juce::ToggleButton::tickDisabledColourId, juce::Colours::dimgrey.withAlpha(0.5f));
            setColour(juce::ToggleButton::tickColourId, juce::Colours::springgreen.withAlpha(0.5f));
            setLookAndFeel(&powerToggle);
        }
        
        ~LV_Toggle() override
        {
            setLookAndFeel(nullptr);
        }
        
        enum class ToggleStyle
        {
            kPower,
            kPhase
        };
        
        void setToggleStyle(ToggleStyle newToggleStyle)
        {
            switch (newToggleStyle) {
                case ToggleStyle::kPower:
                {
                    setLookAndFeel(&powerToggle);
                    break;
                }

                case ToggleStyle::kPhase:
                {
                    setLookAndFeel(&phaseToggle);
                    break;
                }
            }
        }
        
        void mouseEnter (const MouseEvent& event) override
        {
            setColour(juce::ToggleButton::tickDisabledColourId, juce::Colours::whitesmoke);
            setColour(juce::ToggleButton::tickColourId, juce::Colours::whitesmoke);
            
        }
        
        void mouseExit (const MouseEvent& event) override
        {
            setColour(juce::ToggleButton::tickDisabledColourId, juce::Colours::dimgrey.withAlpha(0.5f));
            setColour(juce::ToggleButton::tickColourId, juce::Colours::springgreen.withAlpha(0.5f));
        }
        
        private:
        
        LV_PowerToggleLAF powerToggle;
        LV_PhaseToggleLAF phaseToggle;
    };
}
