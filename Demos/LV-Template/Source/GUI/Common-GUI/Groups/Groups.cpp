/*
  ==============================================================================

    Groups.cpp
    Created: 11 Jun 2022 11:32:10pm
    Author:  Landon Viator

  ==============================================================================
*/

#include "../../../PluginEditor.h"

void LVTemplateAudioProcessorEditor::setGroupProps(juce::GroupComponent &group)
{
    addAndMakeVisible(group);
    group.setColour(juce::GroupComponent::ColourIds::outlineColourId, juce::Colours::whitesmoke.withAlpha(0.1f));
}
