#pragma once
#include <JuceHeader.h>

namespace viator_gui
{
    class CustomTextButton : public juce::LookAndFeel_V4
    {
        public:
        CustomTextButton();
        
        void drawButtonBackground (juce::Graphics& g,
                                   juce::Button& button,
                                   const juce::Colour& backgroundColour,
                                   bool shouldDrawButtonAsHighlighted,
                                   bool shouldDrawButtonAsDown) override;
        
        juce::Font getTextButtonFont (juce::TextButton&, int buttonHeight) override;
        
    private:
    };
}
