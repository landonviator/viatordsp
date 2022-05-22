/*
  ==============================================================================

    SettingsPage.h
    Created: 21 May 2022 11:48:39pm
    Author:  Landon Viator

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "../LookAndFeel/MenuSliderLAF.h"
#include "../LookAndFeel/ToggleButtonLAF.h"
#include "../LookAndFeel/LabelLAF.h"

//==============================================================================
/*
*/
class SettingsPage  : public juce::Component
{
public:
    SettingsPage();
    ~SettingsPage() override;

    void paint (juce::Graphics&) override;
    void resized() override;

    bool getShouldUseToolTips();
    
private:
    
    juce::Slider menuSlider1;
    MenuSliderLAF customMenuSlider;
    
    juce::TextButton toolTipToggle;
    juce::Label tooltipLabel;
    ToggleButtonLAF customToggleButton;
    LabelLAF customLabelLAF;
    bool shouldUseToolTips = false;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (SettingsPage)
};
