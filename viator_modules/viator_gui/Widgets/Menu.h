#pragma once
#include "../LAF/MenuLAF.h"

namespace viator_gui
{
    class Menu  : public juce::ComboBox
    {
    public:
        Menu();
        ~Menu();

    private:
        void mouseEnter (const juce::MouseEvent &event) override;
        void mouseExit (const juce::MouseEvent &event) override;
        
    private:
        const juce::Colour _textColor = juce::Colour::fromRGB(161, 168, 181).darker(0.3f);
        const juce::Colour _noColor = juce::Colours::transparentBlack;
        const juce::Colour _innerBgColor = juce::Colour::fromRGB(40, 44, 52);
        viator_gui::CustomMenu _customLAF;
        
        JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Menu)
    };
}
