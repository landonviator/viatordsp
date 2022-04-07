/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
MeterDemoAudioProcessorEditor::MeterDemoAudioProcessorEditor (MeterDemoAudioProcessor& p)
    : AudioProcessorEditor (&p), audioProcessor (p), meters(audioProcessor)
{
    addAndMakeVisible(meters);
    
    setSize (600, 600);
}

MeterDemoAudioProcessorEditor::~MeterDemoAudioProcessorEditor()
{
}

//==============================================================================
void MeterDemoAudioProcessorEditor::paint (juce::Graphics& g)
{
    juce::Rectangle<int> background = getLocalBounds();
    g.setGradientFill(juce::ColourGradient::vertical(juce::Colour::fromFloatRGBA(0.18f, 0.20f, 0.24f, 1.0), getHeight() * 0.25, juce::Colour::fromFloatRGBA(0.18f, 0.20f, 0.24f, 1.0).darker(0.15), getHeight() * 0.75));
    g.fillRect(background);

    g.setFont (juce::Font (36.0f));
    g.setColour (juce::Colours::dimgrey);
    g.drawText ("Meter", getLocalBounds(), juce::Justification::centredTop, true);
    
}

void MeterDemoAudioProcessorEditor::resized()
{
    meters.setBounds(200, 200, 256, 384);
}
