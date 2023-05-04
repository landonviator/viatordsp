#pragma once
#include <JuceHeader.h>

namespace juce
{
    class CustomMenu : public LookAndFeel_V4
    {
        public:
        CustomMenu();
        
        void drawComboBox (Graphics& g, int width, int height, bool,
                                           int, int, int, int, ComboBox& box);
    private:
    };
}
