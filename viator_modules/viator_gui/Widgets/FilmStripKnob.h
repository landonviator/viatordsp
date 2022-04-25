#pragma once

namespace viator_gui
{
class FilmStripKnob : public juce::Slider
{
public:
    
    FilmStripKnob(const int numFrames, const bool isThisKnobSmall);
    
    void paint(juce::Graphics& g) override;
    
    int getFrameWidth() const  { return frameWidth; }
    int getFrameHeight() const { return frameHeight; }
    
private:
    const int numFrames_;
    const bool isKnobSmall;
    juce::Image filmStrip;
    int frameWidth, frameHeight;
};
}
