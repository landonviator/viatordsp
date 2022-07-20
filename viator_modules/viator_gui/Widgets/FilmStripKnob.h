#pragma once

namespace viator_gui
{
class FilmStripKnob : public juce::Slider
{
public:
    
    FilmStripKnob(int knobType, const juce::String labelSuffix, double rangeMin, double rangeMax);
    
    void paint(juce::Graphics& g) override;
    
    void resized() override;
    
    void updateLabelColor(juce::Colour newColor);
    
    void setLabelAsInt(bool isLabelInt);
    
private:
    int _knobType = 0;
    juce::Image filmStrip;
    int frameWidth, frameHeight;
    
    viator_gui::Label knobLabel {""};
};
}
