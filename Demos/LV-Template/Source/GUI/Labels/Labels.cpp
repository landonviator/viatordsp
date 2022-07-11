/*
  ==============================================================================

    Labels.cpp
    Created: 9 Jul 2022 10:45:15pm
    Author:  Landon Viator

  ==============================================================================
*/

#include "../../PluginEditor.h"

void LVTemplateAudioProcessorEditor::setModuleLabelProps(juce::Label &label)
{
    addAndMakeVisible(label);
    label.setColour(juce::Label::ColourIds::textColourId, m_mainCompColor);
}

void LVTemplateAudioProcessorEditor::setDisLabelProps(viator_gui::Label &label)
{
    addAndMakeVisible(label);
}
