#include "../../PluginEditor.h"

void LVTemplateAudioProcessorEditor::uiResized()
{
    //panel.setBounds(-25.0, -25.0, getWidth() + 50.0, getHeight() * 0.06 + 25.0);
    
    /** Header */
    const auto headerBottomMargin = getHeight() * 0.06f;
    
    m_headerRectangle.setBounds(0, 0, getWidth(), headerBottomMargin);
    
    float rightMargin = getWidth() * 0.95f;
    float headerTopMargin = m_headerRectangle.getHeight() * 0.125f;
    float buttonWidth = getWidth() * 0.05f;
    float buttonHeight = m_headerRectangle.getHeight() * 0.75f;
    
    m_settingsButton.setBounds(rightMargin - buttonWidth, headerTopMargin, buttonWidth, buttonHeight);
    
    /** Settings Page */
    setSettingsButtonProps();
    
    const auto settingsPageX = getWidth() * 0.6f;
    const auto settingsPageWidth = getWidth() * 0.4f;
    
    m_themeMenu.setEnabled(m_settingsButton.getToggleState());
    m_themeMenu.setVisible(m_settingsButton.getToggleState());
    m_settingsPage.setBounds(settingsPageX, headerBottomMargin, settingsPageWidth, getHeight());
    m_themeMenu.setBounds(m_settingsPage.withSizeKeepingCentre(m_settingsPage.getWidth() * 0.5, m_settingsPage.getHeight() * 0.05).withY(m_settingsPage.getY() + 24).toNearestInt());
    m_settingsButton.getToggleState() ? m_settingsPage.setX(settingsPageX) : m_settingsPage.setX(getWidth());
    
    // Save plugin size in the tree
    saveWindowSize();
}

