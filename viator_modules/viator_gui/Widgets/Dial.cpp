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
            
        case DialStyle::kFullDial:
        {
            setLookAndFeel(&fullDial);
            break;
        }
            
        case DialStyle::kFullDialMirrow:
        {
            setLookAndFeel(&fullDialMirrow);
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

//void viator_gui::Dial::mouseEnter (const juce::MouseEvent& event)
//{
//    setColour(juce::Slider::ColourIds::thumbColourId, findColour(juce::Slider::ColourIds::thumbColourId).withMultipliedLightness(1.1));
//    setComponentEffect(&dialShadow);
//}
//
//void viator_gui::Dial::mouseExit (const juce::MouseEvent& event)
//{
//    setColour(juce::Slider::ColourIds::thumbColourId, findColour(juce::Slider::ColourIds::thumbColourId).withMultipliedLightness(0.909f));
//    setComponentEffect(&dialShadow);
//}

void viator_gui::Dial::initProps(juce::String suffix,
               double rangeStart,
               double rangeEnd,
               double intervalValue,
               double returnValue)
{
    setSliderStyle(juce::Slider::SliderStyle::RotaryVerticalDrag);
    setTextBoxStyle(juce::Slider::TextBoxBelow, false, 128, 32);
    setColour(juce::Slider::ColourIds::rotarySliderFillColourId, juce::Colour::fromFloatRGBA(0.392f, 0.584f, 0.929f, 1.0f).darker(1.0f));
    setColour(juce::Slider::ColourIds::rotarySliderOutlineColourId, juce::Colours::black.brighter(0.1));
    setColour(juce::Slider::ColourIds::trackColourId, juce::Colours::whitesmoke.darker(1.5f));
    setColour(juce::Slider::ColourIds::textBoxOutlineColourId, juce::Colours::black.withAlpha(0.0f));
    setColour(juce::Slider::ColourIds::textBoxTextColourId, juce::Colours::whitesmoke.darker(0.5f));
    setColour(juce::Slider::ColourIds::thumbColourId, juce::Colour::fromFloatRGBA(0.392f, 0.584f, 0.929f, 1.0f).darker(1.0f));
    setColour(juce::Slider::ColourIds::backgroundColourId, juce::Colours::whitesmoke.darker(1.5f));
    setRange(rangeStart, rangeEnd, intervalValue);
    setDoubleClickReturnValue(true, returnValue);
    setTextValueSuffix(suffix);
    setLookAndFeel(&fullDial);
    setComponentEffect(&dialShadow);
}

void viator_gui::Dial::initShadows()
{
    shadowProperties.radius = 24;
    shadowProperties.offset = juce::Point<int> (-1, 4);
    shadowProperties.colour = juce::Colours::black.withAlpha(0.5f);
    dialShadow.setShadowProperties (shadowProperties);
}

void viator_gui::Dial::updateLabelColor(juce::Colour newColor)
{
    if (newColor == juce::Colours::black || newColor == juce::Colour::fromRGB(56, 72, 92))
    {
        setColour(juce::Slider::ColourIds::backgroundColourId, juce::Colours::whitesmoke.darker(1.5f));
        setColour(juce::Slider::ColourIds::textBoxTextColourId, juce::Colours::whitesmoke.withAlpha(0.4f));
        setColour(juce::Slider::ColourIds::rotarySliderFillColourId, juce::Colour::fromFloatRGBA(0.392f, 0.584f, 0.929f, 1.0f).darker(1.0f));
        setColour(juce::Slider::ColourIds::thumbColourId, juce::Colour::fromFloatRGBA(0.392f, 0.584f, 0.929f, 1.0f).darker(1.0f));
    }
    
    else
    {
        setColour(juce::Slider::ColourIds::backgroundColourId, juce::Colours::black.brighter(0.1));
        setColour(juce::Slider::ColourIds::rotarySliderFillColourId, newColor.withAlpha(0.6f));
        setColour(juce::Slider::ColourIds::thumbColourId, newColor.withAlpha(0.6f));
        setColour(juce::Slider::ColourIds::textBoxTextColourId, newColor.withAlpha(0.6f));
    }

    forceShadow();
}

void viator_gui::Dial::updateShadowColor(juce::Colour newColor, float newAlpha)
{
    shadowProperties.colour = newColor.withAlpha(newAlpha);
    dialShadow.setShadowProperties (shadowProperties);
    setComponentEffect(&dialShadow);
    forceShadow();
}

void viator_gui::Dial::paint(juce::Graphics &g)
{
    juce::Slider::paint(g);
}

void viator_gui::Dial::resized()
{
    juce::Slider::resized();
}
