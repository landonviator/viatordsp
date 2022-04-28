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
    
    addAndMakeVisible(cpuLabel);
    cpuLabel.setText("CPU", juce::dontSendNotification);
    
    addAndMakeVisible(gainSlider);
    gainSlider.setSliderStyle(juce::Slider::SliderStyle::RotaryVerticalDrag);
    gainSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 72, 36);
    gainSlider.setRange(0.0, 20.0, 0.01);
    gainSlider.setColour(juce::Slider::ColourIds::rotarySliderFillColourId, juce::Colours::whitesmoke.darker(1.5f));
    gainSlider.setColour(juce::Slider::ColourIds::rotarySliderOutlineColourId, juce::Colours::black.brighter(0.1));
    gainSlider.setColour(juce::Slider::ColourIds::trackColourId, juce::Colours::whitesmoke.darker(1.5f));
    gainSlider.setColour(juce::Slider::ColourIds::textBoxOutlineColourId, juce::Colours::black.withAlpha(0.0f));
    gainSlider.setColour(juce::Slider::ColourIds::textBoxTextColourId, juce::Colours::whitesmoke.darker(1.5f));
    gainSlider.setColour(juce::Slider::ColourIds::thumbColourId, juce::Colour::fromFloatRGBA(0.392f, 0.584f, 0.929f, 1.0f).darker(1.0f));
    
    gainAttach = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.treeState, "input", gainSlider);
}
