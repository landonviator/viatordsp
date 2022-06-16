#include "../../PluginEditor.h"

void LVTemplateAudioProcessorEditor::uiPaint(juce::Graphics &g)
{
    /** Set Plugin Theme First*/
    setPluginTheme(static_cast<Theme>(m_settingsPage.getPluginTheme()));
    
    /** Set Background with or without Gradient*/
    if (m_settingsPage.getGradientState())
    {
        g.setGradientFill(juce::ColourGradient::vertical(m_bgColor.darker(0.75f), getHeight(), m_bgColor.brighter(0.02f), getHeight() * 0.4));
        g.fillRect(getLocalBounds());
    }
    
    else
    {
        g.fillAll(m_bgColor);
    }
    
    /** Set Header */
    g.setColour(juce::Colours::black.withAlpha(0.2f));
    g.fillRect(0, 0, getWidth(), getHeight() * 0.08);
    g.setColour(juce::Colours::black.withAlpha(0.1f));
    g.drawLine(0, getHeight() * 0.08, getWidth(), getHeight() * 0.08, 1.0);
    
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
