#pragma once
#include <JuceHeader.h>

class LabelLAF : public juce::LookAndFeel_V2
{
public:
    LabelLAF();
    
    void drawLabel (juce::Graphics& g, juce::Label& label) override;
};
