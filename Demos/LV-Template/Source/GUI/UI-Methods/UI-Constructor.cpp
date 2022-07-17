#include "../../PluginEditor.h"

void LVTemplateAudioProcessorEditor::uiConstructor()
{
    // Init the plugin window size logic
    initWindow();
    
    // Settings Page and Plugin Theme init
    addAndMakeVisible(m_settingsPage);
    m_settingsPage.setAlwaysOnTop(true);
    setPluginTheme(static_cast<Theme>(m_settingsPage.getPluginTheme()));
    
    // Init settings button
    setSettingsButtonProps();
}

void  LVTemplateAudioProcessorEditor::setSettingsButtonProps()
{
    m_settingsButton.setComponentID("settings");
    m_settingsButton.onClick = [this]()
    {
        resized();
        repaint();
        
        m_settingsPage.setEnabled(m_settingsButton.getToggleState());
        m_settingsPage.setVisible(m_settingsButton.getToggleState());
    };
}

void  LVTemplateAudioProcessorEditor::setTextButtonProps(juce::TextButton &button)
{
    addAndMakeVisible(button);
    button.setClickingTogglesState(true);
    
    if (button.getComponentID() == "settings")
    {
        button.setColour(juce::ComboBox::outlineColourId, m_textAccentColor);
        button.setColour(juce::TextButton::ColourIds::textColourOnId, m_textAccentColor);
        button.setColour(juce::TextButton::ColourIds::textColourOffId, m_textAccentColor);
        button.setColour(juce::TextButton::ColourIds::buttonColourId, m_mainCompColor);
        button.setColour(juce::TextButton::ColourIds::buttonOnColourId, m_mainCompColor);
        button.setLookAndFeel(&customButtonLAF);
    }
    
    else
    {
        button.setColour(juce::ComboBox::outlineColourId, juce::Colours::transparentBlack);
        button.setColour(juce::TextButton::ColourIds::textColourOnId, juce::Colours::whitesmoke);
        button.setColour(juce::TextButton::ColourIds::textColourOffId, juce::Colours::whitesmoke.withAlpha(0.5f));
        button.setColour(juce::TextButton::ColourIds::buttonColourId, juce::Colour::fromRGB(53, 55, 70));
        button.setColour(juce::TextButton::ColourIds::buttonOnColourId, juce::Colour::fromRGB(53, 55, 70).brighter(0.1));
    }
}
