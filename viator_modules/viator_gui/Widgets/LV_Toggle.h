#pragma once
#include "StyleSheet.h"

namespace viator_gui
{
    class LV_Toggle : public juce::ToggleButton
    {
        
    public:
    
        LV_Toggle();
        
        ~LV_Toggle() override;
        
        enum class ToggleStyle
        {
            kPower,
            kPhase
        };
        
        void setToggleStyle(ToggleStyle newToggleStyle);
        
        void mouseEnter (const juce::MouseEvent& event) override;
        
        void mouseExit (const juce::MouseEvent& event) override;
        
        private:
        
        juce::LV_PowerToggleLAF powerToggle;
        juce::LV_PhaseToggleLAF phaseToggle;
    };
}
