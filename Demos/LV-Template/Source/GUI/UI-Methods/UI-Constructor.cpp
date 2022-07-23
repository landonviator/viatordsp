#include "../../PluginEditor.h"

void LVTemplateAudioProcessorEditor::uiConstructor()
{
    // Init the plugin window size logic
    initWindow();
    
    // Settings Page and Plugin Theme init
    addAndMakeVisible(_settingsPage);
    _settingsPage.setAlwaysOnTop(true);
    setPluginTheme(static_cast<Theme>(_settingsPage.getPluginTheme()));
    
    // Header
    addAndMakeVisible(_headerComp);
    
    // IO Module
    addAndMakeVisible(_ioComp);
}

