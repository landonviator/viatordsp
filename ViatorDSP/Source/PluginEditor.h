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
class ViatorDSPAudioProcessorEditor  : public juce::AudioProcessorEditor
, private juce::Timer
{
public:
    ViatorDSPAudioProcessorEditor (ViatorDSPAudioProcessor&);
    ~ViatorDSPAudioProcessorEditor() override;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;
    
    void timerCallback() override
    {
        cpu = audioProcessor.getCPULoad();
        label.setText(std::to_string(static_cast<int>(cpu)) + "%", juce::dontSendNotification);
    }

private:
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    ViatorDSPAudioProcessor& audioProcessor;
    
    float topHeaderMargin;
    float cpu = 0;
    
    viator_gui::Label label {false};

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (ViatorDSPAudioProcessorEditor)
};
