/*
  ==============================================================================

    LabelsCommon.cpp
    Created: 14 Jun 2022 6:16:19pm
    Author:  Landon Viator

  ==============================================================================
*/

#include "../../PluginEditor.h"

void ParaEQDemoAudioProcessorEditor::setLabelProps(juce::Label &label)
{
    addAndMakeVisible(label);
    label.setJustificationType(juce::Justification::centred);
    label.setFont(juce::Font("Helvetica", 16.0, juce::Font::FontStyleFlags::bold));
    label.setColour(juce::Label::ColourIds::outlineColourId, juce::Colours::transparentBlack);
    label.setColour(juce::Label::ColourIds::textColourId, juce::Colours::whitesmoke.withAlpha(0.5f));
    label.setColour(juce::Label::ColourIds::backgroundColourId, juce::Colours::transparentBlack);
}
