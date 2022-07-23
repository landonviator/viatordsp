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
, _inputDial(0, " dB", -24.0, 24.0)
, _outputDial(0, " dB", -24.0, 24.0)
, _skeuPhaseToggle(false, "HQ", true)
, _skeuHQToggle (true, "HQ", false)
, _flatInputDial(" dB", "Input", -24.0, 24.0, 0.01, 0.0)
, _flatOutputDial(" dB", "Output", -24.0, 24.0, 0.01, 0.0)
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
    
    // Flat Input
    addAndMakeVisible(_flatInputDial);
    _flatInputAttach = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor._treeState, inputID, _flatInputDial);
    
    // Flat Output
    addAndMakeVisible(_flatOutputDial);
    _flatOutputAttach = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor._treeState, outputID, _flatOutputDial);
    
    // Skeu Phase Toggle
    addAndMakeVisible(_skeuPhaseToggle);
    _skeuPhaseToggleAttach = std::make_unique<juce::AudioProcessorValueTreeState::ButtonAttachment>(audioProcessor._treeState, phaseID, _skeuPhaseToggle);
    
    // Flat Phase Toggle
    addAndMakeVisible(_flatPhaseToggle);
    _flatPhaseToggleAttach = std::make_unique<juce::AudioProcessorValueTreeState::ButtonAttachment>(audioProcessor._treeState, phaseID, _flatPhaseToggle);
    
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
    
    // Update colors on theme change
    updateSliderColors(_flatInputDial);
    updateSliderColors(_flatOutputDial);
    
    // Update Label colors
    _inputDial.updateLabelColor(m_textAccentColor);
    _outputDial.updateLabelColor(m_textAccentColor);
    _inputLabel.setColour(juce::Label::ColourIds::textColourId, m_textAccentColor);
    _outputLabel.setColour(juce::Label::ColourIds::textColourId, m_textAccentColor);
    _skeuPhaseToggle.updateLabelColor(m_textAccentColor);
    _skeuHQToggle.updateLabelColor(m_textAccentColor);
    
    // Update flat comp colors
    updateFlatColors();
    
    updateToggleColors(_skeuPhaseToggle);
    updateToggleColors(_skeuHQToggle);
}

void IOModule::resized()
{
    const auto dialX = getWidth() * 0.22;
    const auto dialY = getHeight() * 0.12;
    
    // Skeuomorphic
    if (_settingsPage.getUIType())
    {
        activateFlatComps(false);
        const auto ySkeuDialSpace = 1.3;
        const auto skeuDialSize = getWidth() * 0.55;
        const auto toggleX = getWidth() * 0.15;
        const auto toggleSize = getWidth() * 0.35;
        
        _inputDial.setBounds(dialX, dialY, skeuDialSize, skeuDialSize);
        _outputDial.setBounds(dialX, _inputDial.getY() + _inputDial.getHeight() * ySkeuDialSpace, skeuDialSize, skeuDialSize);
        _skeuPhaseToggle.setBounds(toggleX, _outputDial.getY() + _outputDial.getHeight() * 1.1, toggleSize, toggleSize);
        _skeuHQToggle.setBounds(_skeuPhaseToggle.getX() + _skeuPhaseToggle.getWidth(), _skeuPhaseToggle.getY(), toggleSize, toggleSize);
        activateSkeuComps(true);
    }
    
    // Flat
    else
    {
        activateSkeuComps(false);
        const auto yFlatDialSpace = 1.3;
        const auto flatDialSize = getWidth() * 0.55;
        _flatInputDial.setBounds(dialX, dialY, flatDialSize, flatDialSize);
        _flatOutputDial.setBounds(dialX, _inputDial.getY() + _inputDial.getHeight() * yFlatDialSpace, flatDialSize, flatDialSize);
        _flatPhaseToggle.setBounds(dialX, _flatOutputDial.getY() + _flatOutputDial.getHeight() * 1.1, flatDialSize, flatDialSize * 0.3);
        activateFlatComps(true);
    }
}

void IOModule::activateSkeuComps(bool shouldBeOn)
{
    // Dials
    _inputDial.setEnabled(shouldBeOn);
    _inputDial.setVisible(shouldBeOn);
    _outputDial.setEnabled(shouldBeOn);
    _outputDial.setVisible(shouldBeOn);
    
    // Toggle
    _skeuPhaseToggle.setEnabled(shouldBeOn);
    _skeuPhaseToggle.setVisible(shouldBeOn);
    
    // Switch component attachment
    if (shouldBeOn)
    {
        if (_inputLabel.getAttachedComponent() != &_inputDial)
        {
            _inputLabel.attachToComponent(&_inputDial, false);
        }
        
        if (_outputLabel.getAttachedComponent() != &_outputDial)
        {
            _outputLabel.attachToComponent(&_outputDial, false);
        }
    }
}

void IOModule::activateFlatComps(bool shouldBeOn)
{
    // Dials
    _flatInputDial.setEnabled(shouldBeOn);
    _flatInputDial.setVisible(shouldBeOn);
    _flatOutputDial.setEnabled(shouldBeOn);
    _flatOutputDial.setVisible(shouldBeOn);
    
    // Toggle
    _flatPhaseToggle.setEnabled(shouldBeOn);
    _flatPhaseToggle.setVisible(shouldBeOn);
    
    // Switch component attachment
    if (shouldBeOn)
    {
        if (_inputLabel.getAttachedComponent() != &_flatInputDial)
        {
            _inputLabel.attachToComponent(&_flatInputDial, false);
        }
        
        if (_outputLabel.getAttachedComponent() != &_flatOutputDial)
        {
            _outputLabel.attachToComponent(&_flatOutputDial, false);
        }
    }
}

void IOModule::updateSliderColors(viator_gui::Dial &slider)
{
    slider.setColour(juce::Slider::ColourIds::rotarySliderFillColourId, m_mainCompFillColor);
    slider.setColour(juce::Slider::ColourIds::rotarySliderOutlineColourId, m_bgLighterColor);
    slider.setColour(juce::Slider::ColourIds::trackColourId, m_textAccentColor);
    slider.setColour(juce::Slider::ColourIds::textBoxOutlineColourId, juce::Colours::black.withAlpha(0.0f));
    slider.setColour(juce::Slider::ColourIds::textBoxTextColourId, m_textAccentColor);
    slider.setColour(juce::Slider::ColourIds::thumbColourId, m_mainCompColor);
    slider.setColour(juce::Slider::ColourIds::backgroundColourId, m_bgTransparent);
    
    if (_settingsPage.getGlowState())
    {
        slider.updateShadowColor(m_mainCompColor, _settingsPage.getCurrentGlowValue());
    }
    
    else
    {
        slider.updateShadowColor(juce::Colours::black, 0.4f);
    }
    
    slider.forceShadow();
}

void IOModule::updateToggleColors(viator_gui::ToggleButton& button)
{
    button.setColour(juce::ToggleButton::ColourIds::tickDisabledColourId, m_bgColor);
    button.setColour(juce::ToggleButton::ColourIds::tickColourId, m_textColor);
}

void IOModule::updateFlatColors()
{
    _flatPhaseToggle.setColour(juce::TextButton::ColourIds::buttonColourId, juce::Colours::transparentBlack);
    _flatPhaseToggle.setColour(juce::ComboBox::ColourIds::outlineColourId, m_textAccentColor);
    _flatPhaseToggle.setColour(juce::TextButton::ColourIds::buttonOnColourId, juce::Colours::transparentBlack);
    _flatPhaseToggle.setColour(juce::TextButton::ColourIds::textColourOnId, m_mainCompColor);
    _flatPhaseToggle.setColour(juce::TextButton::ColourIds::textColourOffId, m_textAccentColor);
}
