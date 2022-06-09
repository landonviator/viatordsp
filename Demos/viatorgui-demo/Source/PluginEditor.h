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
class ViatorguidemoAudioProcessorEditor  : public juce::AudioProcessorEditor
{
public:
    ViatorguidemoAudioProcessorEditor (ViatorguidemoAudioProcessor&);
    ~ViatorguidemoAudioProcessorEditor() override;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;

private:
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    ViatorguidemoAudioProcessor& audioProcessor;
    
    juce::Slider slider1;
    juce::Slider slider2;
    juce::Slider slider3;
    void setSliderProps(juce::Slider& slider);
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (ViatorguidemoAudioProcessorEditor)
};
