/*
  ==============================================================================

    UI-Resized.cpp
    Created: 24 Oct 2021 1:41:10am
    Author:  Landon Viator

  ==============================================================================
*/

#include "../PluginEditor.h"

void LVTemplateAudioProcessorEditor::uiResized()
{
    topMargin = getHeight() * 0.05;
    
    //Header
    headerComponent.setBounds(0, 0, getWidth(), topMargin);
    
    //Settings Page
    setSettingsPageBounds();
    
    // Save plugin size in the tree
    saveWindowSize();
}

void LVTemplateAudioProcessorEditor::setSettingsPageBounds()
{
    auto settingsWidth = getWidth() * 0.5;
    auto settingsHeight = getHeight() * 0.95;
    
    auto settingsPageBounds = juce::Rectangle<float>(settingsWidth, topMargin, settingsWidth, settingsHeight).toNearestInt();
    auto settingsPageOutBounds = juce::Rectangle<float>(getWidth(), topMargin, settingsWidth, settingsHeight).toNearestInt();
    
    headerComponent.getSettingsButtonToggleState() ? settingsPage.setBounds(settingsPageBounds) : settingsPage.setBounds(settingsPageOutBounds);
    
//    if (headerComponent.getSettingsButtonToggleState())
//    {
//        settingsPageAnimator.animateComponent(&settingsPage, settingsPageBounds, 1.0f, 250, false, 1.0, 1.0);
//    }
//
//    else
//    {
//        settingsPageAnimator.animateComponent(&settingsPage, settingsPageOutBounds, 1.0f, 250, false, 1.0, 1.0);
//    }
    
}
