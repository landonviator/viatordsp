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
class ParaEQDemoAudioProcessorEditor  : public juce::AudioProcessorEditor, private juce::Timer
{
public:
    ParaEQDemoAudioProcessorEditor (ParaEQDemoAudioProcessor&);
    ~ParaEQDemoAudioProcessorEditor() override;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;
    
    void timerCallback() override
    {
        if (audioProcessor.nextFFTBlockReady)
        {
            audioProcessor.drawNextFrameOfSpectrum();
            audioProcessor.nextFFTBlockReady = false;
            repaint();
        }
    }

private:
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    ParaEQDemoAudioProcessor& audioProcessor;
    
    void initWindowSize();
    
    /** Dials */
    juce::Slider band1GainDial;
    juce::Slider band1CutoffDial;
    juce::Slider band1QDial;
    
    juce::Slider band2GainDial;
    juce::Slider band2CutoffDial;
    juce::Slider band2QDial;
    
    juce::Slider band3GainDial;
    juce::Slider band3CutoffDial;
    juce::Slider band3QDial;
    
    juce::Slider band4GainDial;
    juce::Slider band4CutoffDial;
    juce::Slider band4QDial;
    
    juce::Slider band5GainDial;
    juce::Slider band5CutoffDial;
    juce::Slider band5QDial;
    
    juce::Slider band6GainDial;
    juce::Slider band6CutoffDial;
    juce::Slider band6QDial;
    
    juce::Slider band7GainDial;
    juce::Slider band7CutoffDial;
    juce::Slider band7QDial;
    void setSliderProps(juce::Slider& slider);
    
    std::vector<juce::Slider*> dials =
    {
        &band1GainDial, &band1CutoffDial, &band1QDial,
        &band2GainDial, &band2CutoffDial, &band2QDial,
        &band3GainDial, &band3CutoffDial, &band3QDial,
        &band4GainDial, &band4CutoffDial, &band4QDial,
        &band5GainDial, &band5CutoffDial, &band5QDial,
        &band6GainDial, &band6CutoffDial, &band6QDial,
        &band7GainDial, &band7CutoffDial, &band7QDial
    };
    
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> band1GainDialAttach;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> band1CutoffDialAttach;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> band1QDialAttach;
    
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> band2GainDialAttach;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> band2CutoffDialAttach;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> band2QDialAttach;
    
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> band3GainDialAttach;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> band3CutoffDialAttach;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> band3QDialAttach;
    
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> band4GainDialAttach;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> band4CutoffDialAttach;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> band4QDialAttach;
    
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> band5GainDialAttach;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> band5CutoffDialAttach;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> band5QDialAttach;
    
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> band6GainDialAttach;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> band6CutoffDialAttach;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> band6QDialAttach;
    
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> band7GainDialAttach;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> band7CutoffDialAttach;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> band7QDialAttach;
    
    /** Labels */
    juce::Label band1GainLabel {"Gain 1", "Gain 1"};
    juce::Label band1CutoffLabel {"Cutoff 1", "Cutoff 1"};
    juce::Label band1QLabel {"Q 1", "Q 1"};
    
    juce::Label band2GainLabel {"Gain 2", "Gain 2"};
    juce::Label band2CutoffLabel {"Cutoff 2", "Cutoff 2"};
    juce::Label band2QLabel {"Q 2", "Q 2"};
    
    juce::Label band3GainLabel {"Gain 3", "Gain 3"};
    juce::Label band3CutoffLabel {"Cutoff 3", "Cutoff 3"};
    juce::Label band3QLabel {"Q 3", "Q 3"};
    
    juce::Label band4GainLabel {"Gain 4", "Gain 4"};
    juce::Label band4CutoffLabel {"Cutoff 4", "Cutoff 4"};
    juce::Label band4QLabel {"Q 4", "Q 4"};
    
    juce::Label band5GainLabel {"Gain 5", "Gain 5"};
    juce::Label band5CutoffLabel {"Cutoff 5", "Cutoff 5"};
    juce::Label band5QLabel {"Q 5", "Q 5"};
    
    juce::Label band6GainLabel {"Gain 6", "Gain 6"};
    juce::Label band6CutoffLabel {"Cutoff 6", "Cutoff 6"};
    juce::Label band6QLabel {"Q 6", "Q 6"};
    
    juce::Label band7GainLabel {"Gain 7", "Gain 7"};
    juce::Label band7CutoffLabel {"Cutoff 7", "Cutoff 7"};
    juce::Label band7QLabel {"Q 7", "Q 7"};
    void setLabelProps(juce::Label& label);
    
    std::vector<juce::Label*> labels =
    {
        &band1GainLabel, &band1CutoffLabel, &band1QLabel,
        &band2GainLabel, &band2CutoffLabel, &band2QLabel,
        &band3GainLabel, &band3CutoffLabel, &band3QLabel,
        &band4GainLabel, &band4CutoffLabel, &band4QLabel,
        &band5GainLabel, &band5CutoffLabel, &band5QLabel,
        &band6GainLabel, &band6CutoffLabel, &band6QLabel,
        &band7GainLabel, &band7CutoffLabel, &band7QLabel
    };
    
    juce::Label graphLabel100 {"100", "100"};
    juce::Label graphLabel250 {"250", "250"};
    juce::Label graphLabel500 {"500", "500"};
    juce::Label graphLabel1000 {"1K", "1K"};
    juce::Label graphLabel2000 {"2K", "2K"};
    juce::Label graphLabel4000 {"4K", "4K"};
    juce::Label graphLabel8000 {"8K", "8K"};
    juce::Label graphLabel14000 {"14K", "14K"};
    
    std::vector<juce::Label*> graphLabels =
    {
        &graphLabel100, &graphLabel250, &graphLabel500,
        &graphLabel1000, &graphLabel2000, &graphLabel4000,
        &graphLabel8000, &graphLabel14000
    };
    
    juce::Rectangle<float> m_analyzerBounds;
    void drawFrame (juce::Graphics& g);
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (ParaEQDemoAudioProcessorEditor)
};
