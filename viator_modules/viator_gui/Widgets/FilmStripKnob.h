#pragma once

namespace viator_gui
{
class FilmStripKnob : public juce::Slider
{
public:
    
    FilmStripKnob(const int numFrames, const bool isThisKnobSmall, const juce::String labelText);
    
    void paint(juce::Graphics& g) override;
    
    void resized() override;
    
private:
    const int numFrames_;
    const bool isKnobSmall;
    juce::Image filmStrip;
    int frameWidth, frameHeight;
    viator_gui::Label knobLabel {true, ""};
};
}
