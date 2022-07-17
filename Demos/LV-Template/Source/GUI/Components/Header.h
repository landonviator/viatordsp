/*
  ==============================================================================

    Header.h
    Created: 17 Jul 2022 2:46:42pm
    Author:  Landon Viator

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "../../Parameters/Globals.h"
#include "../../GUI/LookAndFeel/Buttons.h"

//==============================================================================
/*
*/
class Header  : public juce::Component
{
public:
    Header();
    ~Header() override;

    void paint (juce::Graphics&) override;
    void resized() override;
    bool showSettings();

private:
    
    juce::TextButton m_settingsButton;
    void setTextButtonProps(juce::TextButton& button);
    void setSettingsButtonProps();
    ButtonStyle customButtonLAF;
    
    std::vector<juce::TextButton*> buttons =
    {
        &m_settingsButton
    };
    
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Header)
};
