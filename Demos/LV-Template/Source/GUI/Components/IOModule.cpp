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
, _inputDial(3, " dB", -24.0, 24.0)
, _outputDial(3, " dB", -24.0, 24.0)
, _flatInputDial(" dB", "Input", -24.0, 24.0, 0.01, 0.0)
, _flatOutputDial(" dB", "Output", -24.0, 24.0, 0.01, 0.0)
{
    addAndMakeVisible(_inputDial);
    _inputDial.setDoubleClickReturnValue(true, 0.0);
    
    addAndMakeVisible(_inputLabel);
    
    addAndMakeVisible(_outputDial);
    _outputDial.setDoubleClickReturnValue(true, 0.0);
    
    addAndMakeVisible(_outputLabel);
    
    addAndMakeVisible(_flatInputDial);
    addAndMakeVisible(_flatOutputDial);
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
    _inputDial.updateLabelColor(m_textAccentColor);
    _outputDial.updateLabelColor(m_textAccentColor);
    _inputLabel.setColour(juce::Label::ColourIds::textColourId, m_textAccentColor);
    _outputLabel.setColour(juce::Label::ColourIds::textColourId, m_textAccentColor);
}

void IOModule::resized()
{
    const auto dialX = getWidth() * 0.22;
    const auto dialY = getHeight() * 0.12;
    
    // Skeuomorphic
    if (_settingsPage.getUIType())
    {
        activateFlatDials(false);
        const auto ySkeuDialSpace = 1.3;
        const auto skeuDialSize = getWidth() * 0.55;
        _inputDial.setBounds(dialX, dialY, skeuDialSize, skeuDialSize);
        _outputDial.setBounds(dialX, _inputDial.getY() + _inputDial.getHeight() * ySkeuDialSpace, skeuDialSize, skeuDialSize);
        activateSkeuDials(true);
    }
    
    // Flat
    else
    {
        activateSkeuDials(false);
        const auto yFlatDialSpace = 1.3;
        const auto flatDialSize = getWidth() * 0.55;
        _flatInputDial.setBounds(dialX, dialY, flatDialSize, flatDialSize);
        _flatOutputDial.setBounds(dialX, _inputDial.getY() + _inputDial.getHeight() * yFlatDialSpace, flatDialSize, flatDialSize);
        activateFlatDials(true);
    }
}

void IOModule::activateSkeuDials(bool shouldBeOn)
{
    _inputDial.setEnabled(shouldBeOn);
    _inputDial.setVisible(shouldBeOn);
    _outputDial.setEnabled(shouldBeOn);
    _outputDial.setVisible(shouldBeOn);
    
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

void IOModule::activateFlatDials(bool shouldBeOn)
{
    _flatInputDial.setEnabled(shouldBeOn);
    _flatInputDial.setVisible(shouldBeOn);
    _flatOutputDial.setEnabled(shouldBeOn);
    _flatOutputDial.setVisible(shouldBeOn);
    
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
    slider.forceShadow();
}
