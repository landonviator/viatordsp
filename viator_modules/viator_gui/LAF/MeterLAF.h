#pragma once

namespace viator_gui
{
    class CustomMeter : public juce::LookAndFeel_V4
    {
        public:
        CustomMeter();
        
        void drawLinearSlider (juce::Graphics& g, int x, int y, int width, int height,
                                               float sliderPos,
                                               float minSliderPos,
                                               float maxSliderPos,
                                            const juce::Slider::SliderStyle style, juce::Slider& slider) override;
        
        private:
        float _sliderWidth;
    };
}
