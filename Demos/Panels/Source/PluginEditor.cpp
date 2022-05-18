/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
PanelsAudioProcessorEditor::PanelsAudioProcessorEditor (PanelsAudioProcessor& p)
    : AudioProcessorEditor (&p), audioProcessor (p)
{
    addAndMakeVisible(listBox);
    listBox.setModel(&sourceModel);
    
    setSize (1200, 600);
}

PanelsAudioProcessorEditor::~PanelsAudioProcessorEditor()
{
}

//==============================================================================
void PanelsAudioProcessorEditor::paint (juce::Graphics& g)
{
}

void PanelsAudioProcessorEditor::resized()
{
    listBox.setBounds(getLocalBounds().withSizeKeepingCentre(getWidth() * 0.5, getHeight() * 0.5));
    listBox.setRowHeight(100);
}
