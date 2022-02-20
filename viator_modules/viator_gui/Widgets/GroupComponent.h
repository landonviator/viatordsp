/*
  ==============================================================================

    GroupComponent.h
    Created: 21 Aug 2021 2:48:06pm
    Author:  Landon Viator

  ==============================================================================
*/

#pragma once
/*
  ==============================================================================

    Fader.h
    Created: 21 Jul 2021 12:58:40pm
    Author:  landon viator

  ==============================================================================
*/

#pragma once
#include "../Widgets/StyleSheet.h"

namespace viator_gui
{
    class GroupComponent : public juce::GroupComponent
    {
    public:
        
        GroupComponent()
        {
            setColour(juce::GroupComponent::ColourIds::outlineColourId, juce::Colours::whitesmoke.withAlpha(0.125f));
            setColour(juce::GroupComponent::ColourIds::textColourId, juce::Colours::whitesmoke.withAlpha(0.36f));
            setTextLabelPosition(juce::Justification::centred);
            setLookAndFeel(&customBorder);
        }
        
        ~GroupComponent()
        {
            setLookAndFeel(nullptr);
        }
        
    private:
        
        juce::CustomBorder customBorder;
    };
}
