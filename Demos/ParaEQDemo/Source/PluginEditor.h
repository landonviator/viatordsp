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
class ParaEQDemoAudioProcessorEditor  : public juce::AudioProcessorEditor
{
public:
    ParaEQDemoAudioProcessorEditor (ParaEQDemoAudioProcessor&);
    ~ParaEQDemoAudioProcessorEditor() override;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;

private:
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    ParaEQDemoAudioProcessor& audioProcessor;
    
    void setSliderProps(juce::Slider& slider);
    void initWindowSize();
    
    juce::Slider band1GainDial;
    juce::Slider band1CutoffDial;
    juce::Slider band1QDial;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (ParaEQDemoAudioProcessorEditor)
};
