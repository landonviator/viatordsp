#include "LV_Toggle.h"


viator_gui::LV_Toggle::LV_Toggle()
{
    setClickingTogglesState(true);
    setColour(juce::ToggleButton::tickDisabledColourId, juce::Colours::dimgrey.withAlpha(0.5f));
    setColour(juce::ToggleButton::tickColourId, juce::Colours::springgreen.withAlpha(0.5f));
    setLookAndFeel(&powerToggle);
}

viator_gui::LV_Toggle::~LV_Toggle()
{
    setLookAndFeel(nullptr);
}

void viator_gui::LV_Toggle::setToggleStyle(ToggleStyle newToggleStyle)
{
    switch (newToggleStyle) {
        case ToggleStyle::kPower:
        {
            setLookAndFeel(&powerToggle);
            break;
        }

        case ToggleStyle::kPhase:
        {
            setLookAndFeel(&phaseToggle);
            break;
        }
    }
}

void viator_gui::LV_Toggle::mouseEnter (const juce::MouseEvent& event)
{
    setColour(juce::ToggleButton::tickDisabledColourId, juce::Colours::whitesmoke);
    setColour(juce::ToggleButton::tickColourId, juce::Colours::whitesmoke);
    
}

void viator_gui::LV_Toggle::mouseExit (const juce::MouseEvent& event)
{
    setColour(juce::ToggleButton::tickDisabledColourId, juce::Colours::dimgrey.withAlpha(0.5f));
    setColour(juce::ToggleButton::tickColourId, juce::Colours::springgreen.withAlpha(0.5f));
}
