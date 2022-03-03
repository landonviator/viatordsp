/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
ViatorguidemoAudioProcessorEditor::ViatorguidemoAudioProcessorEditor (ViatorguidemoAudioProcessor& p)
    : AudioProcessorEditor (&p), audioProcessor (p)
, fader(" dB", -10.0, 10.0, 0.1, 0.0)
{
    addAndMakeVisible(fader);
    
    setSize (900, 300);
}

ViatorguidemoAudioProcessorEditor::~ViatorguidemoAudioProcessorEditor()
{
}

//==============================================================================
void ViatorguidemoAudioProcessorEditor::paint (juce::Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (juce::Colours::black.brighter(0.2));

    g.setColour (juce::Colours::white);
    g.setFont (24.0f);
    g.drawFittedText ("Gui Widgets Demo", getLocalBounds(), juce::Justification::centredTop, 1);
}

void ViatorguidemoAudioProcessorEditor::resized()
{
    auto topMargin = 12;
    auto leftMargin = 2;
    
    fader.setBounds(leftMargin, topMargin, 128, 256);
}
