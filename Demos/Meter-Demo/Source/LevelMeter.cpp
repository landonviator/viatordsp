/*
  ==============================================================================

    LevelMeter.cpp
    Created: 1 Apr 2022 6:21:06pm
    Author:  Landon Viator

  ==============================================================================
*/

#include <JuceHeader.h>
#include "LevelMeter.h"

//==============================================================================
LevelMeter::LevelMeter(MeterDemoAudioProcessor& p) : audioProcessor (p)
{
    addAndMakeVisible(leftMeter);
    leftMeter.setSliderStyle(juce::Slider::SliderStyle::LinearBarVertical);
    leftMeter.setRange(-60.0, 0.0, 0.05);
    leftMeter.setSkewFactorFromMidPoint(-21.0);
    leftMeter.setTextBoxStyle(juce::Slider::TextBoxAbove, true, 96, 72);
    leftMeter.setScrollWheelEnabled(false);
    
    leftMeter.setColour(juce::Slider::ColourIds::textBoxOutlineColourId, juce::Colours::black.withAlpha(0.0f));
    leftMeter.setColour(juce::Slider::ColourIds::trackColourId, juce::Colour::fromFloatRGBA(0.392f, 0.584f, 0.929f, 0.4f));
    leftMeter.setColour(juce::Slider::ColourIds::textBoxTextColourId, juce::Colours::whitesmoke.withAlpha(0.0f));
    
    addAndMakeVisible(rightMeter);
    rightMeter.setSliderStyle(juce::Slider::SliderStyle::LinearBarVertical);
    rightMeter.setRange(-60.0, 0.0, 0.05);
    rightMeter.setSkewFactorFromMidPoint(-21.0);
    rightMeter.setTextBoxStyle(juce::Slider::TextBoxAbove, true, 96, 72);
    rightMeter.setScrollWheelEnabled(false);
    
    rightMeter.setColour(juce::Slider::ColourIds::textBoxOutlineColourId, juce::Colours::black.withAlpha(0.0f));
    rightMeter.setColour(juce::Slider::ColourIds::trackColourId, juce::Colour::fromFloatRGBA(0.392f, 0.584f, 0.929f, 0.4f));
    rightMeter.setColour(juce::Slider::ColourIds::textBoxTextColourId, juce::Colours::whitesmoke.withAlpha(0.0f));
    
    addAndMakeVisible(meterToggle);
    meterToggle.setButtonText("Is RMS");
    meterToggle.onClick = [this]()
    {
        audioProcessor.setMeterType(meterToggle.getToggleState());
    };
    
    addAndMakeVisible(leftSliderValueLabel);
    leftSliderValueLabel.setJustificationType(juce::Justification::centred);
    leftSliderValueLabel.attachToComponent(&leftMeter, false);
    
    startTimerHz(30);
}

LevelMeter::~LevelMeter()
{
}

void LevelMeter::paint (juce::Graphics& g)
{
    g.setColour(juce::Colours::black.withAlpha(0.5f));
    g.fillRect(leftMeter.getX(), leftMeter.getY(), leftMeter.getWidth(), leftMeter.getHeight());
    g.fillRect(rightMeter.getX(), rightMeter.getY(), rightMeter.getWidth(), rightMeter.getHeight());
    
    g.setColour(juce::Colours::whitesmoke.withAlpha(0.5f));
    g.setFont (juce::Font (12.0f));
    
    for (int i = 0; i < 10; i++)
    {
        float lineY = rightMeter.getY() - rightMeter.getPositionOfValue(0.0) + rightMeter.getPositionOfValue(i * -3) + 1;
        
        if (i % 3 == 0)
        {
            g.drawText(meterNumbers[i/3], leftMeter.getX() + leftMeter.getWidth() * 0.9, lineY - 8, 64, 24, juce::Justification::centredTop);
        }
    }
}

void LevelMeter::resized()
{
    leftMeter.setBounds(0, 60, 64, 256);
    rightMeter.setBounds(leftMeter.getX() + leftMeter.getWidth() * 1.75, 60, 64, 256);
    meterToggle.setBounds(leftMeter.getX() + leftMeter.getWidth(), leftMeter.getY() - 50, 72, 24);
}

void LevelMeter::setLabelColorLogic()
{
    if (leftSliderValueLabel.getTextValue() >= -0.1)
    {
        leftSliderValueLabel.setColour(juce::Label::ColourIds::textColourId, juce::Colours::indianred);
    }
      
    else if (leftSliderValueLabel.getTextValue() < 0.0 && leftSliderValueLabel.getTextValue() >= -18.0)
    {
        leftSliderValueLabel.setColour(juce::Label::ColourIds::textColourId, juce::Colours::orange);
    }
      
    else
    {
        leftSliderValueLabel.setColour(juce::Label::ColourIds::textColourId, juce::Colours::green.brighter(0.5));
    }
}
