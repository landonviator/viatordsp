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
{
//    addAndMakeVisible(slider1);
//    slider1.setSliderStyle(juce::Slider::SliderStyle::LinearVertical);
//    slider1.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 72, 36);
//    slider1.setColour(juce::Slider::ColourIds::backgroundColourId, juce::Colours::black.brighter(0.1f));
//    slider1.setColour(juce::Slider::ColourIds::trackColourId, slider1.findColour(juce::Slider::ColourIds::thumbColourId));
//    slider1.setColour(juce::Slider::ColourIds::thumbColourId, juce::Colours::whitesmoke);
//    slider1.setRange(-24.0, 24.0, 0.01);
//    slider1.setTextValueSuffix(" dB");
//    slider1.setDoubleClickReturnValue(true, 0.0);
//
//    addAndMakeVisible(slider2);
//    slider2.setSliderStyle(juce::Slider::SliderStyle::LinearVertical);
//    slider2.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 72, 36);
//    slider2.setColour(juce::Slider::ColourIds::backgroundColourId, juce::Colours::black.brighter(0.1f));
//    slider2.setColour(juce::Slider::ColourIds::trackColourId, slider2.findColour(juce::Slider::ColourIds::thumbColourId));
//    slider2.setColour(juce::Slider::ColourIds::thumbColourId, juce::Colours::whitesmoke);
//    slider2.setRange(-24.0, 24.0, 0.01);
//    slider2.setTextValueSuffix(" dB");
//    slider2.setDoubleClickReturnValue(true, 0.0);
//
//    addAndMakeVisible(slider3);
//    slider3.setSliderStyle(juce::Slider::SliderStyle::LinearVertical);
//    slider3.setColour(juce::Slider::ColourIds::backgroundColourId, juce::Colours::black.brighter(0.1f));
//    slider3.setColour(juce::Slider::ColourIds::trackColourId, slider3.findColour(juce::Slider::ColourIds::thumbColourId));
//    slider3.setColour(juce::Slider::ColourIds::thumbColourId, juce::Colours::whitesmoke);
//    slider3.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 72, 36);
//    slider3.setRange(-24.0, 24.0, 0.01);
//    slider3.setTextValueSuffix(" dB");
//    slider3.setDoubleClickReturnValue(true, 0.01);
    
    setSliderProps(slider1);
    setSliderProps(slider2);
    setSliderProps(slider3);
    
    setSize(600, 600);
}

ViatorguidemoAudioProcessorEditor::~ViatorguidemoAudioProcessorEditor()
{
}

//==============================================================================
void ViatorguidemoAudioProcessorEditor::paint (juce::Graphics& g)
{
    //Image layer from Illustrator
    g.fillAll(juce::Colour::fromRGB(40, 42, 54));
}

void ViatorguidemoAudioProcessorEditor::resized()
{
    auto topMargin = getHeight() * 0.12f;
    auto leftMargin = getWidth() * 0.1f;
    auto sliderHeight = getHeight() * 0.77f;
    auto sliderWidth = getWidth() * 0.27f;
    
    slider1.setBounds(leftMargin, topMargin, sliderWidth, sliderHeight);
    slider2.setBounds(slider1.getX() + slider1.getWidth(), topMargin, sliderWidth, sliderHeight);
    slider3.setBounds(slider2.getX() + slider2.getWidth(), topMargin, sliderWidth, sliderHeight);
}

void ViatorguidemoAudioProcessorEditor::setSliderProps(juce::Slider &slider)
{
    addAndMakeVisible(slider);
    slider.setSliderStyle(juce::Slider::SliderStyle::LinearVertical);
    slider.setColour(juce::Slider::ColourIds::backgroundColourId, juce::Colours::black.brighter(0.1f));
    slider.setColour(juce::Slider::ColourIds::trackColourId, slider3.findColour(juce::Slider::ColourIds::thumbColourId));
    slider.setColour(juce::Slider::ColourIds::thumbColourId, juce::Colours::whitesmoke);
    slider.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 72, 36);
    slider.setRange(-24.0, 24.0, 0.01);
    slider.setTextValueSuffix(" dB");
    slider.setDoubleClickReturnValue(true, 0.01);
}
