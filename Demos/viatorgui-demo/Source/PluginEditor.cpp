/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
ViatorguidemoAudioProcessorEditor::ViatorguidemoAudioProcessorEditor (ViatorguidemoAudioProcessor& p)
    : AudioProcessorEditor (&p), audioProcessor (p)
, dial(" dB", "Gain", -10.0, 10.0, 0.1, 0.0)
{
    addAndMakeVisible(dial);
    
    addAndMakeVisible(border);
    border.setText("Border");
    
    // Grab the window instance and create a rectangle
    juce::Rectangle<int> r = juce::Desktop::getInstance().getDisplays().getPrimaryDisplay()->userArea;
        
    // Using the width is more useful than the height, because we know the height will always be < than width
    int x = r.getWidth();
        
    // Plugin window will always initialize to half the screen width by half of that for a rectangle
    auto width = x / 2.0;
    auto height = width / 2.0;
        
    //Making the window resizable by aspect ratio and setting size
    AudioProcessorEditor::setResizable(true, true);
    AudioProcessorEditor::setResizeLimits(width * 0.75, height * 0.75, width * 1.25, height * 1.25);
    AudioProcessorEditor::getConstrainer()->setFixedAspectRatio(2.0);
        
    setSize(width, height);
}

ViatorguidemoAudioProcessorEditor::~ViatorguidemoAudioProcessorEditor()
{
}

//==============================================================================
void ViatorguidemoAudioProcessorEditor::paint (juce::Graphics& g)
{
    //Image layer from Illustrator
    auto pluginBackground = juce::ImageCache::getFromMemory(BinaryData::pluginBackground2_png, BinaryData::pluginBackground2_pngSize);
    
    // Draw and position the image
    g.drawImageWithin(pluginBackground, 0, 0, getWidth(), getHeight(), juce::RectanglePlacement::stretchToFit);

    g.setColour (juce::Colours::white);
    g.setFont (24.0f);
    g.drawFittedText ("Gui Widgets Demo", getLocalBounds(), juce::Justification::centredTop, 1);
}

void ViatorguidemoAudioProcessorEditor::resized()
{
    auto topMargin = getHeight() * 0.15;
    auto leftMargin = getWidth() * 0.1;
    auto dialSize = getWidth() * 0.18;
    
    dial.setBounds(leftMargin, topMargin, dialSize, dialSize);
    border.setBounds(dial.getX() + dial.getWidth() * 1.5, topMargin, dial.getWidth() * 1.5, dial.getHeight() * 3.0);
}
