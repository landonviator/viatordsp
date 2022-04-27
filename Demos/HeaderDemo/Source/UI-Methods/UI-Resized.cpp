/*
  ==============================================================================

    UI-Resized.cpp
    Created: 24 Oct 2021 1:41:10am
    Author:  Landon Viator

  ==============================================================================
*/

#include "../PluginEditor.h"

void HeaderDemoAudioProcessorEditor::uiResized()
{
    cpuLabel.setBounds(getWidth() * 0.9, getHeight() * 0.02, getWidth() * 0.5, getHeight() * 0.025);
}
