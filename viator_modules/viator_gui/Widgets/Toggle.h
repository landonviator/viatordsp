#pragma once
#include "StyleSheet.h"

namespace viator_gui
{
    class Toggle : public juce::ToggleButton
    {
        
    public:
    
        Toggle();
        
        ~Toggle() override;
        
        enum class ToggleStyle
        {
            kPower,
            kPhase
        };
        
        void setToggleStyle(ToggleStyle newToggleStyle);
        
        void mouseEnter (const juce::MouseEvent& event) override;
        
        void mouseExit (const juce::MouseEvent& event) override;
        
        private:
        
        juce::PowerToggleLAF powerToggle;
        juce::PhaseToggleLAF phaseToggle;
    };
}
