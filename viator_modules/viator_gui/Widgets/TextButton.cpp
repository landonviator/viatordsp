#include <JuceHeader.h>
#include "TextButton.h"

namespace viator_gui
{
    TextButton::TextButton()
    {
        setClickingTogglesState(true);
        setColour(juce::TextButton::ColourIds::buttonColourId, juce::Colours::transparentBlack);
        setColour(juce::TextButton::ColourIds::buttonOnColourId, juce::Colours::transparentBlack);
        setColour(juce::ComboBox::outlineColourId, juce::Colours::transparentBlack);
        setColour(juce::TextButton::ColourIds::textColourOnId, _textColor);
        setColour(juce::TextButton::ColourIds::textColourOffId, _textColor);
        setLookAndFeel(&_customLAF);
    }

    TextButton::~TextButton()
    {
        setLookAndFeel(nullptr);
    }

    void TextButton::paint (juce::Graphics& g)
    {
        juce::TextButton::paint(g);
    }

    void TextButton::resized()
    {
        juce::TextButton::resized();
    }
}
