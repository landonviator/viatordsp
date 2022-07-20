#include "Label.h"

viator_gui::Label::Label()
{
    
}

viator_gui::Label::Label(juce::String text)
{
    setText(text, juce::dontSendNotification);
    setColour(0x1000280, juce::Colour::fromFloatRGBA(0, 0, 0, 0));
    setColour(0x1000282, juce::Colour::fromFloatRGBA(0, 0, 0, 0));
    setColour(juce::Label::ColourIds::textColourId, juce::Colours::whitesmoke.darker(0.5f));
    setJustificationType(juce::Justification::centred);
    setFont(juce::Font ("Helvetica", getWidth() * 0.18, juce::Font::FontStyleFlags::bold));
}

void viator_gui::Label::paint(juce::Graphics& g)
{
    juce::Label::paint(g);
}

void viator_gui::Label::resized()
{
    juce::Label::resized();
    setFont(juce::Font ("Helvetica", getWidth() * 0.12, juce::Font::FontStyleFlags::bold));
}

