#pragma once
#include <JuceHeader.h>
namespace juce
{
    class CustomTextButton : public juce::LookAndFeel_V4
    {
        public:
        CustomTextButton();
        
        void drawButtonBackground (Graphics& g,
                                                   Button& button,
                                                   const Colour& backgroundColour,
                                                   bool shouldDrawButtonAsHighlighted,
                                   bool shouldDrawButtonAsDown) override;
        private:
    };
}
