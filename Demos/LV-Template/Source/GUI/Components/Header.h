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
#include "../../GUI/LookAndFeel/MenuLAF.h"
#include "../../PluginProcessor.h"

//==============================================================================
/*
*/
class Header  : public juce::Component
{
public:
    Header(LVTemplateAudioProcessor&);
    ~Header() override;

    void paint (juce::Graphics&) override;
    void resized() override;
    bool showSettings();

private:
    
    LVTemplateAudioProcessor& audioProcessor;
    
    juce::TextButton _settingsButton;
    void setTextButtonProps(juce::TextButton& button);
    void setSettingsButtonProps();
    ButtonStyle customButtonLAF;
    
    std::vector<juce::TextButton*> buttons =
    {
        &_settingsButton
    };
    
    viator_gui::Menu _presetBrowser;
    void setPresetBrowserProps();
    void setPresetBrowserItems();
    void setPreset(float input, float output);
    std::unique_ptr<juce::AudioProcessorValueTreeState::ComboBoxAttachment> _presetMenuAttach;
    juce::Custom_Menu_Boy _customMenu;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Header)
};
