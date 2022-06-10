/*
  ==============================================================================

    Display.cpp
    Created: 9 Jun 2022 7:07:30pm
    Author:  Landon Viator

  ==============================================================================
*/

#include "../../PluginEditor.h"

void ParaEQDemoAudioProcessorEditor::initWindowSize()
{
    // Grab the window instance and create a rectangle
    juce::Rectangle<int> r = juce::Desktop::getInstance().getDisplays().getPrimaryDisplay()->userArea;
    
    // Using the width is more useful than the height, because we know the height will always be < than width
    int x = r.getWidth();
    
    auto width = 0;
    
    if (r.getWidth() <= 1920)
    {
        //small screen size
        width = x * 0.85;
    }
    
    else
    {
        //large screen size
        width = x * 0.5;
    }
    
    auto height = width * 0.5;
    
    //Making the window resizable by aspect ratio and setting size
    AudioProcessorEditor::setResizable(true, true);
    AudioProcessorEditor::setResizeLimits(width * 0.75, height * 0.75, width * 1.25, height * 1.25);
    AudioProcessorEditor::getConstrainer()->setFixedAspectRatio(2.0);
    
    setSize (width, height);
}
