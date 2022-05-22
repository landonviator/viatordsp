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
    menuSlider1.setLookAndFeel(&customMenuSlider);
}

SettingsPage::~SettingsPage()
{
    menuSlider1.setLookAndFeel(nullptr);
}

void SettingsPage::paint (juce::Graphics& g)
{
    g.fillAll(juce::Colour::fromRGB(32, 34, 37));
}

void SettingsPage::resized()
{
    auto topMargin = getHeight() * 0.1;
    auto leftMargin = getWidth() * 0.1;
    auto sliderWidth = getWidth() * 0.5;
    auto sliderHeight = getWidth() * 0.1f;
    
    menuSlider1.setBounds(leftMargin, topMargin, sliderWidth, sliderHeight);
}
