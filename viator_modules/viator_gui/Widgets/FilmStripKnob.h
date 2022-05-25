#pragma once

namespace viator_gui
{
class FilmStripKnob : public juce::Slider
{
public:
    
    FilmStripKnob(const int knobSize, const juce::String labelSuffix, const juce::String labelText);
    
    void paint(juce::Graphics& g) override;
    
    void resized() override;
    
    void updateLabelColor(juce::Colour newColor);
    
private:
    const int _knobSize = 0;
    juce::Image filmStrip;
    int frameWidth, frameHeight;
    
    viator_gui::Label knobLabel {true, ""};
    juce::Label knobTitle {};
};
}
