/*
  ==============================================================================

    SettingsPage.cpp
    Created: 21 May 2022 11:48:39pm
    Author:  Landon Viator

  ==============================================================================
*/

#include <JuceHeader.h>
#include "SettingsPage.h"

//==============================================================================
SettingsPage::SettingsPage()
{
    addAndMakeVisible(menuSlider1);
    menuSlider1.setSliderStyle(juce::Slider::SliderStyle::LinearHorizontal);
    menuSlider1.setTextBoxStyle(juce::Slider::TextBoxLeft, false, 36, 24);
    menuSlider1.setRange(0.0, 10.0, 1.0);
    menuSlider1.setTooltip("This is a slider tooltip");
    menuSlider1.setLookAndFeel(&customMenuSlider);
    
    addAndMakeVisible(toolTipToggle);
    toolTipToggle.setLookAndFeel(&customToggleButton);
    toolTipToggle.onClick = [this]()
    {
        shouldUseToolTips = toolTipToggle.getToggleState();
    };
    
    addAndMakeVisible(tooltipLabel);
    tooltipLabel.setText("Show ToolTips?", juce::dontSendNotification);
    tooltipLabel.setColour(juce::Label::ColourIds::textColourId, juce::Colours::whitesmoke.withAlpha(0.5f));
}

SettingsPage::~SettingsPage()
{
    menuSlider1.setLookAndFeel(nullptr);
    toolTipToggle.setLookAndFeel(nullptr);
}

void SettingsPage::paint (juce::Graphics& g)
{
    //Background
    g.fillAll(juce::Colour::fromRGB(32, 34, 37));
    
    //Title Text
    g.setColour(juce::Colours::whitesmoke.withAlpha(0.5f));
    g.setFont(juce::Font ("Helvetica", getHeight() * 0.035, juce::Font::FontStyleFlags::bold));
    g.drawFittedText("Settings", getLocalBounds(), juce::Justification::centredTop, 1);
}

void SettingsPage::resized()
{
    auto topMargin = getHeight() * 0.1;
    auto leftMargin = getWidth() * 0.1;
    auto sliderWidth = getWidth() * 0.5;
    auto sliderHeight = getWidth() * 0.1f;
    auto buttonwidth = getWidth() * 0.08;
    auto buttonHeight = getHeight() * 0.039;
    
    //Tooltip Toggle
    toolTipToggle.setBounds(leftMargin, topMargin, buttonwidth, buttonHeight);
    
    //Tooltip Label
    tooltipLabel.setBounds(toolTipToggle.getX() + toolTipToggle.getWidth(), topMargin, buttonwidth * 2.0, buttonHeight);
    tooltipLabel.setFont(juce::Font ("Helvetica", getWidth() * 0.02, juce::Font::FontStyleFlags::bold));
    
    //Menu Slider 1
    menuSlider1.setBounds(leftMargin, toolTipToggle.getY() + toolTipToggle.getHeight(), sliderWidth, sliderHeight);
}

bool SettingsPage::getShouldUseToolTips()
{
    return shouldUseToolTips;
}
