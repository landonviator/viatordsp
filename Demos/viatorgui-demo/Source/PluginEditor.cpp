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
, dial(" dB", "Gain", -10.0, 10.0, 0.1, 0.0)
{
    addAndMakeVisible(dial);
    
    addAndMakeVisible(border);
    border.setText("Border");
    
    setSize (900, 900);
}

ViatorguidemoAudioProcessorEditor::~ViatorguidemoAudioProcessorEditor()
{
}

//==============================================================================
void ViatorguidemoAudioProcessorEditor::paint (juce::Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    juce::Rectangle<int> background = AudioProcessorEditor::getLocalBounds();
    g.setGradientFill(juce::ColourGradient::vertical(juce::Colour::fromFloatRGBA(0.18f, 0.20f, 0.24f, 1.0), getHeight() * low, juce::Colour::fromFloatRGBA(0.18f, 0.20f, 0.24f, 1.0).darker(0.25), getHeight() * high));
    g.fillRect(background);

    g.setColour (juce::Colours::white);
    g.setFont (24.0f);
    g.drawFittedText ("Gui Widgets Demo", getLocalBounds(), juce::Justification::centredTop, 1);
}

void ViatorguidemoAudioProcessorEditor::resized()
{
    auto topMargin = 64;
    auto leftMargin = 16;
    auto dialSize = getWidth() * 0.25;
    
    dial.setBounds(leftMargin, topMargin, dialSize, dialSize);
    border.setBounds(dial.getX() + dial.getWidth() * 1.5, topMargin, dial.getWidth() * 1.5, dial.getHeight() * 3.0);
}
