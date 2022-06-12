/*
  ==============================================================================

    GradientToggle.cpp
    Created: 12 Jun 2022 1:59:30pm
    Author:  Landon Viator

  ==============================================================================
*/

#include "../../../PluginEditor.h"

void LVTemplateAudioProcessorEditor::setGradientToggleProps()
{
    m_gradientToggle.setButtonText("Gradient");
    m_gradientToggle.onClick = [this]()
    {
        repaint();
    };
}
