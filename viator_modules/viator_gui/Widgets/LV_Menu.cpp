#include "LV_Menu.h"

viator_gui::LV_Menu::LV_Menu()
{
    setLookAndFeel(&customMenu);
    setColour(juce::ComboBox::ColourIds::backgroundColourId, juce::Colours::black.brighter(0.1f).withAlpha(0.0f));
    setColour(juce::ComboBox::ColourIds::outlineColourId, juce::Colours::whitesmoke.withAlpha(0.0f));
    setColour(juce::ComboBox::ColourIds::focusedOutlineColourId, juce::Colours::black.withAlpha(0.5f));
    setColour(juce::ComboBox::ColourIds::textColourId, juce::Colours::whitesmoke.withAlpha(0.5f));
    setColour(juce::ComboBox::ColourIds::arrowColourId, juce::Colours::skyblue.darker(0.5f));

    getLookAndFeel().setColour(juce::PopupMenu::backgroundColourId, juce::Colours::black.brighter(0.1f));
    getLookAndFeel().setColour(juce::PopupMenu::highlightedBackgroundColourId, juce::Colours::skyblue.withAlpha(0.1f));
    getLookAndFeel().setColour(juce::PopupMenu::textColourId, juce::Colours::whitesmoke.withAlpha(0.5f));
    getLookAndFeel().setColour(juce::PopupMenu::highlightedTextColourId, juce::Colours::skyblue);

    setJustificationType(juce::Justification::centred);
}

viator_gui::LV_Menu::~LV_Menu()
{
    setLookAndFeel(nullptr);
}

void viator_gui::LV_Menu::timerCallback()
{
    setColour(juce::ComboBox::ColourIds::backgroundColourId, juce::Colours::black.brighter(0.1f).withAlpha(0.0f));
}

void viator_gui::LV_Menu::mouseEnter (const juce::MouseEvent& event)
{
    setColour(juce::ComboBox::ColourIds::backgroundColourId, juce::Colours::whitesmoke.withAlpha(0.05f));
    startTimer(1000);
}

void viator_gui::LV_Menu::mouseExit (const juce::MouseEvent& event)
{
    setColour(juce::ComboBox::ColourIds::backgroundColourId, juce::Colours::black.brighter(0.1f).withAlpha(0.0f));
    stopTimer();
}
