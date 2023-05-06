#include "Dial.h"

viator_gui::Dial::Dial()
{
    // Slider props
    setRange(-15.0, 15.0, 0.1);
    setTextBoxStyle(juce::Slider::TextBoxBelow, false, 64, 32);
    setTextValueSuffix(" dB");
    setSliderStyle(juce::Slider::SliderStyle::RotaryVerticalDrag);
    setDoubleClickReturnValue(true, 0.0);
    setLookAndFeel(&_customDial);
    
    // Shadow
    shadowProperties.radius = 5;
    shadowProperties.offset = juce::Point<int> (0, 0);
    shadowProperties.colour = juce::Colours::black.withAlpha(0.6f);
    dialShadow.setShadowProperties (shadowProperties);
}

viator_gui::Dial::~Dial()
{
    setLookAndFeel(nullptr);
}

void viator_gui::Dial::paint(juce::Graphics &g)
{
    setComponentEffect(&dialShadow);
    juce::Slider::paint(g);
}

void viator_gui::Dial::resized()
{
    juce::Slider::resized();
}
