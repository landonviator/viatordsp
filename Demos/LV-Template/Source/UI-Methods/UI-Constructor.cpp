#include "../PluginEditor.h"

void LVTemplateAudioProcessorEditor::uiConstructor()
{
    // Window
    initWindow();
    setName("Editor");
    
    startTimerHz(30);
    
    addAndMakeVisible(largeDial);
    
    tooltipWindow.getLookAndFeel().setColour(juce::TooltipWindow::ColourIds::backgroundColourId, juce::Colour::fromRGB(54, 57, 63));
    tooltipWindow.getLookAndFeel().setColour(juce::TooltipWindow::ColourIds::outlineColourId, juce::Colour::fromRGB(0, 0, 0));
    
    addAndMakeVisible(headerComponent);
    
    addAndMakeVisible(settingsPage);
    showToolTip(settingsPage.getShouldUseToolTips());
}
