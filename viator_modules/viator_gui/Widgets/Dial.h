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
    
    /** Create an instance like this:
     * viator_dsp::Dial myDial {" dB", 0.0, 10.0, 0.1, 0.0};
     * " dB" is the text in the dial's number textbox
     * 0.0 is the range start
     * 10.0 is the range end
     * 0.1 is the interval between each dial setting
     * 0.0 is the number the dial is reset to when double clicked
    */
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

    /** Set the dial style
     * e.g. myDial.setDialStyle(viator_gui::Dial::DialStyle::kHardDial);
    */
    enum class DialStyle
    {
        kHardDial,
        kFullDial,
        kAlphaDial,
        kAbleDial
    };
    
    void setDialStyle(DialStyle dialStyle);
    
    /** You need to call forceShadow() if you change a dial's color or style in any way, I'm not sure why but making this method fixed it
     * e.g. 
     * myDial.setColour(juce::Slider::ColourIds::thumbColourId, juce::Colours::aliceblue);
     * dial.setDialStyle(viator_gui::Dial::DialStyle::kFullDial);
     * myDial.forceShadow();
    */
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
}// namespace viator_gui