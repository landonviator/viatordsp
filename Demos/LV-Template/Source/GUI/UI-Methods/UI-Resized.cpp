#include "../../PluginEditor.h"

void LVTemplateAudioProcessorEditor::uiResized()
{
    // Position header
    const auto headerBottomMargin = getHeight() * 0.08;
    _headerComp.setBounds(0, 0, getWidth(), headerBottomMargin);
    
    // Only show settings page on resize if the toggle is on
    _settingsPage.setVisible(_headerComp.showSettings());
    _settingsPage.setEnabled(_headerComp.showSettings());
    
    if (_headerComp.showSettings())
    {
        _settingsPage.setBounds(getWidth() * 0.7f, getHeight() * 0.08f, getWidth() * 0.3f, getHeight());
    }
    
    // Save Plugin Window Size
    saveWindowSize();
}

