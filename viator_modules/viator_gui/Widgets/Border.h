#pragma once
#include "../Widgets/StyleSheet.h"

namespace viator_gui
{
    class Border : public juce::GroupComponent
    {
    public:
        
        Border()
        {
            setColour(juce::GroupComponent::ColourIds::outlineColourId, juce::Colours::whitesmoke.withAlpha(0.125f));
            setColour(juce::GroupComponent::ColourIds::textColourId, juce::Colours::whitesmoke.withAlpha(0.36f));
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
