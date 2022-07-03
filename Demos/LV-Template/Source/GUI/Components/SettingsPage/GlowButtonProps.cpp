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
    m_glowToggle.setToggleState(audioProcessor.variableTree.getProperty("glowtoggle"), juce::dontSendNotification);
    m_glowToggle.onClick = [this]()
    {
        audioProcessor.variableTree.setProperty("glowtoggle",
                                                m_glowToggle.getToggleState(), nullptr);
        getParentComponent()->repaint();
    };
}
