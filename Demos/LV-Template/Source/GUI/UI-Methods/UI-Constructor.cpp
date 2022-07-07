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
    
    driveDial.setRange(0.0, 20.0, 0.01);
    mixDial.setRange(0.0, 100.0, 0.01);
    driveAttach = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.m_treeState, driveID, driveDial);
    driveMixAttach = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.m_treeState, mixID, mixDial);
    
}
