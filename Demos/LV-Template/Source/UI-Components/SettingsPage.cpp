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
    /** Color Button Red */
    addAndMakeVisible(color1Button);
    color1Button.setColour(juce::TextButton::ColourIds::buttonColourId, juce::Colour::fromRGB(255, 118, 117).withAlpha(0.6f));
    color1Button.onClick = [this]()
    {
        masterColor = juce::Colour::fromRGB(255, 118, 117);
        getParentComponent()->repaint();
    };
    
    color1Button.setLookAndFeel(&customColorButtonLAF);
    
    /** Color Button Green */
    addAndMakeVisible(color2Button);
    color2Button.setColour(juce::TextButton::ColourIds::buttonColourId, juce::Colour::fromRGB(85, 239, 196).withAlpha(0.6f));
    color2Button.onClick = [this]()
    {
        masterColor = juce::Colour::fromRGB(0, 184, 148);
        getParentComponent()->repaint();
    };
    color2Button.setLookAndFeel(&customColorButtonLAF);
    
    /** Color Button Blue */
    addAndMakeVisible(color3Button);
    color3Button.setColour(juce::TextButton::ColourIds::buttonColourId, juce::Colour::fromRGB(116, 185, 255).withAlpha(0.6f));
    color3Button.onClick = [this]()
    {
        masterColor = juce::Colour::fromRGB(116, 185, 255);
        getParentComponent()->repaint();
    };
    
    color3Button.setLookAndFeel(&customColorButtonLAF);
    
    /** Color Button Black */
    addAndMakeVisible(color4Button);
    color4Button.setColour(juce::TextButton::ColourIds::buttonColourId, juce::Colour::fromRGB(0, 0, 0));
    color4Button.onClick = [this]()
    {
        masterColor = juce::Colour::fromRGB(0, 0, 0);
        getParentComponent()->repaint();
    };
    
    color4Button.setLookAndFeel(&customColorButtonLAF);
    
    addAndMakeVisible(tooltipSettingsComp);
}

SettingsPage::~SettingsPage()
{
    menuSlider1.setLookAndFeel(nullptr);
    color1Button.setLookAndFeel(nullptr);
    color2Button.setLookAndFeel(nullptr);
    color3Button.setLookAndFeel(nullptr);
    color4Button.setLookAndFeel(nullptr);
}

void SettingsPage::paint (juce::Graphics& g)
{
    //Background
    g.fillAll(juce::Colour::fromRGB(45, 44, 51));
    
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
    auto colorSize = getWidth() * 0.04f;
    auto buttonSpaceBetween = 1.25;
    
    rowheight = getHeight() * 0.075;
    
    tooltipSettingsComp.setBounds(0, rowheight, getWidth(), rowheight);
    
    //Colors
    auto buttonTopMargin = tooltipSettingsComp.getY() + tooltipSettingsComp.getHeight() * 2.0f;
    color1Button.setBounds(100 * buttonSpaceBetween, buttonTopMargin, colorSize, colorSize);
    color2Button.setBounds(color1Button.getX() + color1Button.getWidth() * buttonSpaceBetween, buttonTopMargin, colorSize, colorSize);
    color3Button.setBounds(color2Button.getX() + color2Button.getWidth() * buttonSpaceBetween, buttonTopMargin, colorSize, colorSize);
    color4Button.setBounds(color3Button.getX() + color3Button.getWidth() * buttonSpaceBetween, buttonTopMargin, colorSize, colorSize);
}

bool SettingsPage::getShouldUseToolTips()
{
    return tooltipSettingsComp.getShouldUseToolTips();
}
