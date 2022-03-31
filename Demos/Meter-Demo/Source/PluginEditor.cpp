/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
MeterDemoAudioProcessorEditor::MeterDemoAudioProcessorEditor (MeterDemoAudioProcessor& p)
    : AudioProcessorEditor (&p), audioProcessor (p)
{
    addAndMakeVisible(leftMeter);
    leftMeter.setSliderStyle(juce::Slider::SliderStyle::LinearBarVertical);
    leftMeter.setRange(-60.0, 0.0, 0.05);
    leftMeter.setSkewFactorFromMidPoint(-21.0);
    leftMeter.setTextBoxStyle(juce::Slider::TextBoxAbove, true, 96, 72);
    leftMeter.setScrollWheelEnabled(false);
    
    addAndMakeVisible(rightMeter);
    rightMeter.setSliderStyle(juce::Slider::SliderStyle::LinearBarVertical);
    rightMeter.setRange(-60.0, 0.0, 0.05);
    rightMeter.setSkewFactorFromMidPoint(-21.0);
    rightMeter.setTextBoxStyle(juce::Slider::TextBoxAbove, true, 96, 72);
    rightMeter.setScrollWheelEnabled(false);
    
    addAndMakeVisible(meterToggle);
    meterToggle.setButtonText("Is RMS");
    meterToggle.onClick = [this]()
    {
        audioProcessor.setMeterType(meterToggle.getToggleState());
    };
    
    addAndMakeVisible(sliderValueLabel);
    sliderValueLabel.setText("-12", juce::dontSendNotification);
    
    startTimerHz(30);
    
    setSize (600, 600);
}

MeterDemoAudioProcessorEditor::~MeterDemoAudioProcessorEditor()
{
}

//==============================================================================
void MeterDemoAudioProcessorEditor::paint (juce::Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    juce::Rectangle<int> background = getLocalBounds();
    g.setGradientFill(juce::ColourGradient::vertical(juce::Colour::fromFloatRGBA(0.18f, 0.20f, 0.24f, 1.0), getHeight() * 0.25, juce::Colour::fromFloatRGBA(0.18f, 0.20f, 0.24f, 1.0).darker(0.15), getHeight() * 0.75));
    g.fillRect(background);

    g.setFont (juce::Font (36.0f));
    g.setColour (juce::Colours::dimgrey);
    g.drawText ("Meter", getLocalBounds(), juce::Justification::centredTop, true);
    
    for (int i = 0; i < 17; i++)
    {
            g.drawText("-", rightMeter.getX() + rightMeter.getWidth(), rightMeter.getY() - rightMeter.getPositionOfValue(0.0) + rightMeter.getPositionOfValue(i * -3), 64, 32, juce::Justification::left);
    }
}

void MeterDemoAudioProcessorEditor::resized()
{
    leftMeter.setBounds(200, 200, 64, 256);
    rightMeter.setBounds(leftMeter.getX() + leftMeter.getWidth(), 200, 64, 256);
    //sliderValueLabel.setBounds(rightMeter.getX() + 16, rightMeter.getY() + rightMeter.getPositionOfValue(-12.0), 64, 32);
    meterToggle.setBounds(leftMeter.getX() + leftMeter.getWidth(), leftMeter.getY() - 50, 72, 72);
}
