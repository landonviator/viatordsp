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
    
    if (button.getComponentID() == "settings")
    {
        button.setColour(juce::ComboBox::outlineColourId, m_textAccentColor);
        button.setColour(juce::TextButton::ColourIds::textColourOnId, m_textAccentColor);
        button.setColour(juce::TextButton::ColourIds::textColourOffId, m_textAccentColor);
        button.setColour(juce::TextButton::ColourIds::buttonColourId, juce::Colours::transparentBlack);
        button.setColour(juce::TextButton::ColourIds::buttonOnColourId, juce::Colours::transparentBlack);
    }
    
    else
    {
        button.setColour(juce::ComboBox::outlineColourId, juce::Colours::transparentBlack);
        button.setColour(juce::TextButton::ColourIds::textColourOnId, juce::Colours::whitesmoke);
        button.setColour(juce::TextButton::ColourIds::textColourOffId, juce::Colours::whitesmoke.withAlpha(0.5f));
        button.setColour(juce::TextButton::ColourIds::buttonColourId, juce::Colour::fromRGB(53, 55, 70));
        button.setColour(juce::TextButton::ColourIds::buttonOnColourId, juce::Colour::fromRGB(53, 55, 70).brighter(0.1));
    }
    
    
    /** Individual Button Props */
    setSettingsButtonProps();
}
