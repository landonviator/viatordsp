/*
  ==============================================================================

    DiscordBtn.cpp
    Created: 12 Jun 2022 2:30:29pm
    Author:  Landon Viator

  ==============================================================================
*/

#include "SettingsPage.h"

void SettingsPage::setDiscordBtnProps()
{
    m_discord.setButtonText("Discord");
    m_discord.setClickingTogglesState(false);
    
    // Discord link
    m_discordLink.setURL(m_discordUrl);
    addAndMakeVisible(m_discordLink);
    
    m_discord.onClick = [this]()
    {
        m_discordLink.triggerClick();
    };
}
