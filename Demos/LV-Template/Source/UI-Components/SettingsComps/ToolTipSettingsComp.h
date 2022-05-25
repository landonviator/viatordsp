/*
  ==============================================================================

    ToolTipSettingsComp.h
    Created: 24 May 2022 10:08:12pm
    Author:  Landon Viator

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "../../LookAndFeel/ToggleButtonLAF.h"

//==============================================================================
/*
*/
class ToolTipSettingsComp  : public juce::Component
{
public:
    ToolTipSettingsComp();
    ~ToolTipSettingsComp() override;

    void paint (juce::Graphics&) override;
    void resized() override;
    bool getShouldUseToolTips();
private:
    
    juce::TextButton toolTipToggle;
    juce::Label tooltipLabel;
    ToggleButtonLAF customToggleButton;
    bool shouldUseToolTips = false;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (ToolTipSettingsComp)
};
