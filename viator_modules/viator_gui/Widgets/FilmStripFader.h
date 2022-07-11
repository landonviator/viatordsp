#pragma once

namespace viator_gui
{
class FilmStripFader : public juce::Slider
{
public:
    
    FilmStripFader(int newNumFrames, const bool isHorizontal_, const juce::String labelText);
    void paint(juce::Graphics& g) override;
    void resized() override;
    int getFrameWidth();
    int getFrameHeight();
    void updateLabelColor(juce::Colour newColor);
    
private:
    std::size_t numFrames, sideLength;
    juce::Image filmStrip;
    float frameWidth, frameHeight;
    viator_gui::Label knobLabel {""};
    juce::Label knobTitle {};
    bool isHorizontal = true;
    juce::Colour accentColor = juce::Colours::whitesmoke;
};
}
