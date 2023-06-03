#pragma once
#include "../LAF/SettingsLAF.h"
#include "../LAF/TextButtonLAF.h"

namespace viator_gui
{
    class TextButton  : public juce::TextButton
    {
    public:
        TextButton();
        TextButton(const juce::String& name);
        ~TextButton() override;

        enum class ButtonStyle
        {
            kNormal,
            kSettings
        };
        
        void paint (juce::Graphics&) override;
        void resized() override;
        
        void setButtonStyle(const ButtonStyle& newStyle);
        
    private:
        viator_gui::SettingsButton _customLAF;
        viator_gui::CustomTextButton _customTextButton;
        
    private:
        void initButtonColors();
        
    private:
        ButtonStyle _buttonStyle = ButtonStyle::kNormal;
        
        JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (TextButton)
    };
}
