#pragma once
#include "../Widgets/StyleSheet.h"

namespace viator_gui
{
    class Border : public juce::GroupComponent
    {
    public:
        
        Border()
        {
            setColour(juce::GroupComponent::ColourIds::outlineColourId, juce::Colours::black.withAlpha(0.35f));
            setColour(juce::GroupComponent::ColourIds::textColourId, juce::Colours::whitesmoke.darker(1.0));
            setTextLabelPosition(juce::Justification::centred);
            setLookAndFeel(&customBorder);
        }
        
        ~Border()
        {
            setLookAndFeel(nullptr);
        }
        
    private:
        
        juce::CustomBorder customBorder;
    };
}
