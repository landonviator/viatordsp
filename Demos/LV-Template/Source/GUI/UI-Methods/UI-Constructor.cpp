#include "../../PluginEditor.h"

void LVTemplateAudioProcessorEditor::uiConstructor()
{
    // Window
    initWindow();
    
    setPluginTheme(m_pluginTheme);
    
    /** Buttons */
    for (auto& button : buttons)
    {
        setTextButtonProps(*button);
    }
    
    setSliderProps(testDial);
    setMenuProps(m_themeMenu);
    setGroupProps(m_themeGroup);
    setThemeMenuProps();
    
    addAndMakeVisible(panel);
    panel.setLookAndFeel(&customPanelLAF);
    panel.setComponentEffect(&glow);
}
