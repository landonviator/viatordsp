/*
  ==============================================================================

    LV_GroupComponent.h
    Created: 21 Aug 2021 2:48:06pm
    Author:  Landon Viator

  ==============================================================================
*/

#pragma once
/*
  ==============================================================================

    LV_Fader.h
    Created: 21 Jul 2021 12:58:40pm
    Author:  landon viator

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>
#include "../Widgets/StyleSheet.h"

namespace juce
{
    class LV_GroupComponent : public GroupComponent
    {
    public:
        
        LV_GroupComponent()
        {
            setColour(juce::GroupComponent::ColourIds::outlineColourId, juce::Colours::whitesmoke.withAlpha(0.125f));
            setColour(juce::GroupComponent::ColourIds::textColourId, juce::Colours::whitesmoke.withAlpha(0.36f));
            setTextLabelPosition(juce::Justification::centred);
            setLookAndFeel(&customBorder);
        }
        
        ~LV_GroupComponent()
        {
            setLookAndFeel(nullptr);
        }
        
    private:
        
        LV_CustomBorder customBorder;
    };
}
