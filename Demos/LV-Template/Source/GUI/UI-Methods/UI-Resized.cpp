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
    setThemePageResized();
    
    /** Test Widgets */
    testDial.setBounds(200, 200, 200, 200);
    
    // Save plugin size in the tree
    saveWindowSize();
}

