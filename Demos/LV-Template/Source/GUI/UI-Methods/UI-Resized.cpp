#include "../../PluginEditor.h"

void LVTemplateAudioProcessorEditor::uiResized()
{
    // Position header
    const auto headerBottomMargin = getHeight() * 0.08;
    m_headerRectangle.setBounds(0, 0, getWidth(), headerBottomMargin);
    
    // Position settings button
    float rightMargin = getWidth() * 0.95f;
    float headerTopMargin = m_headerRectangle.getHeight() * 0.125f;
    float buttonWidth = getWidth() * 0.04;
    float buttonHeight = m_headerRectangle.getHeight() * 0.75f;
    m_settingsButton.setBounds(rightMargin, headerTopMargin, buttonWidth, buttonHeight);
    
    // Position settings page
    setSettingsButtonProps();
    
    // Only show settings page on resize if the toggle is on
    m_settingsPage.setVisible(m_settingsButton.getToggleState());
    m_settingsPage.setEnabled(m_settingsButton.getToggleState());
    
    if (m_settingsButton.getToggleState())
    {
        m_settingsPage.setBounds(getWidth() * 0.7f, getHeight() * 0.08f, getWidth() * 0.3f, getHeight());
    }
    
    // Save Plugin Window Size
    saveWindowSize();
}

