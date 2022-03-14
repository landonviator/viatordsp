/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"

//==============================================================================
/**
*/
class WaveformviewerAudioProcessorEditor  : public juce::AudioProcessorEditor
{
public:
    WaveformviewerAudioProcessorEditor (WaveformviewerAudioProcessor&);
    ~WaveformviewerAudioProcessorEditor() override;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;

private:
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    WaveformviewerAudioProcessor& audioProcessor;
    
    viator_gui::Fader waveZoom;
    viator_gui::PushButton channelToggle;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (WaveformviewerAudioProcessorEditor)
};
