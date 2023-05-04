#pragma once

namespace viator_gui
{
    class CustomFader : public juce::LookAndFeel_V4
    {
        public:
        CustomFader();
        
        void drawLinearSlider (juce::Graphics& g, int x, int y, int width, int height,
                                               float sliderPos,
                                               float minSliderPos,
                                               float maxSliderPos,
                                            const juce::Slider::SliderStyle style, juce::Slider& slider) override;
        void drawLabel (juce::Graphics& g, juce::Label& label) override;
        
        private:
        float _sliderWidth;
    };
}
