#include "../../PluginEditor.h"

void LVTemplateAudioProcessorEditor::uiConstructor()
{
    // Window
    initWindow();
    
    setPluginTheme(m_pluginTheme);
    
    setTextButtonProps(m_settingsButton);
    setMenuProps(m_themeMenu);
    setThemeMenuProps();
    
    addAndMakeVisible(panel);
    panel.setLookAndFeel(&customPanelLAF);
    panel.setComponentEffect(&glow);
}
