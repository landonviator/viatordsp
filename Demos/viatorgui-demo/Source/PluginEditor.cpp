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
, dial(" dB", -10.0, 10.0, 0.1, 0.0)
, fader(" dB", -10.0, 10.0, 0.1, 0.0)
{
    addAndMakeVisible(dial);
    addAndMakeVisible(fader);
    
    addAndMakeVisible(border);
    border.setText("Border");
    
    addAndMakeVisible(button);
    button.setButtonText("Button");
    
    addAndMakeVisible(phase);
    phase.setToggleStyle(viator_gui::Toggle::ToggleStyle::kPhase);
    
    addAndMakeVisible(power);
    
    setSize (900, 400);
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
    auto topMargin = 64;
    auto leftMargin = 16;
    
    dial.setBounds(leftMargin, topMargin, 128, 256);
    fader.setBounds(dial.getX() + dial.getWidth(), topMargin, 128, 256);
    border.setBounds(fader.getX() + fader.getWidth(), topMargin, dial.getWidth(), dial.getHeight());
    button.setBounds(border.getX() + border.getWidth() + 32, topMargin, 90, 30);
    phase.setBounds(button.getX() + button.getWidth() + 32, topMargin, 40, 40);
    power.setBounds(phase.getX() + phase.getWidth() + 10, topMargin, 40, 40);
}
