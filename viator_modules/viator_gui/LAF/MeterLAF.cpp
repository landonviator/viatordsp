#include "MeterLAF.h"

namespace viator_gui
{
CustomMeter::CustomMeter()
    {
        
    }

    void CustomMeter::drawLinearSlider (juce::Graphics& g, int x, int y, int width, int height,
                                           float sliderPos,
                                           float minSliderPos,
                                           float maxSliderPos,
                                           const juce::Slider::SliderStyle style, juce::Slider& slider)
    {
        g.setColour (slider.findColour (juce::Slider::backgroundColourId));
        g.fillRect(slider.getLocalBounds());
        g.setColour (slider.findColour (juce::Slider::trackColourId));
        g.fillRect (juce::Rectangle<float> ((float) x + 0.5f, sliderPos, (float) width - 1.0f, (float) y + ((float) height)));
    }
}
