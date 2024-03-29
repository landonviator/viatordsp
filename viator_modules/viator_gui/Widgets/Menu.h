#pragma once
#include "../LAF/MenuLAF.h"

namespace viator_gui
{
    class Menu  : public juce::ComboBox
    {
    public:
        Menu();
        ~Menu();
        
        void setMenuShouldHover(bool shouldMenuHover){_shouldHover = shouldMenuHover;};

    private:
        void mouseEnter (const juce::MouseEvent &event) override;
        void mouseExit (const juce::MouseEvent &event) override;
        
    private:
        const juce::Colour _noColor = juce::Colours::transparentBlack;
        const juce::Colour _innerBgColor = juce::Colours::black.withAlpha(0.8f);
        viator_gui::CustomMenu _customLAF;
        bool _shouldHover = true;
        
        JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Menu)
    };
}
