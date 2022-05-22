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

//==============================================================================
/*
*/
class HeaderComponent  : public juce::Component
{
public:
    HeaderComponent();
    ~HeaderComponent() override;

    void paint (juce::Graphics&) override;
    void resized() override;
    
    bool getSettingsButtonToggleState();

private:
    
    SettingsButtonLAF customSettingsButtonLAF;
    
    juce::TextButton settingsButton;
    void settingsButtonProps();
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (HeaderComponent)
};
