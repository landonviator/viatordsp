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
class MeterDemoAudioProcessorEditor  : public juce::AudioProcessorEditor, private juce::Timer
{
public:
    MeterDemoAudioProcessorEditor (MeterDemoAudioProcessor&);
    ~MeterDemoAudioProcessorEditor() override;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;
    
    void timerCallback() final
    {
        //leftMeter.setValue(audioProcessor.getLeftLevel());
        //rightMeter.setValue(audioProcessor.getRightLevel());
    }

private:
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    MeterDemoAudioProcessor& audioProcessor;
    
    juce::Slider leftMeter;
    juce::Slider rightMeter;
    juce::ToggleButton meterToggle;
    juce::Label sliderValueLabel;
    
    std::vector<std::string> meterNumbers =
    {
        "- -3",
        "- -6",
        "- -9",
        "- -12",
        "- -15",
        "- -18",
        "- -21",
        "- -24",
        "- -27",
        "- -30",
        "- -33",
        "- -36",
        "- -39",
        "- -42",
        "- -45",
        "- -48",
        "- -51",
    };

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MeterDemoAudioProcessorEditor)
};
