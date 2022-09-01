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
class GUIPlaygroundAudioProcessorEditor  : public juce::AudioProcessorEditor, private juce::Timer
{
public:
    GUIPlaygroundAudioProcessorEditor (GUIPlaygroundAudioProcessor&);
    ~GUIPlaygroundAudioProcessorEditor() override;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;
    void timerCallback() override
    {
        if (progress <= 1.0)
        {
            progress += 0.01;
        }
    }

private:
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    GUIPlaygroundAudioProcessor& audioProcessor;
    
    juce::TextButton alertBtn;
    std::unique_ptr<juce::AlertWindow> alertWindow;
    juce::Slider slider;
    double progress = 0.0;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (GUIPlaygroundAudioProcessorEditor)
};
