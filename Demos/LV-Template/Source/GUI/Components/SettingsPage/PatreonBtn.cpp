/*
  ==============================================================================

    PatreonBtn.cpp
    Created: 12 Jun 2022 2:30:37pm
    Author:  Landon Viator

  ==============================================================================
*/

#include "SettingsPage.h"

void SettingsPage::setPatreonBtnProps()
{
    m_patreon.setButtonText("Patreon");
    m_patreon.setClickingTogglesState(false);
    
    // Patreon link
    m_patreonLink.setURL(m_patreonUrl);
    addAndMakeVisible(m_patreonLink);
    
    m_patreon.onClick = [this]()
    {
        m_patreonLink.triggerClick();
    };
}
