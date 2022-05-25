/*
  ==============================================================================

    MasterColorComp.cpp
    Created: 24 May 2022 11:07:02pm
    Author:  Landon Viator

  ==============================================================================
*/

#include <JuceHeader.h>
#include "MasterColorComp.h"

//==============================================================================
MasterColorComp::MasterColorComp()
{
    /** Color Button Red */
    addAndMakeVisible(redButton);
    redButton.setColour(juce::TextButton::ColourIds::buttonColourId, juce::Colour::fromRGB(214, 87, 69));
    redButton.onClick = [this]()
    {
        masterColor = juce::Colour::fromRGB(214, 87, 69);
        getParentComponent()->getParentComponent()->repaint();
    };
    
    redButton.setLookAndFeel(&customColorButtonLAF);
    
    /** Color Button Green */
    addAndMakeVisible(greenButton);
    greenButton.setColour(juce::TextButton::ColourIds::buttonColourId, juce::Colour::fromRGB(101, 202, 122).withAlpha(0.75f));
    greenButton.onClick = [this]()
    {
        masterColor = juce::Colour::fromRGB(101, 202, 122).withAlpha(0.75f);
        getParentComponent()->getParentComponent()->repaint();
    };
    greenButton.setLookAndFeel(&customColorButtonLAF);
    
    /** Color Button Blue */
    addAndMakeVisible(blueButton);
    blueButton.setColour(juce::TextButton::ColourIds::buttonColourId, juce::Colour::fromRGB(82, 150, 213));
    blueButton.onClick = [this]()
    {
        masterColor = juce::Colour::fromRGB(82, 150, 213);
        getParentComponent()->getParentComponent()->repaint();
    };
    
    blueButton.setLookAndFeel(&customColorButtonLAF);
    
    /** Color Button Orange */
    addAndMakeVisible(orangeButton);
    orangeButton.setColour(juce::TextButton::ColourIds::buttonColourId, juce::Colour::fromRGB(216, 131, 59));
    orangeButton.onClick = [this]()
    {
        masterColor = juce::Colour::fromRGB(216, 131, 59);
        getParentComponent()->getParentComponent()->repaint();
    };
    
    orangeButton.setLookAndFeel(&customColorButtonLAF);
    
    /** Color Button Yellow */
    addAndMakeVisible(yellowButton);
    yellowButton.setColour(juce::TextButton::ColourIds::buttonColourId, juce::Colour::fromRGB(234, 198, 69));
    yellowButton.onClick = [this]()
    {
        masterColor = juce::Colour::fromRGB(234, 198, 69).withAlpha(0.9f);
        getParentComponent()->getParentComponent()->repaint();
    };
    
    yellowButton.setLookAndFeel(&customColorButtonLAF);
    
    /** Color Button Purple */
    addAndMakeVisible(purpleButton);
    purpleButton.setColour(juce::TextButton::ColourIds::buttonColourId, juce::Colour::fromRGB(146, 92, 177));
    purpleButton.onClick = [this]()
    {
        masterColor = juce::Colour::fromRGB(146, 92, 177);
        getParentComponent()->getParentComponent()->repaint();
    };
    
    purpleButton.setLookAndFeel(&customColorButtonLAF);
    
    /** Color Button Asphalt */
    addAndMakeVisible(asphaltButton);
    asphaltButton.setColour(juce::TextButton::ColourIds::buttonColourId, juce::Colour::fromRGB(56, 72, 92));
    asphaltButton.onClick = [this]()
    {
        masterColor = juce::Colour::fromRGB(56, 72, 92);
        getParentComponent()->getParentComponent()->repaint();
    };
    
    asphaltButton.setLookAndFeel(&customColorButtonLAF);
    
    /** Color Button Black */
    addAndMakeVisible(blackButton);
    blackButton.setColour(juce::TextButton::ColourIds::buttonColourId, juce::Colour::fromRGB(0, 0, 0));
    blackButton.onClick = [this]()
    {
        masterColor = juce::Colour::fromRGB(0, 0, 0);
        getParentComponent()->getParentComponent()->repaint();
    };
    
    blackButton.setLookAndFeel(&customColorButtonLAF);
    
    addAndMakeVisible(colorsLabel);
    colorsLabel.setText("Plugin Accent Color", juce::dontSendNotification);
    colorsLabel.setColour(juce::Label::ColourIds::textColourId, juce::Colours::whitesmoke.withAlpha(0.5f));
}

MasterColorComp::~MasterColorComp()
{
    redButton.setLookAndFeel(nullptr);
    greenButton.setLookAndFeel(nullptr);
    blueButton.setLookAndFeel(nullptr);
    orangeButton.setLookAndFeel(nullptr);
    yellowButton.setLookAndFeel(nullptr);
    purpleButton.setLookAndFeel(nullptr);
    asphaltButton.setLookAndFeel(nullptr);
    blackButton.setLookAndFeel(nullptr);
}

void MasterColorComp::paint (juce::Graphics& g)
{
    g.setColour(juce::Colours::black.withAlpha(0.2f));
    g.fillRoundedRectangle(getWidth() * 0.05, getHeight() * 0.05, getWidth() * 0.9, getHeight() * 0.9, 2.0f);
    
    g.setColour(juce::Colours::black.withAlpha(0.3f));
    g.drawRoundedRectangle(getWidth() * 0.05, getHeight() * 0.05, getWidth() * 0.9, getHeight() * 0.9, 2.0f, 2.0f);
}

void MasterColorComp::resized()
{
    auto leftMargin = getWidth() * 0.1;
    auto topMargin = getHeight() * 0.3f;
    auto colorSize = getWidth() * 0.045f;
    auto buttonSpaceBetween = 1.25;
    auto compWidth = getWidth() * 0.2;
    auto compHeight = getHeight() * 0.6;
    auto labelTopMargin = getHeight() * 0.23f;
    
    redButton.setBounds(leftMargin, topMargin, colorSize, colorSize);
    greenButton.setBounds(redButton.getX() + redButton.getWidth() * buttonSpaceBetween, topMargin, colorSize, colorSize);
    blueButton.setBounds(greenButton.getX() + greenButton.getWidth() * buttonSpaceBetween, topMargin, colorSize, colorSize);
    orangeButton.setBounds(blueButton.getX() + blueButton.getWidth() * buttonSpaceBetween, topMargin, colorSize, colorSize);
    yellowButton.setBounds(orangeButton.getX() + orangeButton.getWidth() * buttonSpaceBetween, topMargin, colorSize, colorSize);
    purpleButton.setBounds(yellowButton.getX() + yellowButton.getWidth() * buttonSpaceBetween, topMargin, colorSize, colorSize);
    asphaltButton.setBounds(purpleButton.getX() + purpleButton.getWidth() * buttonSpaceBetween, topMargin, colorSize, colorSize);
    blackButton.setBounds(asphaltButton.getX() + asphaltButton.getWidth() * buttonSpaceBetween, topMargin, colorSize, colorSize);
    
    colorsLabel.setBounds(blackButton.getX() + blackButton.getWidth() * 1.3f, labelTopMargin, compWidth * 2.0, compHeight);
    colorsLabel.setFont(juce::Font ("Helvetica", getWidth() * 0.025f, juce::Font::FontStyleFlags::bold));
}
