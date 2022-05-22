/*
  ==============================================================================

    SettingsButtonLogic.cpp
    Created: 21 May 2022 11:30:54pm
    Author:  Landon Viator

  ==============================================================================
*/

#include "../../UI-Components/HeaderComponent.h"

void HeaderComponent::settingsButtonProps()
{
    settingsButton.setClickingTogglesState(true);
    settingsButton.setColour(juce::TextButton::ColourIds::buttonColourId, juce::Colour::fromRGB(54, 57, 63));
    settingsButton.setColour(juce::TextButton::ColourIds::buttonOnColourId, juce::Colour::fromRGB(54, 57, 63).brighter(0.2));
    settingsButton.setLookAndFeel(&customSettingsButtonLAF);
    settingsButton.onClick = [this]()
    {
        getParentComponent()->resized();
    };
}
