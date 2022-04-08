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
    sliderShadowProperties.radius = 8;
    sliderShadowProperties.offset = juce::Point<int> (0, 0);
    sliderShadowProperties.colour = juce::Colours::black.withAlpha(1.0f);
    sliderShadow.setShadowProperties (sliderShadowProperties);
    
    addAndMakeVisible(leftMeter);
    leftMeter.setSliderStyle(juce::Slider::SliderStyle::LinearVertical);
    leftMeter.setRange(-60.0, 0.0, 0.05);
    leftMeter.setSkewFactorFromMidPoint(-21.0);
    leftMeter.setTextBoxStyle(juce::Slider::TextBoxBelow, true, 96, 72);
    leftMeter.setScrollWheelEnabled(false);
    
    leftMeter.setColour(juce::Slider::ColourIds::textBoxOutlineColourId, juce::Colours::black.withAlpha(0.0f));
    leftMeter.setColour(juce::Slider::ColourIds::thumbColourId, juce::Colours::black.withAlpha(0.0f));
    leftMeter.setColour(juce::Slider::ColourIds::trackColourId, juce::Colour::fromFloatRGBA(0.18f, 0.20f, 0.24f, 1.0));
    leftMeter.setColour(juce::Slider::ColourIds::textBoxTextColourId, juce::Colours::whitesmoke.withAlpha(0.0f));
    leftMeter.setColour(juce::Slider::ColourIds::backgroundColourId, juce::Colours::black.withAlpha(0.0f));
    
    addAndMakeVisible(leftSliderValueLabel);
    leftSliderValueLabel.setFont(12.0f);
    leftSliderValueLabel.attachToComponent(&leftMeter, false);
    leftSliderValueLabel.setJustificationType(juce::Justification::centred);
    leftSliderValueLabel.setText("0.0", juce::dontSendNotification);
    
    addAndMakeVisible(rightMeter);
    rightMeter.setSliderStyle(juce::Slider::SliderStyle::LinearVertical);
    rightMeter.setRange(-60.0, 0.0, 0.05);
    rightMeter.setSkewFactorFromMidPoint(-21.0);
    rightMeter.setTextBoxStyle(juce::Slider::TextBoxBelow, true, 96, 72);
    rightMeter.setScrollWheelEnabled(false);
    
    rightMeter.setColour(juce::Slider::ColourIds::textBoxOutlineColourId, juce::Colours::black.withAlpha(0.0f));
    rightMeter.setColour(juce::Slider::ColourIds::thumbColourId, juce::Colours::black.withAlpha(0.0f));
    rightMeter.setColour(juce::Slider::ColourIds::trackColourId, juce::Colour::fromFloatRGBA(0.18f, 0.20f, 0.24f, 1.0));
    rightMeter.setColour(juce::Slider::ColourIds::textBoxTextColourId, juce::Colours::whitesmoke.withAlpha(0.0f));
    rightMeter.setColour(juce::Slider::ColourIds::backgroundColourId, juce::Colours::black.withAlpha(0.0f));
    
    addAndMakeVisible(rightSliderValueLabel);
    rightSliderValueLabel.setFont(12.0f);
    rightSliderValueLabel.attachToComponent(&rightMeter, false);
    rightSliderValueLabel.setJustificationType(juce::Justification::centred);
    rightSliderValueLabel.setText("0.0", juce::dontSendNotification);
    
    addAndMakeVisible(meterToggle);
    meterToggle.setButtonText("Is RMS");
    meterToggle.onClick = [this]()
    {
        audioProcessor.setMeterType(meterToggle.getToggleState());
    };
    
    addAndMakeVisible(leftSliderValueLabel);
    leftSliderValueLabel.setJustificationType(juce::Justification::centred);
    leftSliderValueLabel.attachToComponent(&leftMeter, false);
    
    leftMeter.setComponentEffect(&sliderShadow);
    rightMeter.setComponentEffect(&sliderShadow);
    
    startTimerHz(30);
}

LevelMeter::~LevelMeter()
{
}

void LevelMeter::paint (juce::Graphics& g)
{
    g.setColour(juce::Colours::black.brighter(0.1f));
    g.fillRect(getLocalBounds());
    
    g.setColour(juce::Colours::whitesmoke.withAlpha(0.5f));
    g.setFont (juce::Font (12.0f));
    
    for (int i = 0; i < 19; i++)
    {
        float lineY = rightMeter.getY() + rightMeter.getPositionOfValue(i * -3) - 2;
        
        if (i % 3 == 0)
        {
            g.drawText(meterNumbers[i/3], 0, lineY - 6, 64, 24, juce::Justification::centredTop);
            
            g.setColour(juce::Colours::whitesmoke.withAlpha(0.25f));
            g.drawLine(48, lineY, rightMeter.getX() + rightMeter.getWidth(), lineY);
        }
        
    }
}

void LevelMeter::resized()
{
    leftMeter.setBounds(48, 64, 64, getHeight());
    rightMeter.setBounds(leftMeter.getX() + leftMeter.getWidth() * 0.6, leftMeter.getY(), 64, leftMeter.getHeight());
    meterToggle.setBounds(rightMeter.getX() + rightMeter.getWidth() * 1.25, leftMeter.getY(), 72, 24);
}

void LevelMeter::setLabelColorLogic(juce::Label& label)
{
    if (label.getTextValue() >= -0.1)
    {
        label.setColour(juce::Label::ColourIds::textColourId, juce::Colours::indianred);
    }
      
    else if (label.getTextValue() < 0.0 && leftSliderValueLabel.getTextValue() >= -18.0)
    {
        label.setColour(juce::Label::ColourIds::textColourId, juce::Colours::orange);
    }
      
    else
    {
        label.setColour(juce::Label::ColourIds::textColourId, juce::Colours::green.brighter(0.5));
    }
}
