/*
  ==============================================================================

    ButtonProps.cpp
    Created: 10 Jun 2022 8:09:32pm
    Author:  Landon Viator

  ==============================================================================
*/

#include "../../../PluginEditor.h"

void LVTemplateAudioProcessorEditor::setTextButtonProps(juce::TextButton &button)
{
    addAndMakeVisible(button);
    button.setClickingTogglesState(true);
    button.setColour(juce::ComboBox::outlineColourId, m_textAccentColor);
    button.setColour(juce::TextButton::ColourIds::textColourOnId, m_textAccentColor);
    button.setColour(juce::TextButton::ColourIds::textColourOffId, m_textAccentColor);
    button.setColour(juce::TextButton::ColourIds::buttonColourId, juce::Colours::transparentBlack);
    button.setColour(juce::TextButton::ColourIds::buttonOnColourId, juce::Colours::transparentBlack);
    setSettingsButtonProps();
}
