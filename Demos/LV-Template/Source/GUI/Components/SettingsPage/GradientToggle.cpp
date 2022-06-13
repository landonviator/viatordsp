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
    m_gradientToggle.onClick = [this]()
    {
        getParentComponent()->repaint();
    };
}
