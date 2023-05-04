#pragma once
#include <JuceHeader.h>
#include "../Globals/Globals.h"

namespace juce
{
    class CustomFader : public juce::LookAndFeel_V4
    {
        public:
        CustomFader();
        
        void drawLinearSlider (Graphics& g, int x, int y, int width, int height,
                                               float sliderPos,
                                               float minSliderPos,
                                               float maxSliderPos,
                                            const Slider::SliderStyle style, Slider& slider) override;
        void drawLabel (juce::Graphics& g, juce::Label& label) override;
        
        private:
        float _sliderWidth;
    };
}
