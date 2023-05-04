#include <JuceHeader.h>
#include "Menu.h"

namespace viator_gui
{
    Menu::Menu()
    {
        setLookAndFeel(&_customLAF);
        setColour(juce::ComboBox::ColourIds::textColourId, _textColor);
        setColour(juce::ComboBox::ColourIds::arrowColourId, _textColor);
        setColour(juce::ComboBox::ColourIds::backgroundColourId, _noColor);
        setColour(juce::ComboBox::ColourIds::outlineColourId, _noColor);
        getLookAndFeel().setColour(juce::ComboBox::ColourIds::textColourId, _textColor);
        getLookAndFeel().setColour(juce::ComboBox::ColourIds::buttonColourId, _textColor);
        getLookAndFeel().setColour(juce::ComboBox::ColourIds::arrowColourId, _textColor);
        getLookAndFeel().setColour(juce::ComboBox::ColourIds::focusedOutlineColourId, _noColor);
        getLookAndFeel().setColour(juce::PopupMenu::ColourIds::backgroundColourId, _innerBgColor);
        getLookAndFeel().setColour(juce::PopupMenu::ColourIds::textColourId, _textColor);
        getLookAndFeel().setColour(juce::PopupMenu::ColourIds::highlightedTextColourId, _textColor.brighter(1.0f));
        getLookAndFeel().setColour(juce::PopupMenu::ColourIds::highlightedBackgroundColourId, juce::Colours::whitesmoke.withAlpha(0.1f));
    }

    Menu::~Menu()
    {
        setLookAndFeel(nullptr);
    }

    void Menu::mouseEnter(const juce::MouseEvent &event)
    {
        setColour(juce::ComboBox::ColourIds::backgroundColourId, juce::Colours::whitesmoke.withAlpha(0.05f));
        repaint();
    }

    void Menu::mouseExit(const juce::MouseEvent &event)
    {
        setColour(juce::ComboBox::ColourIds::backgroundColourId, _noColor);
        repaint();
    }
}
