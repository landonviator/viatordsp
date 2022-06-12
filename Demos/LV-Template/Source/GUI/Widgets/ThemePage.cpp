/*
  ==============================================================================

    ThemePage.cpp
    Created: 11 Jun 2022 11:35:00pm
    Author:  Landon Viator

  ==============================================================================
*/

#include "../../PluginEditor.h"

void LVTemplateAudioProcessorEditor::setThemePageResized()
{
    setSettingsButtonProps();
    
    const auto settingsPageX = getWidth() * 0.6f;
    const auto settingsPageWidth = getWidth() * 0.4f;
    const auto headerBottomMargin = getHeight() * 0.06f;
    const auto contentX = getWidth() * 0.63;
    const auto contentWidth = getWidth() * 0.34;
    const auto contentY = getHeight() * 0.06;
    const auto contentHeight = contentY * 3.0;
    
    m_themeGroup.setEnabled(m_settingsButton.getToggleState());
    m_themeGroup.setVisible(m_settingsButton.getToggleState());
    m_themeGroup.setBounds(contentX, contentY, contentWidth, contentHeight);
    
    m_themeMenu.setEnabled(m_settingsButton.getToggleState());
    m_themeMenu.setVisible(m_settingsButton.getToggleState());
    
    m_glowToggle.setEnabled(m_settingsButton.getToggleState());
    m_glowToggle.setVisible(m_settingsButton.getToggleState());
    
    m_gradientToggle.setEnabled(m_settingsButton.getToggleState());
    m_gradientToggle.setVisible(m_settingsButton.getToggleState());
    
    m_discord.setEnabled(m_settingsButton.getToggleState());
    m_discord.setVisible(m_settingsButton.getToggleState());
    
    m_patreon.setEnabled(m_settingsButton.getToggleState());
    m_patreon.setVisible(m_settingsButton.getToggleState());
    
    m_twitch.setEnabled(m_settingsButton.getToggleState());
    m_twitch.setVisible(m_settingsButton.getToggleState());
    m_twitchLink.setEnabled(m_settingsButton.getToggleState());
    m_twitchLink.setVisible(m_settingsButton.getToggleState());
    
    m_settingsPage.setBounds(settingsPageX, headerBottomMargin, settingsPageWidth, getHeight());
    
    m_glowToggle.setBounds(contentX * 1.03, contentY * 1.6, m_settingsPage.getWidth() * 0.2, m_settingsPage.getHeight() * 0.05);
    const auto buttonX = m_glowToggle.getX();
    const auto buttonY = m_glowToggle.getY();
    const auto buttonWidth = m_glowToggle.getWidth();
    const auto buttonHeight = m_glowToggle.getHeight();
    
    m_themeMenu.setBounds(m_glowToggle.getX() + m_glowToggle.getWidth() * 1.55, m_glowToggle.getY(), m_glowToggle.getWidth() * 2.0, m_glowToggle.getHeight());
    
    m_settingsButton.getToggleState() ? m_settingsPage.setX(settingsPageX) : m_settingsPage.setX(getWidth());
    m_gradientToggle.setBounds(buttonX, buttonY + buttonHeight * 1.5, buttonWidth, buttonHeight);
    
    m_discord.setBounds(buttonX, buttonY * 9.5, buttonWidth, buttonHeight);
    m_patreon.setBounds(m_discord.getX() + m_discord.getWidth() * 1.5, m_discord.getY(), buttonWidth, buttonHeight);
    
    // Twitch
    m_twitch.setBounds(m_patreon.getX() + m_patreon.getWidth() * 1.5, m_discord.getY(), buttonWidth, buttonHeight);
}
