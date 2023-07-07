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

Fader::Fader(const int numFrames, const juce::Image& filmStrip)
{
    // Slider props
    setRange(-60.0, 6.0, 0.1);
    setTextBoxStyle(juce::Slider::TextBoxBelow, false, 64, 32);
    setTextValueSuffix(" dB");
    setSliderStyle(juce::Slider::SliderStyle::LinearVertical);
    setDoubleClickReturnValue(true, 0.0);
    
    // film strip
    _numFrames = numFrames;
    _filmStrip = filmStrip;
    frameHeight = filmStrip.getHeight() / _numFrames;
    frameWidth = filmStrip.getWidth();
}

Fader::~Fader()
{
    setLookAndFeel(nullptr);
}

void Fader::paint (juce::Graphics& g)
{
    if (_filmStrip.isValid())
    {
        const float sliderPos = (float) valueToProportionOfLength(getValue());

        int value = sliderPos * (_numFrames - 1);
        auto dialWidth = getWidth() * 0.9;
        int dialX = getWidth() * 0.05;
        int dialY = 0;

        g.drawImage(_filmStrip, dialX, dialY, dialWidth, dialWidth, 0, value * frameHeight, frameWidth, frameHeight);
    }
    
    else
    {
        setComponentEffect(&dialShadow);
        juce::Slider::paint(g);
    }
}

void Fader::resized()
{
    juce::Slider::resized();
}
}
