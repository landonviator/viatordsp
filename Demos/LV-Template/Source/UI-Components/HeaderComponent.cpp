/*
  ==============================================================================

    HeaderComponent.cpp
    Created: 21 May 2022 10:21:27pm
    Author:  Landon Viator

  ==============================================================================
*/

#include <JuceHeader.h>
#include "HeaderComponent.h"

//==============================================================================
HeaderComponent::HeaderComponent()
{
    addAndMakeVisible(settingsButton);
    settingsButtonProps();
}

HeaderComponent::~HeaderComponent()
{
}

void HeaderComponent::paint (juce::Graphics& g)
{
    //Header
    juce::Rectangle<float> headerRect;
    headerRect.setBounds(0.0f, 0.0f, getWidth(), getHeight());
    g.setColour(juce::Colour::fromRGB(32, 34, 37));
    g.fillRect(headerRect);
    
    g.setColour(juce::Colours::whitesmoke.darker(1.0f).darker(1.0f));
    g.drawLine(0, getHeight(), getWidth(), getHeight(), 2.0f);
}

void HeaderComponent::resized()
{
    auto rightMargin = getWidth() * 0.95;
    auto buttonTopMargin = getHeight() * 0.125f;
    auto buttonWidth = getWidth() * 0.04;
    auto buttonHeight = getHeight() * 0.75;
    
    settingsButton.setBounds(rightMargin, buttonTopMargin, buttonWidth, buttonHeight);
}

bool HeaderComponent::getSettingsButtonToggleState()
{
    return settingsButton.getToggleState();
}
