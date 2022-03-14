/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
WaveformviewerAudioProcessorEditor::WaveformviewerAudioProcessorEditor (WaveformviewerAudioProcessor& p)
    : AudioProcessorEditor (&p), audioProcessor (p)
, waveZoom(" s", 32, 1024, 1.0, 256)
{
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    
    addAndMakeVisible(audioProcessor.waveViewer);
    audioProcessor.waveViewer.setColours(juce::Colours::black, juce::Colours::whitesmoke.withAlpha(0.5f));
    
    addAndMakeVisible(waveZoom);
    waveZoom.onValueChange = [this]()
    {
        audioProcessor.waveViewer.setBufferSize(waveZoom.getValue());
    };
    
    addAndMakeVisible(channelToggle);
    channelToggle.setButtonText("CH");
    
    channelToggle.onClick = [this]()
    {
        if (audioProcessor.getCurrentNumChannels() > 1)
        {
            channelToggle.getToggleState() ? audioProcessor.waveViewer.setNumChannels(2) : audioProcessor.waveViewer.setNumChannels(1);
        }
    };
    
    setSize (400, 400);
}

WaveformviewerAudioProcessorEditor::~WaveformviewerAudioProcessorEditor()
{
}

//==============================================================================
void WaveformviewerAudioProcessorEditor::paint (juce::Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (juce::Colours::black.brighter(0.1));

    g.setColour (juce::Colours::white);
    g.setFont (36.0f);
    g.drawFittedText ("Waveform Viewer", getLocalBounds(), juce::Justification::centredTop, 1);
}

void WaveformviewerAudioProcessorEditor::resized()
{
    auto buttonWidth = getWidth() * 0.16;
    auto buttonHeight = buttonWidth * 0.5;
    
    audioProcessor.waveViewer.setBounds(getLocalBounds().withSizeKeepingCentre(getWidth() * 0.5, getHeight() * 0.5));
    
    waveZoom.setBounds(audioProcessor.waveViewer.getX() + audioProcessor.waveViewer.getWidth(), audioProcessor.waveViewer.getY(), 96, audioProcessor.waveViewer.getHeight());
    
    channelToggle.setBounds(audioProcessor.waveViewer.getX() - (buttonWidth + buttonHeight * 0.5), audioProcessor.waveViewer.getY(), buttonWidth, buttonHeight);
}
