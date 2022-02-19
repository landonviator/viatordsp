#include "LV_NumberBox.h"

void viator_gui::LV_NumberBox::mouseEnter (const juce::MouseEvent& event)
{
    setColour(juce::Slider::ColourIds::textBoxTextColourId, findColour(juce::Slider::ColourIds::textBoxTextColourId).withAlpha(1.0f));
}

void viator_gui::LV_NumberBox::mouseExit (const juce::MouseEvent& event)
{
    setColour(juce::Slider::ColourIds::textBoxTextColourId, findColour(juce::Slider::ColourIds::textBoxTextColourId).withAlpha(0.5f));
}
