/*
  ==============================================================================

    LV_Dial.h
    Created: 20 Jul 2021 9:43:18pm
    Author:  landon viator

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>
#include "../Widgets/StyleSheet.h"

namespace juce
{

class LV_Dial  : public Slider
{
public:
    LV_Dial(         String suffix,
                     double rangeStart,
                     double rangeEnd,
                     double intervalValue,
                     double returnValue)
    {
        initShadows();
        initProps(suffix, rangeStart, rangeEnd, intervalValue, returnValue);
    }
    
    ~LV_Dial() override
    {
        setLookAndFeel(nullptr);
    }

    enum class DialStyle
    {
        kHardDial,
        kAlphaDial,
        kAbleDial
    };
    
    void setDialStyle(DialStyle dialStyle)
    {
        switch (dialStyle)
        {
            case DialStyle::kHardDial:
            {
                setLookAndFeel(&hardDial);
                break;
            }
                
            case DialStyle::kAlphaDial:
            {
                setLookAndFeel(&alphaDial);
                break;
            }
                
            case DialStyle::kAbleDial:
            {
                setLookAndFeel(&ableDial);
                break;
            }
        }
    }
    
    void forceShadow()
    {
        setComponentEffect(&dialShadow);
    }

private:
    
    void mouseEnter (const MouseEvent& event) override
    {
        setColour(juce::Slider::ColourIds::thumbColourId, findColour(juce::Slider::ColourIds::thumbColourId).withMultipliedLightness(1.25));
        setComponentEffect(&dialShadow);
    }
    
    void mouseExit (const MouseEvent& event) override
    {
        setColour(juce::Slider::ColourIds::thumbColourId, findColour(juce::Slider::ColourIds::thumbColourId).withMultipliedLightness(0.8f));
        setComponentEffect(&dialShadow);
    }
    
    /** Slider ================================================================*/
    Slider dial;
    LV_HardDialLAF hardDial;
    LV_AlphaDialLAF alphaDial;
    LV_CustomAbleDialLAF ableDial {false};
    
    /** Methods ================================================================*/
    void initProps(juce::String suffix,
                   double rangeStart,
                   double rangeEnd,
                   double intervalValue,
                   double returnValue)
    {
        setSliderStyle(juce::Slider::SliderStyle::RotaryVerticalDrag);
        setTextBoxStyle(juce::Slider::TextBoxBelow, false, 96, 32);
        setColour(juce::Slider::ColourIds::rotarySliderFillColourId, findColour(Slider::ColourIds::thumbColourId));
        setColour(juce::Slider::ColourIds::rotarySliderOutlineColourId, juce::Colours::black.brighter(0.1).withAlpha(0.8f));
        setColour(juce::Slider::ColourIds::trackColourId, juce::Colours::whitesmoke.darker(1.75f).withAlpha(0.7f));
        setColour(juce::Slider::ColourIds::textBoxOutlineColourId, juce::Colours::black.withAlpha(0.0f));
        setColour(juce::Slider::ColourIds::textBoxTextColourId, juce::Colours::whitesmoke.withAlpha(0.36f));
        setColour(juce::Slider::ColourIds::thumbColourId, juce::Colour::fromFloatRGBA(0.392f, 0.584f, 0.929f, 1.0f).darker(1.0f));
        setRange(rangeStart, rangeEnd, intervalValue);
        setDoubleClickReturnValue(true, returnValue);
        setTextValueSuffix(suffix);
        setLookAndFeel(&hardDial);
        setComponentEffect(&dialShadow);
    }
    
    /** Fader shadow ===========================================================*/
    void initShadows()
    {
        shadowProperties.radius = 24;
        shadowProperties.offset = juce::Point<int> (-1, 4);
        shadowProperties.colour = juce::Colours::black.withAlpha(0.5f);
        dialShadow.setShadowProperties (shadowProperties);
    }
    
    juce::DropShadow shadowProperties;
    juce::DropShadowEffect dialShadow;
    
};
}
