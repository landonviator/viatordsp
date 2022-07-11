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
    
    driveToggleAttach = std::make_unique<juce::AudioProcessorValueTreeState::ButtonAttachment>(audioProcessor.m_treeState, driveEnableID, m_distortionToggle);
    toneToggleAttach = std::make_unique<juce::AudioProcessorValueTreeState::ButtonAttachment>(audioProcessor.m_treeState, toneEnableID, m_toneToggle);
    
    /** Sliders */
    for (auto& slider : disSliders)
    {
        setSliderProps(*slider);
    }
    
    for (auto& slider : toneSliders)
    {
        setSliderProps(*slider);
    }
    
    setDisSliderProps();
    setToneSliderProps();
    
    /** Groups */
    for (auto& group : groups)
    {
        setGroupProps(*group);
    }
    
    /** Module Toggles */
    for (auto& toggle : toggles)
    {
        setModuleToggleProps(*toggle);
    }
    
    setPrePostProps();
    
    /** Module Labels */
    for (auto& label : moduleLabels)
    {
        setModuleLabelProps(*label);
    }
    
    /** Module Menus */
    for (auto& menu : menus)
    {
        setMenuProps(*menu);
    }
    
    setDistortionMenuProps();
    
    m_mainBorder.setText("LV-Template");
}
