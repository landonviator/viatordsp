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
    class Fader  : public juce::Slider, private juce::Timer
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
            startTimerHz(5);
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
        
        void paint(juce::Graphics& g) override
        {
            juce::Slider::paint(g);
            
            if (isSelectable)
            {
                g.setColour(juce::Colours::purple.withAlpha(0.25f));
                g.fillRect(getLocalBounds());
                
                if (isSelected)
                {
                    g.resetToDefaultState();
                    g.setColour(juce::Colours::whitesmoke.withAlpha(0.25f));
                    g.fillRect(getLocalBounds());
                }
                
                else
                {
                    g.resetToDefaultState();
                    g.setColour(juce::Colours::purple.withAlpha(0.25f));
                    g.fillRect(getLocalBounds());
                }
            }
        }
        
        void timerCallback() override
        {
            repaint();
        }
        
        void setSelectable(bool sliderISSelectable)
        {
            isSelectable = sliderISSelectable;
        }
        
        void mouseDoubleClick (const juce::MouseEvent &event) override
        {
            if (isSelectable)
            {
                if (isSelected)
                {
                    isSelected = false;
                    DBG("Slider deselected!");
                }
                
                else
                {
                    isSelected = true;
                    DBG("Slider selected!");
                }
            }
        }
        
        bool getIsSelected()
        {
            return isSelected;
        }
        
        void setSelected(bool newSelectState)
        {
            isSelected = newSelectState;
        }
        
        void setHasMidiMap(bool newHasMidiMap)
        {
            hasMidiMap = newHasMidiMap;
        }
        
        bool getHasMidiMap()
        {
            return hasMidiMap;
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
        
        /** Midi Map*/
        bool isSelectable = false;
        bool isSelected = false;
        bool hasMidiMap = false;
    };
}
