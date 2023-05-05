#include "Fader.h"

namespace viator_gui
{
Fader::Fader()
{
    // Slider props
    setRange(-15.0, 15.0, 0.1);
    setTextBoxStyle(juce::Slider::TextBoxBelow, false, 64, 32);
    setTextValueSuffix(" dB");
    setSliderStyle(juce::Slider::SliderStyle::LinearVertical);
    setDoubleClickReturnValue(true, 0.0);
    setLookAndFeel(&_customFaderLAF);
    
    // Shadow
    shadowProperties.radius = 5;
    shadowProperties.offset = juce::Point<int> (0, 0);
    shadowProperties.colour = juce::Colours::black.withAlpha(0.6f);
    dialShadow.setShadowProperties (shadowProperties);
}

Fader::~Fader()
{
    setLookAndFeel(nullptr);
}

void Fader::paint (juce::Graphics& g)
{
    setComponentEffect(&dialShadow);
    juce::Slider::paint(g);
}

void Fader::resized()
{
    juce::Slider::resized();
}
}
