#include "Dial.h"
namespace viator_gui
{

Dial::Dial(const juce::String& sliderName)
{
    // Slider props
    setName(sliderName);
    setTextBoxStyle(juce::Slider::TextBoxBelow, false, 64, 32);
    setSliderStyle(juce::Slider::SliderStyle::RotaryVerticalDrag);
    setDoubleClickReturnValue(true, 0.0);
    setColour(juce::Slider::ColourIds::textBoxOutlineColourId, juce::Colours::transparentBlack);
    setColour(juce::Slider::ColourIds::backgroundColourId, _auxBackgroundColor.withAlpha(0.35f));
    setColour(juce::Slider::ColourIds::rotarySliderOutlineColourId, _auxBackgroundColor.withAlpha(0.35f));
    setColour(juce::Slider::ColourIds::textBoxTextColourId, _mainTextColor);
    setColour(juce::Slider::ColourIds::trackColourId, _widgetFillColor.withAlpha(0.75f));
    setColour(juce::Slider::ColourIds::rotarySliderFillColourId, _widgetFillColor.withAlpha(0.75f));
    setColour(juce::Slider::ColourIds::thumbColourId, _auxTextColor);
    setLookAndFeel(&_customDial);
}

Dial::Dial (const juce::String& sliderName, const juce::Image& filmStrip)
{
    // Slider props
    setName(sliderName);
    
    setSliderStyle(juce::Slider::SliderStyle::RotaryVerticalDrag);
    setDoubleClickReturnValue(true, 0.0);
    setColour(juce::Slider::ColourIds::textBoxOutlineColourId, juce::Colours::transparentBlack);
    setColour(juce::Slider::ColourIds::textBoxTextColourId, _mainTextColor);
    setLookAndFeel(&customDialLabelLAF);
    
    // film strip
    _filmStrip = filmStrip;
    frameHeight = filmStrip.getHeight() / _numFrames;
    frameWidth = filmStrip.getWidth();
}

Dial::~Dial()
{
    setLookAndFeel(nullptr);
}

void Dial::paint (juce::Graphics& g)
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
        juce::Slider::paint(g);
    }
}

void Dial::resized()
{
    juce::Slider::resized();
}

void Dial::setDialTextBoxWidth(const float newWidth)
{
    setTextBoxStyle(juce::Slider::TextBoxBelow, false, newWidth, 16);
}

void Dial::setDialColors(juce::Colour mainText,
                                     juce::Colour widgetFill,
                                     juce::Colour auxBG,
                                     juce::Colour auxText)
{
    setColour(juce::Slider::ColourIds::backgroundColourId, auxBG);
    setColour(juce::Slider::ColourIds::rotarySliderOutlineColourId, auxBG);
    setColour(juce::Slider::ColourIds::textBoxTextColourId, mainText);
    setColour(juce::Slider::ColourIds::trackColourId, widgetFill);
    setColour(juce::Slider::ColourIds::rotarySliderFillColourId, widgetFill);
    setColour(juce::Slider::ColourIds::thumbColourId, auxText);
}

void Dial::setDialValueType(CustomDial::ValueType newValueType)
{
    _customDial.setDialValueType(newValueType);
    repaint();
}

void Dial::setDialValueType(CustomDialLabel::ValueType newValueType)
{
    customDialLabelLAF.setDialValueType(newValueType);
    repaint();
}

}
