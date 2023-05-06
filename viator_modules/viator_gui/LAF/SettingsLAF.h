#pragma once
#include <JuceHeader.h>
namespace viator_gui
{
    class SettingsButton : public juce::LookAndFeel_V4
    {
        public:
        SettingsButton();
        
        void drawButtonBackground (juce::Graphics& g,
                                   juce::Button& button,
                                                   const juce::Colour& backgroundColour,
                                                   bool shouldDrawButtonAsHighlighted,
                                   bool shouldDrawButtonAsDown) override;
        private:
    };
}
