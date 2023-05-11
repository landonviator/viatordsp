#pragma once
#include "../LAF/SettingsLAF.h"

namespace viator_gui
{
    class TextButton  : public juce::TextButton
    {
    public:
        TextButton();
        ~TextButton() override;

        void paint (juce::Graphics&) override;
        void resized() override;

    private:
        viator_gui::SettingsButton _customLAF;
        JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (TextButton)
    };
}
