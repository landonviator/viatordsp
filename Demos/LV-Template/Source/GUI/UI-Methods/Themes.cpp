/*
  ==============================================================================

    Themes.cpp
    Created: 17 Jul 2022 12:56:01am
    Author:  Landon Viator

  ==============================================================================
*/

#include "../../PluginEditor.h"

void LVTemplateAudioProcessorEditor::setPluginTheme(Theme newTheme)
{
    _pluginTheme = newTheme;
    
    switch (newTheme)
    {
        case Theme::kDracula:
        {
            m_bgColor = juce::Colour::fromRGB(40, 42, 53);
            m_bgLighterColor = juce::Colour::fromRGB(53, 55, 70);
            m_textAccentColor = juce::Colour::fromRGB(96, 110, 157);
            m_bgTransparent = juce::Colours::black.withAlpha(0.5f);
            m_mainCompColor = juce::Colour::fromRGB(168, 132, 222);
            m_mainCompFillColor = juce::Colour::fromRGB(245, 117, 191).withAlpha(0.6f);
            break;
        }
            
        case Theme::kPrimeDark:
        {
            m_bgColor = juce::Colour::fromRGB(33, 37, 43);
            m_bgLighterColor = juce::Colour::fromRGB(40, 44, 52);
            m_textAccentColor = juce::Colour::fromRGB(150, 152, 154);
            m_bgTransparent = juce::Colours::black.withAlpha(0.5f);
            m_mainCompColor = juce::Colour::fromRGB(93, 174, 242);
            m_mainCompFillColor = juce::Colour::fromRGB(171, 178, 192).withAlpha(0.6f);
            break;
        }
            
        case Theme::kTokyoLofi:
        {
            m_bgColor = juce::Colour::fromRGB(30, 35, 54);
            m_bgLighterColor = juce::Colour::fromRGB(35, 40, 61);
            m_textAccentColor = juce::Colour::fromRGB(107, 208, 234).darker(1.0);
            m_bgTransparent = juce::Colours::black.withAlpha(0.5f);
            m_mainCompColor = juce::Colour::fromRGB(12, 164, 190);
            m_mainCompFillColor = juce::Colour::fromRGB(96, 138, 212).withAlpha(0.6f);
            break;
        }
            
        case Theme::kWinter:
        {
            m_bgColor = juce::Colour::fromRGB(0, 22, 41);
            m_bgLighterColor = juce::Colour::fromRGB(51, 97, 125);
            m_textAccentColor = juce::Colour::fromRGB(203, 237, 248).darker(1.0);
            m_bgTransparent = juce::Colours::black.withAlpha(0.5f);
            m_mainCompColor = juce::Colour::fromRGB(210, 220, 234);
            m_mainCompFillColor = juce::Colour::fromRGB(210, 220, 234).withAlpha(0.6f);
            break;
        }
            
        case Theme::kFoxy:
        {
            m_bgColor = juce::Colour::fromRGB(43, 43, 47);
            m_bgLighterColor = juce::Colour::fromRGB(28, 27, 29).brighter(0.1);
            m_textAccentColor = juce::Colour::fromRGB(121, 97, 160);
            m_bgTransparent = juce::Colours::black.withAlpha(0.5f);
            m_mainCompColor = juce::Colour::fromRGB(145, 82, 136);
            m_mainCompFillColor = juce::Colour::fromRGB(96, 148, 87).withAlpha(0.6f);
            break;
        }
            
        case Theme::kPurp:
        {
            m_bgColor = juce::Colour::fromRGB(24, 14, 42).brighter(0.1);
            m_bgLighterColor = juce::Colour::fromRGB(35, 26, 52).brighter(0.05);
            m_textAccentColor = juce::Colour::fromRGB(165, 88, 129);
            m_bgTransparent = juce::Colours::black.withAlpha(0.5f);
            m_mainCompColor = juce::Colour::fromRGB(170, 130, 255);
            m_mainCompFillColor = juce::Colour::fromRGB(165, 88, 129).withAlpha(0.6f);
            break;
        }
            
        case Theme::kDull:
        {
            m_bgColor = juce::Colour::fromRGB(52, 52, 52);
            m_bgLighterColor = juce::Colour::fromRGB(38, 37, 38);
            m_textAccentColor = juce::Colour::fromRGB(173, 173, 173);
            m_bgTransparent = juce::Colours::black.withAlpha(0.5f);
            m_mainCompColor = juce::Colour::fromRGB(188, 120, 62);
            m_mainCompFillColor = juce::Colour::fromRGB(175, 175, 175).withAlpha(0.6f);
            break;
        }
    }
}
