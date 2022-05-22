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
HeaderComponent::HeaderComponent(LVTemplateAudioProcessor& p) : audioProcessor(p)
{
    startTimerHz(10);
    
    addAndMakeVisible(settingsButton);
    settingsButtonProps();
    
    addAndMakeVisible(cpuLabel);
    cpuLabel.setColour(juce::Label::ColourIds::textColourId, juce::Colours::whitesmoke.withAlpha(0.5f));
    cpuLabel.setLookAndFeel(&customLabelLAF);
}

HeaderComponent::~HeaderComponent()
{
    stopTimer();
    
    cpuLabel.setLookAndFeel(nullptr);
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
    auto spaceBetween = 1.25;
    
    cpuLabel.setFont(juce::Font ("Helvetica", getHeight() * 0.35f, juce::Font::FontStyleFlags::bold));
    
    settingsButton.setBounds(rightMargin, buttonTopMargin, buttonWidth, buttonHeight);
    cpuLabel.setBounds(settingsButton.getX() - settingsButton.getWidth() * spaceBetween, buttonTopMargin, buttonWidth, buttonHeight);
}

bool HeaderComponent::getSettingsButtonToggleState()
{
    return settingsButton.getToggleState();
}
