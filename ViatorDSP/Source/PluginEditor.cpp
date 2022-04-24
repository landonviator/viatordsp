/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
ViatorDSPAudioProcessorEditor::ViatorDSPAudioProcessorEditor (ViatorDSPAudioProcessor& p)
    : AudioProcessorEditor (&p), audioProcessor (p)
{
    startTimerHz(10);
    
    addAndMakeVisible(label);
    label.setText("CPU", juce::dontSendNotification);
    label.setJustificationType(juce::Justification::centred);
    label.setColour(juce::Label::ColourIds::textColourId, juce::Colours::whitesmoke.darker(1.0f));
    
    // Grab the window instance and create a rectangle
    juce::Rectangle<int> r = juce::Desktop::getInstance().getDisplays().getPrimaryDisplay()->userArea;
    
    // Using the width is more useful than the height, because we know the height will always be < than width
    int x = r.getWidth();
    
    auto width = 0;
    
    if (r.getWidth() <= 1440)
    {
        width = x * 0.65;
    }
    
    else
    {
        width = x * 0.5;
    }
    
    auto height = width * 0.7;
    
    //Making the window resizable by aspect ratio and setting size
    AudioProcessorEditor::setResizable(true, true);
    AudioProcessorEditor::setResizeLimits(width * 0.75, height * 0.75, width * 1.25, height * 1.25);
    AudioProcessorEditor::getConstrainer()->setFixedAspectRatio(1.43);
    
    setSize (width, height);
}

ViatorDSPAudioProcessorEditor::~ViatorDSPAudioProcessorEditor()
{
}

//==============================================================================
void ViatorDSPAudioProcessorEditor::paint (juce::Graphics& g)
{
    // Background
    g.fillAll(juce::Colours::black);

    // Background
    auto background = juce::ImageCache::getFromMemory(BinaryData::background_png, BinaryData::background_pngSize);
    g.drawImageWithin(background, 0, 0, getWidth(), getHeight(), juce::RectanglePlacement::stretchToFit);
        
    // Logo layer
    auto headerLogo = juce::ImageCache::getFromMemory(BinaryData::landon5504_png, BinaryData::landon5504_pngSize);
        
    // Draw and position the image
    g.drawImageWithin(headerLogo, getWidth() * 0.42, topHeaderMargin, getWidth() * 0.15, getHeight() * 0.05, juce::RectanglePlacement::centred);
}

void ViatorDSPAudioProcessorEditor::resized()
{
    topHeaderMargin = getHeight() * 0.015;
    auto labelSize = getWidth() * 0.05;
    
    label.setBounds(getWidth() * 0.93, getHeight() * 0.87, labelSize, labelSize);
}
