#include "Dial.h"

void viator_gui::Dial::setDialStyle(DialStyle dialStyle)
{
    switch (dialStyle)
    {
        case DialStyle::kHardDial:
        {
            setLookAndFeel(&hardDial);
            break;
        }
            
        case DialStyle::kAlphaDial:
        {
            setLookAndFeel(&alphaDial);
            break;
        }
            
        case DialStyle::kAbleDial:
        {
            setLookAndFeel(&ableDial);
            break;
        }
    }
}

void viator_gui::Dial::forceShadow()
{
    setComponentEffect(&dialShadow);
}

void viator_gui::Dial::mouseEnter (const juce::MouseEvent& event)
{
    setColour(juce::Slider::ColourIds::thumbColourId, findColour(juce::Slider::ColourIds::thumbColourId).withMultipliedLightness(1.25));
    setComponentEffect(&dialShadow);
}

void viator_gui::Dial::mouseExit (const juce::MouseEvent& event)
{
    setColour(juce::Slider::ColourIds::thumbColourId, findColour(juce::Slider::ColourIds::thumbColourId).withMultipliedLightness(0.8f));
    setComponentEffect(&dialShadow);
}

void viator_gui::Dial::initProps(juce::String suffix,
               double rangeStart,
               double rangeEnd,
               double intervalValue,
               double returnValue)
{
    setSliderStyle(juce::Slider::SliderStyle::RotaryVerticalDrag);
    setTextBoxStyle(juce::Slider::TextBoxBelow, false, 96, 32);
    setColour(juce::Slider::ColourIds::rotarySliderFillColourId, findColour(Slider::ColourIds::thumbColourId));
    setColour(juce::Slider::ColourIds::rotarySliderOutlineColourId, juce::Colours::black.brighter(0.1).withAlpha(0.8f));
    setColour(juce::Slider::ColourIds::trackColourId, juce::Colours::whitesmoke.darker(1.75f).withAlpha(0.7f));
    setColour(juce::Slider::ColourIds::textBoxOutlineColourId, juce::Colours::black.withAlpha(0.0f));
    setColour(juce::Slider::ColourIds::textBoxTextColourId, juce::Colours::whitesmoke.withAlpha(0.36f));
    setColour(juce::Slider::ColourIds::thumbColourId, juce::Colour::fromFloatRGBA(0.392f, 0.584f, 0.929f, 1.0f).darker(1.0f));
    setRange(rangeStart, rangeEnd, intervalValue);
    setDoubleClickReturnValue(true, returnValue);
    setTextValueSuffix(suffix);
    setLookAndFeel(&hardDial);
    setComponentEffect(&dialShadow);
}

void viator_gui::Dial::initShadows()
{
    shadowProperties.radius = 24;
    shadowProperties.offset = juce::Point<int> (-1, 4);
    shadowProperties.colour = juce::Colours::black.withAlpha(0.5f);
    dialShadow.setShadowProperties (shadowProperties);
}
