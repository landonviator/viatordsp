#include "../../PluginEditor.h"

void LVTemplateAudioProcessorEditor::uiResized()
{
    /** Header */
    const auto headerBottomMargin = getHeight() * 0.08;
    m_headerRectangle.setBounds(0, 0, getWidth(), headerBottomMargin);
    
    float rightMargin = getWidth() * 0.95f;
    float headerTopMargin = m_headerRectangle.getHeight() * 0.125f;
    float buttonWidth = getWidth() * 0.04;
    float buttonHeight = m_headerRectangle.getHeight() * 0.75f;
    m_settingsButton.setBounds(rightMargin, headerTopMargin, buttonWidth, buttonHeight);
    
    /** Settings Page */
    setSettingsButtonProps();
    
    /** Panels */
    setPanelLayout();
    setDistortionGroupLayout();
    setToneGroupLayout();
    setReverbGroupLayout();
    
    /** Settings Page */
    m_settingsPage.setVisible(m_settingsButton.getToggleState());
    m_settingsPage.setEnabled(m_settingsButton.getToggleState());
    
    if (m_settingsButton.getToggleState())
    {
        m_settingsPage.setBounds(getWidth() * 0.7f, getHeight() * 0.08f, getWidth() * 0.3f, getHeight());
    }
    
    /** Save Plugin Window Size */
    saveWindowSize();
}

