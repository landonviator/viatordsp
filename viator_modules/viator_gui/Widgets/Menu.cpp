#include "Menu.h"

viator_gui::Menu::Menu()
{
    setLookAndFeel(&customMenuLAF);
    
    setColour(juce::ComboBox::ColourIds::backgroundColourId, juce::Colours::black.brighter(0.1));
    setColour(juce::ComboBox::ColourIds::outlineColourId, juce::Colours::whitesmoke.withAlpha(0.0f));
    setColour(juce::ComboBox::ColourIds::focusedOutlineColourId, juce::Colours::black.withAlpha(0.5f));
    setColour(juce::ComboBox::ColourIds::textColourId, juce::Colours::whitesmoke.withAlpha(0.5f));
    setColour(juce::ComboBox::ColourIds::arrowColourId, juce::Colours::whitesmoke.withAlpha(0.5f));

    getLookAndFeel().setColour(juce::PopupMenu::backgroundColourId, juce::Colours::black.brighter(0.1));
    getLookAndFeel().setColour(juce::PopupMenu::highlightedBackgroundColourId, juce::Colours::skyblue.withAlpha(0.1f));
    getLookAndFeel().setColour(juce::PopupMenu::textColourId, juce::Colours::whitesmoke.withAlpha(0.5f));
    getLookAndFeel().setColour(juce::PopupMenu::highlightedTextColourId, juce::Colours::whitesmoke.withAlpha(0.5f));

    setJustificationType(juce::Justification::centred);
}

viator_gui::Menu::~Menu()
{
    setLookAndFeel(nullptr);
}

void viator_gui::Menu::timerCallback()
{
    setColour(juce::ComboBox::ColourIds::backgroundColourId, juce::Colours::black.brighter(0.1));
}

void viator_gui::Menu::mouseEnter (const juce::MouseEvent& event)
{
    setColour(juce::ComboBox::ColourIds::backgroundColourId, juce::Colours::black.brighter(0.12));
    startTimer(1000);
}

void viator_gui::Menu::mouseExit (const juce::MouseEvent& event)
{
    setColour(juce::ComboBox::ColourIds::backgroundColourId, juce::Colours::black.brighter(0.1));
    stopTimer();
}
