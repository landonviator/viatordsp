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
class IRLoaderDemoAudioProcessorEditor  : public juce::AudioProcessorEditor
{
public:
    IRLoaderDemoAudioProcessorEditor (IRLoaderDemoAudioProcessor&);
    ~IRLoaderDemoAudioProcessorEditor() override;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;

private:
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    IRLoaderDemoAudioProcessor& audioProcessor;
    
    juce::TextButton loadBtn;
    std::unique_ptr<juce::FileChooser> fileChooser;
    juce::Label irName;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (IRLoaderDemoAudioProcessorEditor)
};
