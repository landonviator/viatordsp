/*
  ==============================================================================

    IOModule.cpp
    Created: 19 Jul 2022 3:52:10pm
    Author:  Landon Viator

  ==============================================================================
*/

#include <JuceHeader.h>
#include "IOModule.h"

//==============================================================================
IOModule::IOModule(LVTemplateAudioProcessor& p, SettingsPage& s) : audioProcessor(p), _settingsPage(s)
, _inputDial(0, " dB", -24.0, 24.0, false)
, _outputDial(0, " dB", -24.0, 24.0, false)
, _skeuPhaseToggle(false, "HQ", true)
, _skeuHQToggle (true, "HQ", false)
{
    // Skeu Input
    addAndMakeVisible(_inputDial);
    _inputDial.setDoubleClickReturnValue(true, 0.0);
    _inputAttach = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor._treeState, inputID, _inputDial);
    
    // Skeu Input Label
    addAndMakeVisible(_inputLabel);
    
    // Skeu Output
    addAndMakeVisible(_outputDial);
    _outputDial.setDoubleClickReturnValue(true, 0.0);
    _outputAttach = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor._treeState, outputID, _outputDial);
    
    // Skeu Output Label
    addAndMakeVisible(_outputLabel);
    
    // Skeu Phase Toggle
    addAndMakeVisible(_skeuPhaseToggle);
    _skeuPhaseToggleAttach = std::make_unique<juce::AudioProcessorValueTreeState::ButtonAttachment>(audioProcessor._treeState, phaseID, _skeuPhaseToggle);
    
    // Skeu HQ Toggle
    addAndMakeVisible(_skeuHQToggle);
    _skeuHQToggleAttach = std::make_unique<juce::AudioProcessorValueTreeState::ButtonAttachment>(audioProcessor._treeState, hqID, _skeuHQToggle);
}

IOModule::~IOModule()
{
}

void IOModule::paint (juce::Graphics& g)
{
    // Paint background
    g.setColour(m_mainCompColor.withAlpha(0.2f));
    g.drawLine(getWidth(), getHeight() * 0.125, getWidth(), getHeight() * 0.875, 3);
    
    // Update Label colors
    _inputDial.updateLabelColor(m_textAccentColor);
    _outputDial.updateLabelColor(m_textAccentColor);
    _inputLabel.setColour(juce::Label::ColourIds::textColourId, m_textAccentColor);
    _outputLabel.setColour(juce::Label::ColourIds::textColourId, m_textAccentColor);
    _skeuPhaseToggle.updateLabelColor(m_textAccentColor);
    _skeuHQToggle.updateLabelColor(m_textAccentColor);
    
    updateToggleColors(_skeuPhaseToggle);
    updateToggleColors(_skeuHQToggle);
}

void IOModule::resized()
{
    const auto dialX = getWidth() * 0.22;
    const auto dialY = getHeight() * 0.12;
    const auto toggleSize = getWidth() * 0.35;
    
    const auto ySkeuDialSpace = 1.3;
    const auto skeuDialSize = getWidth() * 0.55;
    const auto toggleX = getWidth() * 0.15;
        
    _inputDial.setBounds(dialX,
                         dialY,
                         skeuDialSize,
                         skeuDialSize);
    const auto inputSpace = _inputDial.getY() + _inputDial.getHeight();
    
    _outputDial.setBounds(dialX,
                          inputSpace * ySkeuDialSpace,
                          skeuDialSize,
                          skeuDialSize);
    const auto outputSpace = _outputDial.getY() + _outputDial.getHeight();
    
    _skeuPhaseToggle.setBounds(toggleX,
                               outputSpace * 1.1,
                               toggleSize,
                               toggleSize);
    const auto hqSpace = _skeuPhaseToggle.getX() + _skeuPhaseToggle.getWidth();
    
    _skeuHQToggle.setBounds(hqSpace,
                            _skeuPhaseToggle.getY(),
                            toggleSize,
                            toggleSize);
}

void IOModule::updateToggleColors(viator_gui::ToggleButton& button)
{
    button.setColour(juce::ToggleButton::ColourIds::tickDisabledColourId, m_bgColor);
    button.setColour(juce::ToggleButton::ColourIds::tickColourId, m_textColor);
}
