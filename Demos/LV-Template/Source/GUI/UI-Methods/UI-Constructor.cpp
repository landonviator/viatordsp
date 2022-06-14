#include "../../PluginEditor.h"

void LVTemplateAudioProcessorEditor::uiConstructor()
{
    /** Plugin Window */
    initWindow();
    
    /** Settings Page and Plugin Theme*/
    addAndMakeVisible(m_settingsPage);
    m_settingsPage.setAlwaysOnTop(true);
    setPluginTheme(static_cast<Theme>(m_settingsPage.getPluginTheme()));
    
    /** Buttons */
    for (auto& button : buttons)
    {
        setTextButtonProps(*button);
    }
    
    /** Sliders */
    for (auto& slider : sliders)
    {
        setSliderProps(*slider);
    }
    
    driveAttach = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.m_treeState, driveID, testDial1);
}
