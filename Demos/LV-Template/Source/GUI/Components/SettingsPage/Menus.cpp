/*
  ==============================================================================

    Menus.cpp
    Created: 11 Jun 2022 12:30:04am
    Author:  Landon Viator

  ==============================================================================
*/

#include "SettingsPage.h"

void SettingsPage::setMenuProps(juce::ComboBox &menu)
{
    addAndMakeVisible(menu);
    menu.setColour(juce::ComboBox::ColourIds::backgroundColourId, juce::Colour::fromRGB(53, 55, 70));
    menu.setColour(juce::ComboBox::ColourIds::outlineColourId, juce::Colours::whitesmoke.withAlpha(0.0f));
    menu.setColour(juce::ComboBox::ColourIds::focusedOutlineColourId, juce::Colours::black.withAlpha(0.5f));
    menu.setColour(juce::ComboBox::ColourIds::textColourId, juce::Colours::whitesmoke.withAlpha(0.5f));
    menu.setColour(juce::ComboBox::ColourIds::arrowColourId, juce::Colours::whitesmoke.withAlpha(0.5f));

    menu.getLookAndFeel().setColour(juce::PopupMenu::backgroundColourId, juce::Colour::fromRGB(53, 55, 70));
    menu.getLookAndFeel().setColour(juce::PopupMenu::highlightedBackgroundColourId, juce::Colours::skyblue.withAlpha(0.1f));
    menu.getLookAndFeel().setColour(juce::PopupMenu::textColourId, juce::Colours::whitesmoke.withAlpha(0.5f));
    menu.getLookAndFeel().setColour(juce::PopupMenu::highlightedTextColourId, juce::Colours::whitesmoke.withAlpha(0.5f));

    menu.setJustificationType(juce::Justification::centred);
}
