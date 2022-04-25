#pragma once

namespace viator_gui
{
class FilmStripFader : public juce::Slider
{
public:
    
    FilmStripFader(int newNumFrames, const bool isThisKnobSmall, const juce::String labelSuffix, const juce::String labelText);
    
    void paint(juce::Graphics& g) override;
    
    void resized() override;
    
    
private:
    std::size_t numFrames, sideLength;
    juce::Image filmStrip;
    
    viator_gui::Label knobLabel {true, ""};
    juce::Label knobTitle {};
};
}
