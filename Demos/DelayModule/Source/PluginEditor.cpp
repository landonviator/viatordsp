/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
DelayModuleAudioProcessorEditor::DelayModuleAudioProcessorEditor (DelayModuleAudioProcessor& p)
    : AudioProcessorEditor (&p), audioProcessor (p)
{
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    setSize (600, 400);
}

DelayModuleAudioProcessorEditor::~DelayModuleAudioProcessorEditor()
{
}

//==============================================================================
void DelayModuleAudioProcessorEditor::paint (juce::Graphics& g)
{
    juce::Rectangle<int> background = getLocalBounds();
    g.setGradientFill(juce::ColourGradient::vertical(juce::Colour::fromFloatRGBA(0.18f, 0.20f, 0.24f, 1.0), 300 * .01, juce::Colour::fromFloatRGBA(0.12f, 0.14f, 0.18f, 1.0), 300 * .99));
    g.fillRect(background);

    g.setColour (juce::Colours::dimgrey);
    g.setFont (36.0f);
    g.drawFittedText ("Delay", getLocalBounds(), juce::Justification::centredTop, 1);
}

void DelayModuleAudioProcessorEditor::resized()
{
    // This is generally where you'll want to lay out the positions of any
    // subcomponents in your editor..
}
