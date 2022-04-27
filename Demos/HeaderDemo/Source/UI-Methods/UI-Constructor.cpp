/*
  ==============================================================================

    UI-Constructor.cpp
    Created: 24 Oct 2021 1:40:44am
    Author:  Landon Viator

  ==============================================================================
*/

#include "../PluginEditor.h"

void HeaderDemoAudioProcessorEditor::uiConstructor()
{
    initWindow();
    
    startTimerHz(10);
    
    addAndMakeVisible(cpuLabel);
    cpuLabel.setText("CPU", juce::dontSendNotification);
}
