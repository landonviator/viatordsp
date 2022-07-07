/*
  ==============================================================================

    GradientToggle.cpp
    Created: 12 Jun 2022 1:59:30pm
    Author:  Landon Viator

  ==============================================================================
*/

#include "SettingsPage.h"

void SettingsPage::setGradientToggleProps()
{
    m_gradientToggle.setButtonText("Gradient");
    m_gradientToggle.setToggleState(audioProcessor.variableTree.getProperty("gradienttoggle"), juce::dontSendNotification);
    m_gradientToggle.onClick = [this]()
    {
        audioProcessor.variableTree.setProperty("gradienttoggle",
                                                m_gradientToggle.getToggleState(), nullptr);
        getParentComponent()->repaint();
    };
}
