/*
  ==============================================================================

    Header.cpp
    Created: 17 Jul 2022 2:46:42pm
    Author:  Landon Viator

  ==============================================================================
*/

#include <JuceHeader.h>
#include "Header.h"

//==============================================================================
Header::Header()
{
    // Init settings button
    setSettingsButtonProps();
}

Header::~Header()
{
    m_settingsButton.setLookAndFeel(nullptr);
}

void Header::paint (juce::Graphics& g)
{
    // Init Header
    g.setColour(juce::Colours::black.withAlpha(0.2f));
    g.fillRect(0, 0, getWidth(), getHeight());
    g.setColour(juce::Colours::black.withAlpha(0.1f));
    g.drawLine(0, getHeight(), getWidth(), getHeight(), 1.0);
    g.setColour(juce::Colours::black);
    
    // Init logo
    auto headerLogo = juce::ImageCache::getFromMemory(BinaryData::landon5504_png, BinaryData::landon5504_pngSize);
    g.drawImageWithin(headerLogo,
                      getWidth() * 0.02,
                      0,
                      getWidth() * 0.17,
                      getHeight(),
                      juce::RectanglePlacement::centred);
    
    // Init buttons with colors for color change update
    for (auto& button : buttons)
    {
        setTextButtonProps(*button);
    }
}

void Header::resized()
{
    // Position settings button
    float rightMargin = getWidth() * 0.95f;
    float headerTopMargin = getHeight() * 0.125f;
    float buttonWidth = getWidth() * 0.04;
    float buttonHeight = getHeight() * 0.75f;
    m_settingsButton.setBounds(rightMargin, headerTopMargin, buttonWidth, buttonHeight);

    // Position settings page
    setSettingsButtonProps();
}

void Header::setSettingsButtonProps()
{
    m_settingsButton.setComponentID("settings");
    m_settingsButton.onClick = [this]()
    {
        getParentComponent()->resized();
        getParentComponent()->repaint();
    };
}

bool Header::showSettings()
{
    return m_settingsButton.getToggleState();
}

void  Header::setTextButtonProps(juce::TextButton &button)
{
    addAndMakeVisible(button);
    button.setClickingTogglesState(true);
    
    button.setColour(juce::ComboBox::outlineColourId, m_textAccentColor);
    button.setColour(juce::TextButton::ColourIds::textColourOnId, m_textAccentColor);
    button.setColour(juce::TextButton::ColourIds::textColourOffId, m_textAccentColor);
    button.setColour(juce::TextButton::ColourIds::buttonColourId, m_mainCompColor);
    button.setColour(juce::TextButton::ColourIds::buttonOnColourId, m_mainCompColor);
    button.setLookAndFeel(&customButtonLAF);
}
