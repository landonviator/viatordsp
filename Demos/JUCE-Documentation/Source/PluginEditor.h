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
class JUCEDocumentationAudioProcessorEditor  : public juce::AudioProcessorEditor
{
public:
    JUCEDocumentationAudioProcessorEditor (JUCEDocumentationAudioProcessor&);
    ~JUCEDocumentationAudioProcessorEditor() override;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;

private:
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    JUCEDocumentationAudioProcessor& audioProcessor;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (JUCEDocumentationAudioProcessorEditor)
};
