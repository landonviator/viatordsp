#include "Fader.h"

void viator_gui::Fader::forceShadow()
{
    setComponentEffect(&sliderShadow);
}

void viator_gui::Fader::mouseEnter (const juce::MouseEvent& event)
{
    setColour(juce::Slider::ColourIds::thumbColourId, findColour(juce::Slider::ColourIds::thumbColourId).withMultipliedBrightness(1.25));
    setComponentEffect(&sliderShadow);
}

void viator_gui::Fader::mouseExit (const juce::MouseEvent& event)
{
    setColour(juce::Slider::ColourIds::thumbColourId, findColour(juce::Slider::ColourIds::thumbColourId).withMultipliedBrightness(0.8));
    setComponentEffect(&sliderShadow);
}

void viator_gui::Fader::initProps
(
    juce::String suffix,
    double rangeStart,
    double rangeEnd,
    double intervalValue,
    double returnValue
)
{
    setSliderStyle(juce::Slider::SliderStyle::LinearVertical);
    setTextBoxStyle(juce::Slider::TextBoxBelow, true, 72, 32);
    setColour(juce::Slider::ColourIds::backgroundColourId, juce::Colours::black);
    setColour(juce::Slider::ColourIds::trackColourId, juce::Colours::black.withAlpha(0.0f));
    setColour(juce::Slider::ColourIds::textBoxOutlineColourId, juce::Colours::black.withAlpha(0.0f));
    setColour(juce::Slider::ColourIds::textBoxTextColourId, juce::Colours::whitesmoke.withAlpha(0.36f));
    setColour(juce::Slider::ColourIds::thumbColourId, juce::Colour::fromFloatRGBA(0.392f, 0.584f, 0.929f, 1.0f).darker(1.0));
    setRange(rangeStart, rangeEnd, intervalValue);
    setDoubleClickReturnValue(true, returnValue);
    setTextValueSuffix(suffix);
    setLookAndFeel(&customFader);
    setComponentEffect(&sliderShadow);
}

void viator_gui::Fader::initShadows()
{
    sliderShadowProperties.radius = 4;
    sliderShadowProperties.offset = juce::Point<int> (0, 0);
    sliderShadowProperties.colour = juce::Colours::black.withAlpha(1.0f);
    sliderShadow.setShadowProperties (sliderShadowProperties);
}

void viator_gui::Fader::updateLabelColor(juce::Colour newColor)
{
    if (newColor == juce::Colours::black || newColor == juce::Colour::fromRGB(56, 72, 92))
    {
        trimLabel.setColour(juce::Label::ColourIds::textColourId, juce::Colours::whitesmoke.withAlpha(0.6f));
        accentColor = juce::Colours::whitesmoke.withAlpha(0.6f);
    }
    
    else
    {
        trimLabel.setColour(juce::Label::ColourIds::textColourId, newColor);
        accentColor = newColor;
    }
    
    repaint();
}
