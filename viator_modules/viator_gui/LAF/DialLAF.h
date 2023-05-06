#pragma once

namespace viator_gui
{
    class CustomDial : public juce::LookAndFeel_V4
    {
        public:
        CustomDial();
        
        void drawRotarySlider
        (
         juce::Graphics &g,
            int x,
            int y,
            int width,
            int height,
            float sliderPos,
            float rotaryStartAngle,
            float rotaryEndAngle,
         juce::Slider &slider
         ) override;
        
        void drawLabel (juce::Graphics& g, juce::Label& label) override;
        
    private:
        float _sliderWidth;
    };
}
