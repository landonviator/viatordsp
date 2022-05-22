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

private:
    
    juce::Slider menuSlider1;
    MenuSliderLAF customMenuSlider;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (SettingsPage)
};
