#pragma once

namespace viator_gui
{
    class CustomMenu : public juce::LookAndFeel_V4
    {
        public:
        CustomMenu();
        
        void drawComboBox (juce::Graphics& g, int width, int height, bool,
                                           int, int, int, int, juce::ComboBox& box);
    private:
    };
}
