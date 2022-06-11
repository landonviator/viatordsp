#include "../../PluginEditor.h"

void LVTemplateAudioProcessorEditor::uiConstructor()
{
    // Window
    initWindow();
    
    setTextButtonProps(m_settingsButton);
    
    addAndMakeVisible(panel);
    panel.setLookAndFeel(&customPanelLAF);
    panel.setComponentEffect(&glow);
}
