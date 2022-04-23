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
    topHeaderMargin = getHeight() * 0.015;
    
    auto buttonWidth = getWidth() * 0.05;
    auto buttonHeight = buttonWidth * 0.66;
    auto menuWidth = getWidth() * 0.1;
    auto menuHeight = buttonHeight;
    auto fontSize = getWidth() * 0.015;
    
//    msMenu.setBounds(getWidth() * 0.74, topHeaderMargin, menuWidth, menuHeight);
//
//    cpuButton.setBounds(getWidth() * 0.88, topHeaderMargin, buttonWidth, buttonHeight);
//
//    cpuLabel.setBounds(cpuButton.getX() + cpuButton.getWidth() * 1.125, cpuButton.getY(), buttonWidth, buttonHeight);
//    cpuLabel.setFont(fontSize);
    
    dial.setBounds(getLocalBounds().withSizeKeepingCentre(getWidth() * 0.15, getWidth() * 0.2));
}
