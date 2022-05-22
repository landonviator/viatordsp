/*
  ==============================================================================

    UI-SaveWindow.cpp
    Created: 24 Oct 2021 1:46:19am
    Author:  Landon Viator

  ==============================================================================
*/

#include "../PluginEditor.h"

void LVTemplateAudioProcessorEditor::saveWindowSize()
{
    // Save plugin size in value tree
    audioProcessor.variableTree.setProperty("width", getWidth(), nullptr);
    audioProcessor.variableTree.setProperty("height", getHeight(), nullptr);
    
    // Don't know why I needed to do this
    if (constructorFinished)
    {
        audioProcessor.windowWidth = getWidth();
        audioProcessor.windowHeight = getHeight();
    }
}
