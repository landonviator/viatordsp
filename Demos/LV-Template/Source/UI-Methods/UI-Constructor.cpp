/*
  ==============================================================================

    UI-Constructor.cpp
    Created: 24 Oct 2021 1:40:44am
    Author:  Landon Viator

  ==============================================================================
*/

#include "../PluginEditor.h"

void LVTemplateAudioProcessorEditor::uiConstructor()
{
    // Window
    initWindow();
    
    startTimerHz(30);
    
//    if (settingsPage.getShouldUseToolTips())
//    {
//        addAndMakeVisible(tooltipWindow);
//        tooltipWindow.setEnabled(settingsPage.getShouldUseToolTips());
//    }
    
    tooltipWindow.getLookAndFeel().setColour(juce::TooltipWindow::ColourIds::backgroundColourId, juce::Colour::fromRGB(54, 57, 63));
    tooltipWindow.getLookAndFeel().setColour(juce::TooltipWindow::ColourIds::outlineColourId, juce::Colour::fromRGB(0, 0, 0));
    
    addAndMakeVisible(headerComponent);
    
    addAndMakeVisible(settingsPage);
    showToolTip(settingsPage.getShouldUseToolTips());
}
