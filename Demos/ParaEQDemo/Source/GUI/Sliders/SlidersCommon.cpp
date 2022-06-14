/*
  ==============================================================================

    SlidersCommon.cpp
    Created: 9 Jun 2022 7:18:39pm
    Author:  Landon Viator

  ==============================================================================
*/

#include "../../PluginEditor.h"

void ParaEQDemoAudioProcessorEditor::setSliderProps(juce::Slider &slider)
{
    addAndMakeVisible(slider);
    slider.setSliderStyle(juce::Slider::SliderStyle::RotaryVerticalDrag);
    slider.setTextBoxStyle(juce::Slider::NoTextBox, true, 0, 0);
    slider.setColour(juce::Slider::ColourIds::textBoxOutlineColourId, juce::Colours::transparentBlack);
    slider.setColour(juce::Slider::ColourIds::rotarySliderOutlineColourId, juce::Colour::fromRGB(53, 55, 70).withAlpha(0.6f));
    slider.setColour(juce::Slider::ColourIds::rotarySliderFillColourId, juce::Colour::fromRGB(98, 114, 163).withAlpha(0.9f));
    slider.setColour(juce::Slider::ColourIds::thumbColourId, juce::Colours::transparentBlack);
}
