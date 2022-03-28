/*
  ==============================================================================

    Fader.h
    Created: 21 Jul 2021 12:58:40pm
    Author:  landon viator

  ==============================================================================
*/

/*
  ==============================================================================

    FaderComponent.h
    Created: 23 Oct 2021 2:38:27am
    Author:  Landon Viator
 
    In your main editor, make sure to call setColour first, then enableShadow, if not,
    the shadow won't show up.

  ==============================================================================
*/

#pragma once

#include "../Widgets/Label.h"
#include "../Widgets/StyleSheet.h"

//==============================================================================
/*
*/
namespace viator_gui
{
    class Fader  : public juce::Slider
    {
    public:
        Fader
        (
            juce::String suffix,
            juce::String labelText,
            double rangeStart,
            double rangeEnd,
            double intervalValue,
            double returnValue
        )
        {
            initShadows();
            initProps(suffix, rangeStart, rangeEnd, intervalValue, returnValue);
            addAndMakeVisible(trimLabel);
            trimLabel.setText(labelText, juce::dontSendNotification);
            trimLabel.attachToComponent(this, false);
            trimLabel.setJustificationType(juce::Justification::centred);
        }
        
        ~Fader() override
        {
            setLookAndFeel(nullptr);
        }
        
        void forceShadow();
        
    private:
        
        /** Methods ===============================================================*/
        void mouseEnter (const juce::MouseEvent& event) override;
        void mouseExit (const juce::MouseEvent& event) override;
        
        void initProps
        (
            juce::String suffix,
            double rangeStart,
            double rangeEnd,
            double intervalValue,
            double returnValue
         );
        
        /** Fader shadow */
        void initShadows();
        
        /** Slider */
        juce::Slider slider;
        juce::FaderLAF customFader;
        
        /** Fader shadow */
        juce::DropShadow sliderShadowProperties;
        juce::DropShadowEffect sliderShadow;
        
        /** Label */
        Label trimLabel;
    };
}
