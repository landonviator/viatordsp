#include "Dial.h"

viator_gui::Dial::Dial(const juce::String& sliderName)
{
    dial.setName(sliderName);
    
    // Slider props
    dial.setRange(-15.0, 15.0, 0.1);
    dial.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 64, 32);
    dial.setTextValueSuffix(" dB");
    dial.setSliderStyle(juce::Slider::SliderStyle::RotaryVerticalDrag);
    dial.setDoubleClickReturnValue(true, 0.0);
    dial.setColour(juce::Slider::ColourIds::textBoxOutlineColourId, juce::Colours::transparentBlack);
    dial.setColour(juce::Slider::ColourIds::backgroundColourId, _auxBackgroundColor.withAlpha(0.35f));
    dial.setColour(juce::Slider::ColourIds::rotarySliderOutlineColourId, _auxBackgroundColor.withAlpha(0.35f));
    dial.setColour(juce::Slider::ColourIds::textBoxTextColourId, _mainTextColor);
    dial.setColour(juce::Slider::ColourIds::trackColourId, _widgetFillColor.withAlpha(0.75f));
    dial.setColour(juce::Slider::ColourIds::rotarySliderFillColourId, _widgetFillColor.withAlpha(0.75f));
    dial.setColour(juce::Slider::ColourIds::thumbColourId, _auxTextColor);
    dial.setLookAndFeel(&_customDial);
    addAndMakeVisible(dial);
}

viator_gui::Dial::~Dial()
{
    setLookAndFeel(nullptr);
}

void viator_gui::Dial::paint (juce::Graphics& g)
{
}

void viator_gui::Dial::resized()
{
    dial.setBounds(getLocalBounds());
}

void viator_gui::Dial::setDialTextBoxWidth(const float newWidth)
{
    dial.setTextBoxStyle(juce::Slider::TextBoxBelow, false, newWidth, 32);
}

void viator_gui::Dial::setDialColors(juce::Colour mainText,
                                     juce::Colour widgetFill,
                                     juce::Colour auxBG,
                                     juce::Colour auxText)
{
    dial.setColour(juce::Slider::ColourIds::backgroundColourId, auxBG);
    dial.setColour(juce::Slider::ColourIds::rotarySliderOutlineColourId, auxBG);
    dial.setColour(juce::Slider::ColourIds::textBoxTextColourId, mainText);
    dial.setColour(juce::Slider::ColourIds::trackColourId, widgetFill);
    dial.setColour(juce::Slider::ColourIds::rotarySliderFillColourId, widgetFill);
    dial.setColour(juce::Slider::ColourIds::thumbColourId, auxText);
}

void viator_gui::Dial::setDialValueType(viator_gui::CustomDial::ValueType newValueType)
{
    _customDial.setDialValueType(newValueType);
    repaint();
}
