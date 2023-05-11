#include <JuceHeader.h>
#include "TextButton.h"

namespace viator_gui
{
    TextButton::TextButton()
    {
        setClickingTogglesState(true);
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
