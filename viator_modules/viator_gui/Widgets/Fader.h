#pragma once
#include "../LAF/FaderLAF.h"

namespace viator_gui
{
class Fader  : public juce::Slider
{
public:
    Fader();
    ~Fader() override;

    void paint (juce::Graphics&) override;
    void resized() override;

private:
    
    // Shadow
    juce::DropShadow shadowProperties;
    juce::DropShadowEffect dialShadow;
    
    // LAF
    viator_gui::CustomFader _customFaderLAF;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Fader)
};
}
