/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
ParaEQDemoAudioProcessorEditor::ParaEQDemoAudioProcessorEditor (ParaEQDemoAudioProcessor& p)
    : AudioProcessorEditor (&p), audioProcessor (p)
{
    initWindowSize();
    
    setSliderProps(band1GainDial);
    setSliderProps(band1CutoffDial);
    setSliderProps(band1QDial);
}

ParaEQDemoAudioProcessorEditor::~ParaEQDemoAudioProcessorEditor()
{
}

//==============================================================================
void ParaEQDemoAudioProcessorEditor::paint (juce::Graphics& g)
{
    g.fillAll(juce::Colour::fromRGB(40, 42, 54));
}

void ParaEQDemoAudioProcessorEditor::resized()
{
    const auto leftMargin = getWidth() * 0.1;
    const auto topMargin = getHeight() * 0.4;
    const auto dialSize = getWidth() * 0.1;
    
    band1GainDial.setBounds(leftMargin, topMargin, dialSize, dialSize);
    band1CutoffDial.setBounds(leftMargin, band1GainDial.getY() + band1GainDial.getHeight(), dialSize, dialSize);
    band1QDial.setBounds(leftMargin, band1CutoffDial.getY() + band1CutoffDial.getHeight(), dialSize, dialSize);
}
