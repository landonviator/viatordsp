#include "Label.h"

viator_gui::Label::Label()
{
    setColour(juce::Label::ColourIds::backgroundColourId, juce::Colours::transparentBlack);
    setColour(juce::Label::ColourIds::backgroundWhenEditingColourId, juce::Colours::transparentBlack);
    setColour(juce::Label::ColourIds::outlineColourId, juce::Colours::transparentBlack);
    setColour(juce::Label::ColourIds::textColourId, viator_utils::gui_utils::Colors::_textColor);
    setColour(juce::Label::ColourIds::textWhenEditingColourId, viator_utils::gui_utils::Colors::_textColor);
    setColour(juce::Label::ColourIds::textColourId, juce::Colours::whitesmoke.darker(0.5f));
    setJustificationType(juce::Justification::centred);
}

viator_gui::Label::Label(juce::String text)
{
    setText(text, juce::dontSendNotification);
    setColour(0x1000280, juce::Colour::fromFloatRGBA(0, 0, 0, 0));
    setColour(0x1000282, juce::Colour::fromFloatRGBA(0, 0, 0, 0));
    setColour(juce::Label::ColourIds::textColourId, juce::Colours::whitesmoke.darker(0.5f));
    setJustificationType(juce::Justification::centred);
}

void viator_gui::Label::paint(juce::Graphics& g)
{
    juce::Label::paint(g);
}

void viator_gui::Label::resized()
{
    juce::Label::resized();
}

