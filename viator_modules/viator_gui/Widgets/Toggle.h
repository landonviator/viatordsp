#pragma once
#include "StyleSheet.h"
#include "Label.h"

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
        
        
        private:
        
        void mouseEnter (const juce::MouseEvent& event) override;
        void mouseExit (const juce::MouseEvent& event) override;
        
        juce::PowerToggleLAF powerToggle;
        juce::PhaseToggleLAF phaseToggle;
        
        /** Label */
        Label toggleLabel {""};
    };
}
