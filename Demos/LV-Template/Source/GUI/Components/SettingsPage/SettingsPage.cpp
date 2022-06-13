/*
  ==============================================================================

    SettingsPage.cpp
    Created: 13 Jun 2022 3:11:30pm
    Author:  Landon Viator

  ==============================================================================
*/

#include <JuceHeader.h>
#include "SettingsPage.h"

//==============================================================================
SettingsPage::SettingsPage()
{
    setMenuProps(m_themeMenu);
    setThemeMenuProps();
    
    /** Buttons */
    for (auto& button : buttons)
    {
        setTextButtonProps(*button);
    }
    
    /** Groups */
    for (auto& group : groups)
    {
        setGroupProps(*group);
    }
}

SettingsPage::~SettingsPage()
{
}

void SettingsPage::paint (juce::Graphics& g)
{
    g.fillAll(juce::Colours::black.brighter(0.1));
}

void SettingsPage::resized()
{
    /** Glow Toggle */
    const auto contentX = getWidth() * 0.1;
    const auto contentY = getHeight() * 0.06;
    m_glowToggle.setBounds(contentX * 1.47, contentY * 1.6, getWidth() * 0.2, getHeight() * 0.05);
    
    /** Theme Menu and Gradient Toggle */
    const auto buttonX = m_glowToggle.getX();
    const auto buttonY = m_glowToggle.getY();
    const auto buttonWidth = m_glowToggle.getWidth();
    const auto buttonHeight = m_glowToggle.getHeight();
    m_themeMenu.setBounds(m_glowToggle.getX() + m_glowToggle.getWidth() * 1.55, m_glowToggle.getY(), m_glowToggle.getWidth() * 2.0, m_glowToggle.getHeight());
    m_gradientToggle.setBounds(buttonX, buttonY + buttonHeight * 1.5, buttonWidth, buttonHeight);
    
    /** Social Toggles */
    m_discord.setBounds(buttonX, buttonY * 9.0, buttonWidth, buttonHeight);
    m_patreon.setBounds(m_discord.getX() + m_discord.getWidth() * 1.5, m_discord.getY(), buttonWidth, buttonHeight);
    m_twitch.setBounds(m_patreon.getX() + m_patreon.getWidth() * 1.5, m_discord.getY(), buttonWidth, buttonHeight);
    m_themeGroup.setBounds(m_glowToggle.getX() * 0.57, m_glowToggle.getY() * 0.65, m_themeMenu.getX() + m_themeMenu.getWidth(), m_gradientToggle.getY() + m_gradientToggle.getHeight() * 0.38);
}

SettingsPage::Theme SettingsPage::getPluginTheme()
{
    return m_pluginTheme;
}

bool SettingsPage::getGlowState()
{
    return m_glowToggle.getToggleState();
}

bool SettingsPage::getGradientState()
{
    return m_gradientToggle.getToggleState();
}
