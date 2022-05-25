/*
  ==============================================================================

    UI-Paint.cpp
    Created: 24 Oct 2021 1:41:00am
    Author:  Landon Viator

  ==============================================================================
*/

#include "../PluginEditor.h"

void LVTemplateAudioProcessorEditor::uiPaint(juce::Graphics &g)
{
    g.fillAll(juce::Colours::black);
    
    auto scale = 0.85f;
    auto leftMargin = getWidth() * (1.0 - scale) * 0.5;
    auto topMargin = getHeight() * (1.0 - scale) * 0.5;
    
    // Background
    auto background = juce::ImageCache::getFromMemory(BinaryData::background_png, BinaryData::background_pngSize);
    g.drawImageWithin(background, leftMargin, topMargin, getWidth() * scale, getHeight() * scale, juce::RectanglePlacement::stretchToFit);
    
    largeDial.updateLabelColor(masterColor);
    headerComponent.repaint();
}
