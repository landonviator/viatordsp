/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
LVTemplateAudioProcessorEditor::LVTemplateAudioProcessorEditor (LVTemplateAudioProcessor& p)
    : AudioProcessorEditor (&p), audioProcessor (p)
, headerComponent(audioProcessor)
{
    uiConstructor();
}

LVTemplateAudioProcessorEditor::~LVTemplateAudioProcessorEditor()
{
    stopTimer();
}

//==============================================================================
void LVTemplateAudioProcessorEditor::paint (juce::Graphics& g)
{
    uiPaint(g);
}

void LVTemplateAudioProcessorEditor::resized()
{
    uiResized();
}

void LVTemplateAudioProcessorEditor::showToolTip(bool shouldShowTips)
{
    tooltipWindow.setEnabled(shouldShowTips);
    tooltipWindow.setVisible(shouldShowTips);
}
