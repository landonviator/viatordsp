#include "../../PluginEditor.h"

void LVTemplateAudioProcessorEditor::uiPaint(juce::Graphics &g)
{
    // Background
    if (m_gradientToggle.getToggleState())
    {
        g.setGradientFill(juce::ColourGradient::vertical(m_bgColor, getHeight(), m_bgColor.darker(0.25), getHeight() * 0.3));
        g.fillRect(getLocalBounds());
    }
    
    else
    {
        g.fillAll(m_bgColor);
    }
    
    
    // Header
    g.setColour(m_bgLighterColor);
    g.fillRect(0, 0, getWidth(), getHeight() * 0.06);
    
    // Header bottom line segment
    g.setColour(juce::Colours::black.withAlpha(0.05f));
    g.drawLine(0, getHeight() * 0.06, getWidth(), getHeight() * 0.06, 2.0);
    
    // Test text
    g.setColour(m_textAccentColor);
    g.setFont(juce::Font ("Helvetica", getHeight() * 0.02f, juce::Font::FontStyleFlags::bold));
    g.drawText("Hello", getWidth() * 0.03, getHeight() * 0.03, 120, getHeight() * 0.03, juce::Justification::centred);
    
    // Settings page
    g.setColour(juce::Colours::black.brighter(0.1));
    g.fillRect(m_settingsPage);
    
    // Update component colors
    setTextButtonProps(m_settingsButton);
    setSliderProps(testDial);
}
