/*
  ==============================================================================

    SliderProps.cpp
    Created: 11 Jun 2022 1:46:51pm
    Author:  Landon Viator

  ==============================================================================
*/

#include "../../PluginEditor.h"

void LVTemplateAudioProcessorEditor::setSliderProps(juce::Slider &slider)
{
    addAndMakeVisible(slider);
    slider.setSliderStyle(juce::Slider::SliderStyle::RotaryVerticalDrag);
    slider.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 128, 32);
    slider.setColour(juce::Slider::ColourIds::rotarySliderFillColourId, m_mainCompFillColor);
    slider.setColour(juce::Slider::ColourIds::rotarySliderOutlineColourId, m_bgLighterColor);
    slider.setColour(juce::Slider::ColourIds::trackColourId, m_textAccentColor);
    slider.setColour(juce::Slider::ColourIds::textBoxOutlineColourId, juce::Colours::black.withAlpha(0.0f));
    slider.setColour(juce::Slider::ColourIds::textBoxTextColourId, m_textAccentColor);
    slider.setColour(juce::Slider::ColourIds::thumbColourId, m_mainCompColor);
    slider.setColour(juce::Slider::ColourIds::backgroundColourId, m_bgTransparent);
    slider.setDoubleClickReturnValue(true, 0.0);
    slider.setLookAndFeel(&customDialLAF);
    
    shadowProperties.radius = 8;
    shadowProperties.offset = juce::Point<int> (0, 0);
    
    if (m_settingsPage.getGlowState())
    {
        shadowProperties.colour = m_mainCompColor.withAlpha(m_settingsPage.getCurrentGlowValue());
    }
    
    else
    {
        shadowProperties.colour = juce::Colours::black;
    }
    
    dialShadow.setShadowProperties (shadowProperties);
    
    slider.setComponentEffect(&dialShadow);
}

void LVTemplateAudioProcessorEditor::setDisSliderProps()
{
    m_driveDial.setTextValueSuffix(" Drive");
    m_driveDial.setRange(0.0, 20.0, 0.01);
    driveAttach = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.m_treeState, driveID, m_driveDial);
    
    m_mixDial.setTextValueSuffix(" Mix");
    m_mixDial.setRange(0.0, 1.0, 0.01);
    driveMixAttach = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.m_treeState, mixID, m_mixDial);
}

void LVTemplateAudioProcessorEditor::setToneSliderProps()
{
    m_tiltSlider.setTextValueSuffix(" Tilt");
    m_tiltSlider.setRange(-15.0, 15.0, 0.01);
    tiltAttach = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.m_treeState, tiltGainID, m_tiltSlider);
    
    m_toneDial.setTextValueSuffix(" Tone");
    m_toneDial.setRange(-15.0, 15.0, 0.01);
    toneAttach = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.m_treeState, midGainID, m_toneDial);
    
    m_cutoffDial.setTextValueSuffix(" Freq");
    m_cutoffDial.setRange(200.0, 5000.0, 0.01);
    cutoffAttach = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.m_treeState, midCutoffID, m_cutoffDial);
}

void LVTemplateAudioProcessorEditor::setVerbDialProps()
{
    m_sizeDial.setTextValueSuffix(" Size");
    m_sizeDial.setRange(0.0, 1.0, 0.01);
    roomAttach = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.m_treeState, roomSizeID, m_sizeDial);

    m_widthDial.setTextValueSuffix(" Width");
    m_widthDial.setRange(0.0, 1.0, 0.01);
    widthAttach = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.m_treeState, widthID, m_widthDial);

    m_dampDial.setTextValueSuffix(" Damp");
    m_dampDial.setRange(0.0, 1.0, 0.01);
    dampAttach = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.m_treeState, dampingID, m_dampDial);

    m_blendDial.setTextValueSuffix(" Blend");
    m_blendDial.setRange(0.0, 1.0, 0.01);
    verbBlendAttach = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.m_treeState, reverbMixID, m_blendDial);

}
