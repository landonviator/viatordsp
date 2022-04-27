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
class HeaderDemoAudioProcessorEditor  : public juce::AudioProcessorEditor, private juce::Timer
{
public:
    HeaderDemoAudioProcessorEditor (HeaderDemoAudioProcessor&);
    ~HeaderDemoAudioProcessorEditor() override;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;
    
    void timerCallback() override
    {
        cpu = audioProcessor.getCPU();
        cpuLabel.setText("CPU " + juce::String (cpu, 2) + "%", juce::dontSendNotification);
    }
    
private:
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    HeaderDemoAudioProcessor& audioProcessor;
    
    /** Boiler plate UI stuff */
    void uiConstructor();
    void initWindow();
    void uiPaint(juce::Graphics &g);
    void uiResized();
    
    juce::Label cpuLabel;
    float cpu = 0;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (HeaderDemoAudioProcessorEditor)
};
