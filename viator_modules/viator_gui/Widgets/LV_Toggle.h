#pragma once
#include "StyleSheet.h"

namespace viator_gui
{
    class LV_Toggle : public juce::ToggleButton
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
        
        void mouseEnter (const juce::MouseEvent& event) override
        {
            setColour(juce::ToggleButton::tickDisabledColourId, juce::Colours::whitesmoke);
            setColour(juce::ToggleButton::tickColourId, juce::Colours::whitesmoke);
            
        }
        
        void mouseExit (const juce::MouseEvent& event) override
        {
            setColour(juce::ToggleButton::tickDisabledColourId, juce::Colours::dimgrey.withAlpha(0.5f));
            setColour(juce::ToggleButton::tickColourId, juce::Colours::springgreen.withAlpha(0.5f));
        }
        
        private:
        
        juce::LV_PowerToggleLAF powerToggle;
        juce::LV_PhaseToggleLAF phaseToggle;
    };
}
