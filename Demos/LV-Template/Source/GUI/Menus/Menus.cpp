/*
  ==============================================================================

    Menus.cpp
    Created: 10 Jul 2022 12:53:50pm
    Author:  Landon Viator

  ==============================================================================
*/

#include "../../PluginEditor.h"

void LVTemplateAudioProcessorEditor::setMenuProps(viator_gui::Menu &menu)
{
    addAndMakeVisible(menu);
    menu.setColour(juce::ComboBox::ColourIds::backgroundColourId, m_textAccentColor.withAlpha(0.4f));
    menu.setColour(juce::ComboBox::ColourIds::outlineColourId, juce::Colours::transparentBlack);
    menu.setColour(juce::ComboBox::ColourIds::focusedOutlineColourId, m_bgLighterColor);
    menu.setColour(juce::ComboBox::ColourIds::textColourId, m_textColor);
    menu.setColour(juce::ComboBox::ColourIds::arrowColourId, m_bgColor);

    menu.getLookAndFeel().setColour(juce::PopupMenu::backgroundColourId, m_textAccentColor.withAlpha(0.4f));
    menu.getLookAndFeel().setColour(juce::PopupMenu::highlightedBackgroundColourId, m_mainCompColor);
    menu.getLookAndFeel().setColour(juce::PopupMenu::textColourId, m_textColor);
    menu.getLookAndFeel().setColour(juce::PopupMenu::highlightedTextColourId, m_bgLighterColor);
}

void LVTemplateAudioProcessorEditor::setDistortionMenuProps()
{
    m_distortionMenu.addItem("Lofi", 1);
    m_distortionMenu.addItem("Hard", 2);
    m_distortionMenu.addItem("Soft", 3);
    m_distortionMenu.addItem("Diode", 4);
    m_distortionMenu.addItem("Fuzz", 5);
    m_distortionMenu.addItem("Tube", 6);
    m_distortionMenu.addItem("Saturation", 7);
    m_distortionMenu.setTextWhenNothingSelected("Distortion Type");
    driveMenuAttach = std::make_unique<juce::AudioProcessorValueTreeState::ComboBoxAttachment>(audioProcessor.m_treeState, driveMenuID, m_distortionMenu);
}
