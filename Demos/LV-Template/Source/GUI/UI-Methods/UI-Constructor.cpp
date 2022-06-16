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
    
    /** Groups */
    for (auto& group : groups)
    {
        setGroupProps(*group);
    }
    
    m_mainBorder.setText("LV-Template");
    
    testDial1.setRange(0.0, 20.0, 0.01);
    testDial2.setRange(0.1, 1.0, 0.01);
    driveAttach = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.m_treeState, driveID, testDial1);
    threshAttach = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.m_treeState, ceilingID, testDial2);
}
