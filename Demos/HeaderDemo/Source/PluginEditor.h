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
        cpu = audioProcessor.getCPULoad();
        cpuLabel.setText(std::to_string(static_cast<int>(cpu)) + "%", juce::dontSendNotification);
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
    bool constructorFinished = false;
    float topHeaderMargin;
    float cpu = 0;
    
    juce::Label cpuLabel;
    juce::TextButton cpuButton;
    viator_gui::Menu msMenu;
    
    viator_gui::Dial dial {" dB", "", -12.0, 12.0, 0.1, 0.0};
    
    std::unique_ptr <juce::AudioProcessorValueTreeState::ButtonAttachment> cpuButtonAttach;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (HeaderDemoAudioProcessorEditor)
};
