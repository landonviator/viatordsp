/*
  ==============================================================================

    SettingsButton.cpp
    Created: 10 Jun 2022 8:08:54pm
    Author:  Landon Viator

  ==============================================================================
*/

#include "../../../PluginEditor.h"

void LVTemplateAudioProcessorEditor::setSettingsButtonProps()
{
    m_settingsButton.setButtonText("Settings");
    m_settingsButton.changeWidthToFitText();
    m_settingsButton.setComponentID("settings");
    m_settingsButton.onClick = [this]()
    {
        resized();
        repaint();
        
        m_settingsPage.setEnabled(m_settingsButton.getToggleState());
        m_settingsPage.setVisible(m_settingsButton.getToggleState());
    };
}
