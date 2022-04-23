
#pragma once

namespace juce
{

    class CustomMenuLAF : public LookAndFeel_V4
    {
        
    public:
        
        void drawComboBox (Graphics& g, int width, int height, bool,
                           int, int, int, int, ComboBox& box);
    };
}
