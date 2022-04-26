/*
  ==============================================================================

    UI-Paint.cpp
    Created: 24 Oct 2021 1:41:00am
    Author:  Landon Viator

  ==============================================================================
*/

#include "../PluginEditor.h"

void HeaderDemoAudioProcessorEditor::uiPaint(juce::Graphics &g)
{
    // Background
    g.fillAll(juce::Colours::black);

    // Background
    auto background = juce::ImageCache::getFromMemory(BinaryData::pluginBackground2_png, BinaryData::pluginBackground2_pngSize);
    g.drawImageWithin(background, getWidth() * 0.025, getHeight() * 0.1, getWidth() * 0.95, getHeight() * 0.85, juce::RectanglePlacement::stretchToFit);
    
    // Logo
    auto logo = juce::ImageCache::getFromMemory(BinaryData::landon5504_png, BinaryData::landon5504_pngSize);
    g.drawImageWithin(logo, getWidth() * 0.025, getHeight() * 0.02, getWidth() * 0.15, getHeight() * 0.075, juce::RectanglePlacement::stretchToFit);
}
