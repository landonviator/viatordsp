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
class Viator_DSP_LibraryAudioProcessorEditor  : public juce::AudioProcessorEditor
{
public:
    Viator_DSP_LibraryAudioProcessorEditor (Viator_DSP_LibraryAudioProcessor&);
    ~Viator_DSP_LibraryAudioProcessorEditor() override;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;

private:
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    Viator_DSP_LibraryAudioProcessor& audioProcessor;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Viator_DSP_LibraryAudioProcessorEditor)
};
