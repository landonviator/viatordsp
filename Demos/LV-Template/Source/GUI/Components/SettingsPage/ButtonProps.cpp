/*
  ==============================================================================

    ButtonProps.cpp
    Created: 13 Jun 2022 4:26:51pm
    Author:  Landon Viator

  ==============================================================================
*/

#include "SettingsPage.h"

void SettingsPage::setTextButtonProps(juce::TextButton &button)
{
    addAndMakeVisible(button);
    button.setClickingTogglesState(true);
    button.setColour(juce::ComboBox::outlineColourId, juce::Colours::transparentBlack);
    button.setColour(juce::TextButton::ColourIds::textColourOnId, juce::Colours::whitesmoke);
    button.setColour(juce::TextButton::ColourIds::textColourOffId, juce::Colours::whitesmoke.withAlpha(0.5f));
    button.setColour(juce::TextButton::ColourIds::buttonColourId, juce::Colour::fromRGB(53, 55, 70));
    button.setColour(juce::TextButton::ColourIds::buttonOnColourId, juce::Colour::fromRGB(53, 55, 70).brighter(0.1));
    
    /** Individual Button Props */
    setGlowButtonProps();
    setGradientToggleProps();
    setDiscordBtnProps();
    setPatreonBtnProps();
    setTwitchBtnProps();
}
