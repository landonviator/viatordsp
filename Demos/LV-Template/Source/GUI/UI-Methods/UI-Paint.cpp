#include "../../PluginEditor.h"

void LVTemplateAudioProcessorEditor::uiPaint(juce::Graphics &g)
{
    /** Set Plugin Theme First*/
    setPluginTheme(static_cast<Theme>(m_settingsPage.getPluginTheme()));
    
    /** Set Background with or without Gradient*/
    if (m_settingsPage.getGradientState())
    {
        g.setGradientFill(juce::ColourGradient::vertical(m_bgColor, getHeight(), m_bgColor.darker(0.25), getHeight() * 0.3));
        g.fillRect(getLocalBounds());
    }
    
    else
    {
        g.fillAll(m_bgColor);
    }
    
    /** Set Header */
    g.setColour(m_bgLighterColor);
    g.fillRect(0, 0, getWidth(), getHeight() * 0.06);
    g.setColour(juce::Colours::black.withAlpha(0.05f));
    g.drawLine(0, getHeight() * 0.06, getWidth(), getHeight() * 0.06, 2.0);
    
    /** Update Component Colors*/
    for (auto& button : buttons)
    {
        setTextButtonProps(*button);
    }
    
    for (auto& slider : sliders)
    {
        setSliderProps(*slider);
    }
}
