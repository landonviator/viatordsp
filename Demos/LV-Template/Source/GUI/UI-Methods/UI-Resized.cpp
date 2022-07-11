#include "../../PluginEditor.h"

void LVTemplateAudioProcessorEditor::uiResized()
{
    /** Header */
    const auto headerBottomMargin = getHeight() * 0.08;
    m_headerRectangle.setBounds(0, 0, getWidth(), headerBottomMargin);
    
    float rightMargin = getWidth() * 0.95f;
    float headerTopMargin = m_headerRectangle.getHeight() * 0.125f;
    float buttonWidth = getWidth() * 0.05f;
    float buttonHeight = m_headerRectangle.getHeight() * 0.75f;
    m_settingsButton.setBounds(rightMargin - buttonWidth * 1.07, headerTopMargin, buttonWidth, buttonHeight);
    
    /** Settings Page */
    setSettingsButtonProps();
    
    /** Panels */
    setPanelLayout();
    setDistortionGroupLayout();
    
    /** Settings Page */
    m_settingsPage.setVisible(m_settingsButton.getToggleState());
    m_settingsPage.setEnabled(m_settingsButton.getToggleState());
    
    if (m_settingsButton.getToggleState())
    {
        m_settingsPage.setBounds(getWidth() * 0.6f, getHeight() * 0.08f, getWidth() * 0.4f, getHeight());
    }
    
    /** Save Plugin Window Size */
    saveWindowSize();
}

