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
    g.drawImageWithin(background, 0, headerSize, getWidth(), backgroundSize, juce::RectanglePlacement::stretchToFit);
    
    // Logo layer
    auto headerLogo = juce::ImageCache::getFromMemory(BinaryData::landon5504_png, BinaryData::landon5504_pngSize);
    
    // Draw and position the image
    g.drawImageWithin(headerLogo, leftHeaderMargin, topHeaderMargin, getWidth() * 0.15, getHeight() * 0.05, juce::RectanglePlacement::centred);
}
