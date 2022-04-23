/*
  ==============================================================================

    UI-Constructor.cpp
    Created: 24 Oct 2021 1:40:44am
    Author:  Landon Viator

  ==============================================================================
*/

#include "../PluginEditor.h"

void HeaderDemoAudioProcessorEditor::uiConstructor()
{
    initWindow();
    
    startTimerHz(10);
    
    addAndMakeVisible(cpuLabel);
    cpuLabel.setText("CPU", juce::dontSendNotification);
    cpuLabel.setColour(juce::Label::ColourIds::textColourId, juce::Colours::whitesmoke.darker(1.0f));
    
    addAndMakeVisible(cpuButton);
    cpuButton.setClickingTogglesState(true);
    cpuButtonAttach = std::make_unique<juce::AudioProcessorValueTreeState::ButtonAttachment>(audioProcessor.treeState, "cpu", cpuButton);
    cpuButton.setButtonText("CPU");
    cpuButton.setColour(juce::TextButton::ColourIds::buttonColourId, juce::Colour::fromFloatRGBA(0.18f, 0.20f, 0.24f, 1.0).darker(1.0f).darker(1.0f));
    cpuButton.setColour(juce::TextButton::ColourIds::buttonOnColourId, juce::Colour::fromFloatRGBA(0.18f, 0.20f, 0.24f, 1.0).darker(0.5f));
    cpuButton.setColour(juce::TextButton::ColourIds::textColourOffId, juce::Colours::whitesmoke.darker(1.0f));
    cpuButton.setColour(juce::TextButton::ColourIds::textColourOnId, juce::Colours::whitesmoke.darker(1.0f));
    cpuButton.setColour(0x1000c00, juce::Colours::whitesmoke.withAlpha(0.06f));
    
    addAndMakeVisible(msMenu);
    msMenu.setTextWhenNothingSelected("M / S");
    msMenu.addItem("Stereo", 1);
    msMenu.addItem("Mid", 2);
    msMenu.addItem("Sides", 3);
    
   // addAndMakeVisible(dial);
}
