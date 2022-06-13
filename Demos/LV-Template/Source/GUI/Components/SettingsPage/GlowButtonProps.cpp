/*
  ==============================================================================

    GlowButtonProps.cpp
    Created: 11 Jun 2022 2:42:04pm
    Author:  Landon Viator

  ==============================================================================
*/

#include "SettingsPage.h"

void SettingsPage::setGlowButtonProps()
{
    m_glowToggle.setButtonText("Glow");
    m_glowToggle.onClick = [this]()
    {
        getParentComponent()->repaint();
    };
}
