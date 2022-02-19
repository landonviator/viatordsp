/*
  ==============================================================================

    LV_Menu.h
    Created: 10 Oct 2021 1:42:17pm
    Author:  Landon Viator

  ==============================================================================
*/

#pragma once
#include "../Widgets/StyleSheet.h"

namespace viator_gui
{
    class LV_Menu : public juce::ComboBox, private juce::Timer
    {
        
    public:
    
        LV_Menu();
        
        ~LV_Menu();
        
    private:
        
        void timerCallback() final;
        
        void mouseEnter (const juce::MouseEvent& event) override;
        
        void mouseExit (const juce::MouseEvent& event) override;
        
        juce::LV_Custom_Menu customMenu;
    };
}
