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
    setName("Settings Page");
    addAndMakeVisible(tooltipSettingsComp);
    addAndMakeVisible(masterColorComp);
}

SettingsPage::~SettingsPage()
{
    
}

void SettingsPage::paint (juce::Graphics& g)
{
    //Background
    //g.fillAll(juce::Colour::fromRGB(45, 44, 51));
    g.fillAll(juce::Colours::black.withAlpha(0.7f));
    
    //Title Text
    g.setColour(juce::Colours::whitesmoke.withAlpha(0.5f));
    g.setFont(juce::Font ("Helvetica", getHeight() * 0.035, juce::Font::FontStyleFlags::bold));
    g.drawFittedText("Settings", getLocalBounds().withY(getHeight() * 0.02f), juce::Justification::centredTop, 1);
}

void SettingsPage::resized()
{
    rowheight = getHeight() * 0.075;
    
    tooltipSettingsComp.setBounds(0, rowheight, getWidth(), rowheight);
    
    masterColorComp.setBounds(0, tooltipSettingsComp.getY() + tooltipSettingsComp.getHeight(), getWidth(), rowheight);
}

bool SettingsPage::getShouldUseToolTips()
{
    return tooltipSettingsComp.getShouldUseToolTips();
}
