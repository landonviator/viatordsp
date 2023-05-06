#pragma once
#include "../LAF/DialLAF.h"
#include "Label.h"

namespace viator_gui
{
class Dial  : public juce::Slider
{
public:
    
    Dial ();
    ~Dial() override;
    
    void paint(juce::Graphics& g) override;
    void resized() override;

private:
    
private:
    
    Slider dial;
    
    juce::DropShadow shadowProperties;
    juce::DropShadowEffect dialShadow;
    
    viator_gui::CustomDial _customDial;
    
private:
    
}; // class
}// namespace viator_gui
