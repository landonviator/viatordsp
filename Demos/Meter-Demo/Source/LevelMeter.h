/*
  ==============================================================================

    LevelMeter.h
    Created: 1 Apr 2022 6:21:06pm
    Author:  Landon Viator

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"

//==============================================================================
/*
*/
class LevelMeter  : public juce::Component, private juce::Timer
{
public:
    LevelMeter(MeterDemoAudioProcessor& audioProcessor);
    ~LevelMeter() override;

    void paint (juce::Graphics&) override;
    void resized() override;
    
    void timerCallback() final
    {
        leftMeter.setValue(audioProcessor.getLeftLevel());
        
        if(leftMeter.getValue() > leftMax)
        {
            leftMax = leftMeter.getValue();
            leftMeterString = leftMeter.getTextFromValue(leftMeter.getValue());
            leftSliderValueLabel.setText(leftMeterString, juce::dontSendNotification);
            setLabelColorLogic();
        }
        
        rightMeter.setValue(audioProcessor.getRightLevel());
    }

private:
    MeterDemoAudioProcessor& audioProcessor;
    
    juce::Slider leftMeter;
    juce::Slider rightMeter;
    juce::ToggleButton meterToggle;
    juce::String leftMeterString;
    
    juce::Label leftSliderValueLabel;
    void setLabelColorLogic();
    
    std::vector<std::string> meterNumbers =
    {
        "-0-",
        "-9-",
        "-18-",
        "-27-",
        "-36-",
        "-45-",
        "-54-"
    };
    
    void mouseDown(const juce::MouseEvent& event) override
    {
        leftMax = -60.0;
    }
    
    float leftMax = -60.0;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (LevelMeter)
};
