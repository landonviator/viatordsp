#include "../../PluginEditor.h"

void LVTemplateAudioProcessorEditor::uiResized()
{
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
    
    /** Test Widgets */
    const auto leftMargin = getWidth() * 0.1;
    const auto topMargin = getHeight() * 0.4;
    const auto dialSize = getWidth() * 0.2;
    testDial1.setBounds(leftMargin, topMargin, dialSize, dialSize);
    testDial2.setBounds(testDial1.getX() + testDial1.getWidth(), topMargin, dialSize, dialSize);
    testDial3.setBounds(testDial2.getX() + testDial2.getWidth(), topMargin, dialSize, dialSize);
    testDial4.setBounds(testDial3.getX() + testDial3.getWidth(), topMargin, dialSize, dialSize);
    
    /** Settings Page */
    m_settingsPage.setBounds(getWidth() * 0.6f, getHeight() * 0.06f, getWidth() * 0.4f, getHeight());
    m_settingsPage.setEnabled(m_settingsButton.getToggleState());
    m_settingsPage.setVisible(m_settingsButton.getToggleState());
    
    /** Save Plugin Window Size */
    saveWindowSize();
}

