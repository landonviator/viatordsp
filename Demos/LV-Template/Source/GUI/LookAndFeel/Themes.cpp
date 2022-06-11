/*
  ==============================================================================

    Themes.cpp
    Created: 10 Jun 2022 11:34:28pm
    Author:  Landon Viator

  ==============================================================================
*/

#include "../../PluginEditor.h"

void LVTemplateAudioProcessorEditor::setPluginTheme(Theme newTheme)
{
    switch (newTheme)
    {
        case Theme::kDracula:
        {
            m_bgColor = juce::Colour::fromRGB(40, 42, 53);
            m_bgLighterColor = juce::Colour::fromRGB(53, 55, 70);
            m_textAccentColor = juce::Colour::fromRGB(96, 110, 157);
            m_bgTransparent = juce::Colours::black.withAlpha(0.5f);
            break;
        }
            
        case Theme::kPrimeDark:
        {
            m_bgColor = juce::Colour::fromRGB(33, 37, 43);
            m_bgLighterColor = juce::Colour::fromRGB(40, 44, 52);
            m_textAccentColor = juce::Colour::fromRGB(150, 152, 154);
            m_bgTransparent = juce::Colours::black.withAlpha(0.5f);
            break;
        }
            
        case Theme::kPrimeLight:
        {
            m_bgColor = juce::Colour::fromRGB(170, 171, 172);
            m_bgLighterColor = juce::Colour::fromRGB(245, 245, 245);
            m_textAccentColor = juce::Colour::fromRGB(105, 143, 213);
            m_bgTransparent = juce::Colours::black.withAlpha(0.5f);
            break;
        }
            
        case Theme::kTokyoLofi:
        {
            m_bgColor = juce::Colour::fromRGB(22, 22, 31);
            m_bgLighterColor = juce::Colour::fromRGB(27, 27, 39);
            m_textAccentColor = juce::Colour::fromRGB(107, 208, 234);
            m_bgTransparent = juce::Colours::black.withAlpha(0.5f);
            break;
        }
            
        case Theme::kTokyoLight:
        {
            m_bgColor = juce::Colour::fromRGB(203, 204, 210);
            m_bgLighterColor = juce::Colour::fromRGB(213, 213, 217);
            m_textAccentColor = juce::Colour::fromRGB(169, 78, 70);
            m_bgTransparent = juce::Colours::black.withAlpha(0.5f);
            break;
        }
            
        case Theme::kWinter:
        {
            m_bgColor = juce::Colour::fromRGB(0, 22, 41);
            m_bgLighterColor = juce::Colour::fromRGB(1, 161, 218);
            m_textAccentColor = juce::Colour::fromRGB(203, 237, 248);
            m_bgTransparent = juce::Colours::black.withAlpha(0.5f);
            break;
        }
            
        case Theme::kFoxy:
        {
            m_bgColor = juce::Colour::fromRGB(43, 43, 47);
            m_bgLighterColor = juce::Colour::fromRGB(28, 27, 29);
            m_textAccentColor = juce::Colour::fromRGB(121, 97, 160);
            m_bgTransparent = juce::Colours::black.withAlpha(0.5f);
            break;
        }
            
        case Theme::kMaterialLight:
        {
            m_bgColor = juce::Colour::fromRGB(231, 233, 235);
            m_bgLighterColor = juce::Colour::fromRGB(45, 44, 44);
            m_textAccentColor = juce::Colour::fromRGB(170, 170, 171);
            m_bgTransparent = juce::Colours::black.withAlpha(0.5f);
            break;
        }
            
        case Theme::kPurp:
        {
            m_bgColor = juce::Colour::fromRGB(24, 14, 42);
            m_bgLighterColor = juce::Colour::fromRGB(35, 26, 52);
            m_textAccentColor = juce::Colour::fromRGB(165, 88, 129);
            m_bgTransparent = juce::Colours::black.withAlpha(0.5f);
            break;
        }
            
        case Theme::kDull:
        {
            m_bgColor = juce::Colour::fromRGB(52, 52, 52);
            m_bgLighterColor = juce::Colour::fromRGB(38, 37, 38);
            m_textAccentColor = juce::Colour::fromRGB(173, 173, 173);
            m_bgTransparent = juce::Colours::black.withAlpha(0.5f);
            break;
        }
    }
}
