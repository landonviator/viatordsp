/*
  ==============================================================================

    Dial.h
    Created: 20 Jul 2021 9:43:18pm
    Author:  landon viator

  ==============================================================================
*/

#pragma once
#include "../Widgets/StyleSheet.h"

namespace viator_gui
{
class Dial  : public juce::Slider
{
public:
    
    Dial
    (   juce::String suffix,
        double rangeStart,
        double rangeEnd,
        double intervalValue,
        double returnValue
    )
    {
        initShadows();
        initProps(suffix, rangeStart, rangeEnd, intervalValue, returnValue);
    }
    
    ~Dial() override
    {
        setLookAndFeel(nullptr);
    }

    enum class DialStyle
    {
        kHardDial,
        kFullDial,
        kAlphaDial,
        kAbleDial
    };
    
    void setDialStyle(DialStyle dialStyle);
    
    void forceShadow();

private:
    
    /** Methods */
    void mouseEnter (const juce::MouseEvent& event) override;
    void mouseExit (const juce::MouseEvent& event) override;
    
    void initProps(juce::String suffix,
                   double rangeStart,
                   double rangeEnd,
                   double intervalValue,
                   double returnValue);
    
    /** Fader shadow */
    void initShadows();
    
    /** Slider */
    Slider dial;
    juce::HardDialLAF hardDial;
    juce::FullDialLAF fullDial;
    juce::AlphaDialLAF alphaDial;
    juce::CustomAbleDialLAF ableDial {false};
    
    /** Shadow */
    juce::DropShadow shadowProperties;
    juce::DropShadowEffect dialShadow;
    
}; // class
}// namespace viator+gui
