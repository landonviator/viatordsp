/*
  ==============================================================================

    UI-InitWindow.cpp
    Created: 24 Oct 2021 1:46:10am
    Author:  Landon Viator

  ==============================================================================
*/

#include "../PluginEditor.h"

void HeaderDemoAudioProcessorEditor::initWindow()
{
    // Grab the window instance and create a rectangle
    juce::Rectangle<int> r = juce::Desktop::getInstance().getDisplays().getPrimaryDisplay()->userArea;
    
    // Using the width is more useful than the height, because we know the height will always be < than width
    int x = r.getWidth();
    
    auto width = 0;
    
    if (r.getWidth() <= 1440)
    {
        width = x * 0.65;
    }
    
    else
    {
        width = x * 0.5;
    }
    
    auto height = width * 0.5;
    
    //Making the window resizable by aspect ratio and setting size
    AudioProcessorEditor::setResizable(true, true);
    AudioProcessorEditor::setResizeLimits(width * 0.75, height * 0.75, width * 1.25, height * 1.25);
    AudioProcessorEditor::getConstrainer()->setFixedAspectRatio(2.0);
    
    setSize (width, height);
}
