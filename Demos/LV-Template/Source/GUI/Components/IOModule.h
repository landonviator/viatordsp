/*
  ==============================================================================

    IOModule.h
    Created: 19 Jul 2022 3:52:10pm
    Author:  Landon Viator

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "../../PluginProcessor.h"
#include "SettingsPage.h"

//==============================================================================
/*
*/
class IOModule  : public juce::Component
{
public:
    IOModule(LVTemplateAudioProcessor&, SettingsPage&);
    ~IOModule() override;

    void paint (juce::Graphics&) override;
    void resized() override;

private:
    
    LVTemplateAudioProcessor& audioProcessor;
    SettingsPage& _settingsPage;
    
    /** Skeuomorphic */
    viator_gui::FilmStripKnob _inputDial;
    viator_gui::FilmStripKnob _outputDial;
    viator_gui::Label _inputLabel {"Input"};
    viator_gui::Label _outputLabel {"Output"};
    viator_gui::ToggleButton _skeuPhaseToggle;
    void activateSkeuComps(bool shouldBeOn);
    void updateFlatColors();
    
    /** Flat */
    viator_gui::Dial _flatInputDial;
    viator_gui::Dial _flatOutputDial;
    viator_gui::PushButton _flatPhaseToggle;
    void activateFlatComps(bool shouldBeOn);
    
    void updateSliderColors(viator_gui::Dial& slider);
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (IOModule)
};
