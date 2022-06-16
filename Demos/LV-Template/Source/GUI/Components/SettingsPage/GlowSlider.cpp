/*
  ==============================================================================

    GlowSlider.cpp
    Created: 15 Jun 2022 10:29:52pm
    Author:  Landon Viator

  ==============================================================================
*/

#include "SettingsPage.h"

void SettingsPage::setGlowSliderProps()
{
    addAndMakeVisible(m_glowSlider);
    m_glowSlider.setSliderStyle(juce::Slider::SliderStyle::LinearHorizontal);
    m_glowSlider.setTextBoxStyle(juce::Slider::TextBoxLeft, false, 64, 32);
    m_glowSlider.setColour(juce::Slider::ColourIds::trackColourId, juce::Colour::fromRGB(53, 55, 70));
    m_glowSlider.setColour(juce::Slider::ColourIds::textBoxOutlineColourId, juce::Colours::transparentBlack);
    m_glowSlider.setColour(juce::Slider::ColourIds::textBoxTextColourId, juce::Colours::whitesmoke);
    m_glowSlider.setColour(juce::Slider::ColourIds::thumbColourId, juce::Colour::fromRGB(53, 55, 70));
    m_glowSlider.setColour(juce::Slider::ColourIds::backgroundColourId, juce::Colours::black);
    m_glowSlider.setDoubleClickReturnValue(true, 1.0);
    m_glowSlider.setRange(0.0, 1.0, 0.01);
    m_glowSlider.setValue(audioProcessor.variableTree.getProperty("glowslider"));
    
    m_glowSlider.onValueChange = [this]()
    {
        _currentGlowValue = m_glowSlider.getValue();
        audioProcessor.variableTree.setProperty("glowslider", m_glowSlider.getValue(), nullptr);
        getParentComponent()->repaint();
    };
}
