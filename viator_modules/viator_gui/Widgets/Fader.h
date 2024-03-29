#pragma once
#include "../LAF/FaderLAF.h"

namespace viator_gui
{
class Fader  : public juce::Slider
{
public:
    Fader();
    Fader(const int numFrames, const juce::Image& filmStrip);
    ~Fader() override;

    void paint (juce::Graphics&) override;
    void resized() override;
    
    void setViatorTooltip(const juce::String newTooltip) {_tooltip = newTooltip;};
    juce::String getViatorTooltip(){return _tooltip;};
    
    void setDialValueType(CustomFader::ValueType newValueType);

private:
    
    // Shadow
    juce::DropShadow shadowProperties;
    juce::DropShadowEffect dialShadow;
    
    // LAF
    viator_gui::CustomFader _customFaderLAF;
    
    // vars
    int _numFrames = 256;
    int frameWidth;
    int frameHeight;
    juce::Image _filmStrip;
    juce::String _tooltip {""};
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Fader)
};
}
