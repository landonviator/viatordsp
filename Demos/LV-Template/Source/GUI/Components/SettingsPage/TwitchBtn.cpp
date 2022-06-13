/*
  ==============================================================================

    TwitchBtn.cpp
    Created: 12 Jun 2022 2:30:51pm
    Author:  Landon Viator

  ==============================================================================
*/

#include "SettingsPage.h"

void SettingsPage::setTwitchBtnProps()
{
    m_twitch.setButtonText("Twitch");
    m_twitch.setClickingTogglesState(false);
    
    // Twitch link
    m_twitchLink.setURL(m_twitchUrl);
    addAndMakeVisible(m_twitchLink);
    
    m_twitch.onClick = [this]()
    {
        m_twitchLink.triggerClick();
    };
}
