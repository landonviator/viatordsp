#include "../../PluginEditor.h"

void LVTemplateAudioProcessorEditor::uiPaint(juce::Graphics &g)
{
    // Init Plugin Theme First
    setPluginTheme(static_cast<Theme>(m_settingsPage.getPluginTheme()));
    
    // Init Background with or without Gradient
    if (m_settingsPage.getGradientState())
    {
        g.setGradientFill(juce::ColourGradient::vertical(m_bgColor.darker(0.75f), getHeight(), m_bgColor.brighter(0.02f), getHeight() * 0.4));
        g.fillRect(getLocalBounds());
    }
    
    else
    {
        g.fillAll(m_bgColor);
    }
    
    // Init Header
    g.setColour(juce::Colours::black.withAlpha(0.2f));
    g.fillRect(0, 0, getWidth(), getHeight() * 0.08);
    g.setColour(juce::Colours::black.withAlpha(0.1f));
    g.drawLine(0, getHeight() * 0.08, getWidth(), getHeight() * 0.08, 1.0);
    g.setColour(juce::Colours::black);
    
    // Init logo
    auto headerLogo = juce::ImageCache::getFromMemory(BinaryData::landon5504_png, BinaryData::landon5504_pngSize);
    g.drawImageWithin(headerLogo,
                      getWidth() * 0.02,
                      0,
                      getWidth() * 0.17,
                      getHeight() * 0.08,
                      juce::RectanglePlacement::centred);
    
    // Init buttons with colors for color change update
    for (auto& button : buttons)
    {
        setTextButtonProps(*button);
    }
}
