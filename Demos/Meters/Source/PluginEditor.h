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
class MetersAudioProcessorEditor  : public juce::AudioProcessorEditor
, private juce::Timer
{
public:
    MetersAudioProcessorEditor (MetersAudioProcessor&);
    ~MetersAudioProcessorEditor() override;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;
    void timerCallback()
    {
        meter.setValue(audioProcessor.getRMS());
    }

private:
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    MetersAudioProcessor& audioProcessor;
    
    juce::Slider meter;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MetersAudioProcessorEditor)
};
