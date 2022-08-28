/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
GUIPlaygroundAudioProcessorEditor::GUIPlaygroundAudioProcessorEditor (GUIPlaygroundAudioProcessor& p)
    : AudioProcessorEditor (&p), audioProcessor (p)
{
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    setSize (900, 600);
}

GUIPlaygroundAudioProcessorEditor::~GUIPlaygroundAudioProcessorEditor()
{
}

//==============================================================================
void GUIPlaygroundAudioProcessorEditor::paint (juce::Graphics& g)
{
    g.setGradientFill(juce::ColourGradient::vertical(juce::Colour::fromRGB(40, 42, 53).darker(0.35f), getHeight(), juce::Colour::fromRGB(40, 42, 53).brighter(0.02), getHeight() * 0.4));
    g.fillRect(getLocalBounds());
}

void GUIPlaygroundAudioProcessorEditor::resized()
{
    // This is generally where you'll want to lay out the positions of any
    // subcomponents in your editor..
}
