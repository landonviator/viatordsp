/*
  ==============================================================================

    MasterColorComp.h
    Created: 24 May 2022 11:07:02pm
    Author:  Landon Viator

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "../../LookAndFeel/ColorButtonLAF.h"
#include "../../Globals.h"

//==============================================================================
/*
*/
class MasterColorComp  : public juce::Component
{
public:
    MasterColorComp();
    ~MasterColorComp() override;

    void paint (juce::Graphics&) override;
    void resized() override;

private:
    juce::TextButton redButton;
    juce::TextButton greenButton;
    juce::TextButton blueButton;
    juce::TextButton orangeButton;
    juce::TextButton yellowButton;
    juce::TextButton purpleButton;
    juce::TextButton asphaltButton;
    juce::TextButton blackButton;
    
    ColorButtonLAF customColorButtonLAF;
    
    juce::Label colorsLabel;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MasterColorComp)
};
