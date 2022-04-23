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
    auto background = juce::ImageCache::getFromMemory(BinaryData::background_png, BinaryData::background_pngSize);
    g.drawImageWithin(background, 0, 0, getWidth(), getHeight(), juce::RectanglePlacement::stretchToFit);
    
    auto back = juce::ImageCache::getFromMemory(BinaryData::Articulations_back_png, BinaryData::Articulations_back_pngSize);
    
    g.drawImageWithin(back, 128, 128, 32, 32, juce::RectanglePlacement::stretchToFit);
    
    auto decor = juce::ImageCache::getFromMemory(BinaryData::Articulations_decore_png, BinaryData::Articulations_decore_pngSize);
    
    g.drawImageWithin(decor, 128, 128, 32, 32, juce::RectanglePlacement::stretchToFit);
    
    // Logo layer
    auto headerLogo = juce::ImageCache::getFromMemory(BinaryData::landon5504_png, BinaryData::landon5504_pngSize);
    
    // Draw and position the image
    g.drawImageWithin(headerLogo, getWidth() * 0.42, topHeaderMargin, getWidth() * 0.15, getHeight() * 0.05, juce::RectanglePlacement::centred);
}
