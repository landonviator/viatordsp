/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
HeaderDemoAudioProcessorEditor::HeaderDemoAudioProcessorEditor (HeaderDemoAudioProcessor& p)
    : AudioProcessorEditor (&p), audioProcessor (p)
{
    // Grab the window instance and create a rectangle
    juce::Rectangle<int> r = juce::Desktop::getInstance().getDisplays().getPrimaryDisplay()->userArea;
    
    // Using the width is more useful than the height, because we know the height will always be < than width
    int x = r.getWidth();
    
    auto width = 0;
    
    if (r.getWidth() <= 1440)
    {
        width = x;
    }
    
    else
    {
        width = x * 0.5;
    }
    
    auto height = width * 0.606;
    
    //Making the window resizable by aspect ratio and setting size
    AudioProcessorEditor::setResizable(true, true);
    AudioProcessorEditor::setResizeLimits(width * 0.75, height * 0.75, width * 1.25, height * 1.25);
    AudioProcessorEditor::getConstrainer()->setFixedAspectRatio(1.65);
    
    setSize (width, height);
}

HeaderDemoAudioProcessorEditor::~HeaderDemoAudioProcessorEditor()
{
}

//==============================================================================
void HeaderDemoAudioProcessorEditor::paint (juce::Graphics& g)
{
    g.fillAll(juce::Colours::black.brighter(0.1f));

    g.setColour (juce::Colours::whitesmoke.darker(1.0f));
    g.setFont (36.0f);
    g.drawFittedText ("Header", getLocalBounds(), juce::Justification::centredTop, 1);
}

void HeaderDemoAudioProcessorEditor::resized()
{
    // This is generally where you'll want to lay out the positions of any
    // subcomponents in your editor..
}
