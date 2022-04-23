/*
  ==============================================================================

    Menu.h
    Created: 10 Oct 2021 1:42:17pm
    Author:  Landon Viator

  ==============================================================================
*/

#pragma once
#include "../Widgets/Menu_Styles.h"

namespace viator_gui
{
    class Menu : public juce::ComboBox, private juce::Timer
    {
        
    public:
    
        Menu();
        
        ~Menu();
        
    private:
        
        void timerCallback() final;
        
        void mouseEnter (const juce::MouseEvent& event) override;
        
        void mouseExit (const juce::MouseEvent& event) override;
        
        juce::CustomMenuLAF customMenuLAF;
    };
}
