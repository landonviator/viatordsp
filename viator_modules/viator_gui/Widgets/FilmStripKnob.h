#pragma once

namespace viator_gui
{
class FilmStripKnob : public juce::Slider
{
public:
    
    FilmStripKnob(const int knobSize, const juce::String labelSuffix, const juce::String labelText, double rangeMin, double rangeMax);
    
    void paint(juce::Graphics& g) override;
    
    void resized() override;
    
    void updateLabelColor(juce::Colour newColor);
    
    void setLabelAsInt(bool isLabelInt);
    
private:
    const int _knobSize = 0;
    juce::Image filmStrip;
    int frameWidth, frameHeight;
    
    viator_gui::Label knobLabel {""};
    juce::Label knobTitle {};
    
    bool m_labelIsInt = true;
};
}
