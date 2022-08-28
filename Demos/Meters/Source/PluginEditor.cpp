/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
MetersAudioProcessorEditor::MetersAudioProcessorEditor (MetersAudioProcessor& p)
    : AudioProcessorEditor (&p), audioProcessor (p)
{
    startTimer(10);
    addAndMakeVisible(meter);
    meter.setSliderStyle(juce::Slider::SliderStyle::LinearHorizontal);
    meter.setColour(juce::Slider::ColourIds::backgroundColourId, juce::Colours::black.brighter(0.1));
    meter.setColour(juce::Slider::ColourIds::trackColourId, juce::Colours::whitesmoke.withAlpha(0.5f));
    meter.setColour(juce::Slider::ColourIds::thumbColourId, juce::Colours::transparentBlack);
    meter.setColour(juce::Slider::ColourIds::textBoxTextColourId, juce::Colours::transparentBlack);
    meter.setColour(juce::Slider::ColourIds::textBoxOutlineColourId, juce::Colours::transparentBlack);
    meter.setRange(-60.0, 0.0, 0.1);
    meter.setSkewFactorFromMidPoint(-48.0);
    setSize (800, 600);
}

MetersAudioProcessorEditor::~MetersAudioProcessorEditor()
{
}

//==============================================================================
void MetersAudioProcessorEditor::paint (juce::Graphics& g)
{
    g.setGradientFill(juce::ColourGradient::vertical(juce::Colour::fromRGB(40, 42, 53).darker(0.75f), getHeight(), juce::Colour::fromRGB(40, 42, 53).brighter(0.02f), getHeight() * 0.4));
    g.fillRect(getLocalBounds());
    
    g.setColour(juce::Colours::white);
    for (int i = -60; i < 0; ++i)
    {
        if (i % 3 == 0)
        {
            auto x = 206;
            auto y = 1.26;
            g.drawText("|", meter.getPositionOfValue(i) + x, meter.getY() * y, 5, 5, juce::Justification::centred);
        }
    }
}

void MetersAudioProcessorEditor::resized()
{
    meter.setBounds(getLocalBounds().withSizeKeepingCentre(getWidth() * 0.5, getHeight() * 0.25));
}
