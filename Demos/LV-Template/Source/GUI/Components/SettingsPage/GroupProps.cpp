/*
  ==============================================================================

    GroupProps.cpp
    Created: 13 Jun 2022 4:44:24pm
    Author:  Landon Viator

  ==============================================================================
*/

#include "SettingsPage.h"

void SettingsPage::setGroupProps(juce::GroupComponent &group)
{
    addAndMakeVisible(group);
    group.setColour(juce::GroupComponent::ColourIds::outlineColourId, juce::Colours::whitesmoke.withAlpha(0.1f));
}
