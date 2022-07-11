#include "Toggle.h"


viator_gui::Toggle::Toggle()
{
    setClickingTogglesState(true);
    setColour(juce::ToggleButton::tickDisabledColourId, juce::Colours::dimgrey.withAlpha(0.5f));
    setColour(juce::ToggleButton::tickColourId, juce::Colours::springgreen.withAlpha(0.5f));
    setLookAndFeel(&powerToggle);
}

viator_gui::Toggle::~Toggle()
{
    setLookAndFeel(nullptr);
}

void viator_gui::Toggle::setToggleStyle(ToggleStyle newToggleStyle)
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

void viator_gui::Toggle::mouseEnter (const juce::MouseEvent& event)
{
    setColour(juce::ToggleButton::tickDisabledColourId, juce::Colours::dimgrey.withAlpha(0.8f));
    setColour(juce::ToggleButton::tickColourId, juce::Colours::springgreen.withAlpha(0.8f));
    
}

void viator_gui::Toggle::mouseExit (const juce::MouseEvent& event)
{
    setColour(juce::ToggleButton::tickDisabledColourId, juce::Colours::dimgrey.withAlpha(0.5f));
    setColour(juce::ToggleButton::tickColourId, juce::Colours::springgreen.withAlpha(0.5f));
}
