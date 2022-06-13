/*
  ==============================================================================

    SliderProps.cpp
    Created: 11 Jun 2022 1:46:51pm
    Author:  Landon Viator

  ==============================================================================
*/

#include "../../../PluginEditor.h"

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
    slider.setRange(0.0, 10.0, 0.1);
    slider.setDoubleClickReturnValue(true, 0.0);
    slider.setTextValueSuffix(" dB");
    slider.setLookAndFeel(&customDialLAF);
    
    shadowProperties.radius = 8;
    shadowProperties.offset = juce::Point<int> (0, 0);
    
    if (m_settingsPage.getGlowState())
    {
        shadowProperties.colour = m_mainCompColor;
    }
    
    else
    {
        shadowProperties.colour = juce::Colours::black;
    }
    
    dialShadow.setShadowProperties (shadowProperties);
    
    slider.setComponentEffect(&dialShadow);
}
