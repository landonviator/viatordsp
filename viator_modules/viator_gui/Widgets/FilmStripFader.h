#pragma once

namespace viator_gui
{
class FilmStripFader : public juce::Slider
{
public:
    
    FilmStripFader(int newNumFrames, const bool isHorizontal_);
    
    void paint(juce::Graphics& g) override;
    
    void resized() override;
    
    int getFrameWidth();
    int getFrameHeight();
    
    
private:
    std::size_t numFrames, sideLength;
    juce::Image filmStrip;
    int frameWidth, frameHeight;
    
    viator_gui::Label knobLabel {true, ""};
    juce::Label knobTitle {};
    
    bool isHorizontal = true;
};
}
