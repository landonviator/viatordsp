#include "../../PluginEditor.h"

void LVTemplateAudioProcessorEditor::uiPaint(juce::Graphics &g)
{
    // Init Plugin Theme First
    setPluginTheme(static_cast<Theme>(_settingsPage.getPluginTheme()));
    
    // Init Background with or without Gradient
    if (_settingsPage.getGradientState())
    {
        g.setGradientFill(juce::ColourGradient::vertical(m_bgColor.darker(0.75f), getHeight(), m_bgColor.brighter(0.02f), getHeight() * 0.4));
        g.fillRect(getLocalBounds());
    }
    
    else
    {
        g.fillAll(m_bgColor);
    }
    
    _settingsPage.repaint();
    
    // Update IO Colors
    _ioComp.repaint();
    
    // Title/version
    g.setColour(m_mainCompColor.withAlpha(0.8f));
    g.setFont(juce::Font("Helvetica", getWidth() * 0.02, juce::Font::FontStyleFlags::plain));
    g.drawText("Plugin v0.0.1", getLocalBounds().removeFromBottom(50), juce::Justification::centred);
}
