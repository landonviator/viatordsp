/*
  ==============================================================================

    HeaderComponent.h
    Created: 21 May 2022 10:21:27pm
    Author:  Landon Viator

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "../LookAndFeel/SettingsButtonLAF.h"
#include "../LookAndFeel/LabelLAF.h"
#include "../PluginProcessor.h"
#include "../Globals.h"
//==============================================================================
/*
*/
class HeaderComponent  : public juce::Component, private juce::Timer
{
public:
    HeaderComponent(LVTemplateAudioProcessor&);
    ~HeaderComponent() override;

    void paint (juce::Graphics&) override;
    void resized() override;
    
    bool getSettingsButtonToggleState();
    
    void timerCallback() override
    {
        cpu = audioProcessor.getCPULoad();
        cpuLabel.setText(std::to_string(static_cast<int>(cpu)) + "%", juce::dontSendNotification);
    }
    
    void updateBGColor();

private:
    
    LVTemplateAudioProcessor& audioProcessor;
    
    SettingsButtonLAF customSettingsButtonLAF;
    
    juce::TextButton settingsButton;
    void settingsButtonProps();
    
    juce::Label cpuLabel;
    float cpu = 0;
    LabelLAF customLabelLAF;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (HeaderComponent)
};
