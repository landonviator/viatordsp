/*
  ==============================================================================

    TextButtonLAF.h
    Created: 5 Sep 2022 7:12:07pm
    Author:  Landon Viator

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>

namespace juce
{
    namespace viator_gui
    {
        class CustomTextButton : public LookAndFeel_V4
        {
            public:
            CustomTextButton();
            
            void drawButtonBackground (Graphics& g,
                                       Button& button,
                                       const Colour& backgroundColour,
                                       bool shouldDrawButtonAsHighlighted,
                                       bool shouldDrawButtonAsDown) override;
            
            Font getTextButtonFont (TextButton&, int buttonHeight) override;
            
        private:
            std::unique_ptr<juce::DropShadower> buttonDropShadower;
            juce::DropShadow buttonDropShadow;
        };
    }
}
