#include "../../PluginEditor.h"

void LVTemplateAudioProcessorEditor::uiPaint(juce::Graphics &g)
{
    // Background
    g.fillAll(m_bgColor);
    
    // Header
    g.setColour(m_bgLighterColor);
    g.fillRect(0, 0, getWidth(), getHeight() * 0.06);
    
    // Header bottom line segment
    g.setColour(juce::Colours::black.withAlpha(0.05f));
    g.drawLine(0, getHeight() * 0.06, getWidth(), getHeight() * 0.06, 2.0);
    
    g.setColour(m_textAccentColor);
    g.setFont(juce::Font ("Helvetica", getHeight() * 0.02f, juce::Font::FontStyleFlags::bold));
    g.drawText("Hello", getWidth() * 0.03, getHeight() * 0.03, 120, getHeight() * 0.03, juce::Justification::centred);
    //glow.setGlowProperties(3.0, juce::Colours::black);
    //panel.setComponentEffect(&glow);
    
    // Settings page
    g.setColour(m_bgTransparent);
    g.fillRect(m_settingsPage);
}
