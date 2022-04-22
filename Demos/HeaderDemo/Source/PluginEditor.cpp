/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
HeaderDemoAudioProcessorEditor::HeaderDemoAudioProcessorEditor (HeaderDemoAudioProcessor& p)
    : AudioProcessorEditor (&p), audioProcessor (p)
{
    uiConstructor();
}

HeaderDemoAudioProcessorEditor::~HeaderDemoAudioProcessorEditor()
{

}

//==============================================================================
void HeaderDemoAudioProcessorEditor::paint (juce::Graphics& g)
{
    uiPaint(g);
}

void HeaderDemoAudioProcessorEditor::resized()
{
    uiResized();
}
