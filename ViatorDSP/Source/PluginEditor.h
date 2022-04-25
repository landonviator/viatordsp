/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"
#include "./UI-Components/CPUComponent.h"

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
        cpuComponent.updateLabel(std::to_string(static_cast<int>(cpu)) + "%");
    }

private:
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    ViatorDSPAudioProcessor& audioProcessor;
    
    float cpu = 0;
    float topHeaderMargin;
    
    viator_gui::Label cpuLabel {false, "CPU"};
    viator_gui::Label cpuHeader {true, "CPU"};
    viator_gui::LEDButton cpuButton;
    viator_gui::ToggleButton toggleButton {true, "Toggle"};
    CPUComponent cpuComponent;
    
    viator_gui::FilmStripKnob knob;
    viator_gui::Fader fader;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (ViatorDSPAudioProcessorEditor)
};
