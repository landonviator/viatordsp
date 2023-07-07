#pragma once

namespace viator_gui
{

class VUMeter  : public juce::Component
{
public:
    
    VUMeter (const juce::String& sliderName, const juce::Image& filmStrip);
    ~VUMeter() override;
    
    void paint (juce::Graphics&) override;
    void resized() override;
    
    juce::Slider& getVUMeter(){return vuMeter;};
    
private:
    
    juce::Image _filmStrip;
    const int _numFrames = 129;
    int frameWidth;
    int frameHeight;
    juce::Slider vuMeter;
    
    void mouseDown(const juce::MouseEvent&) override {}
    void mouseDrag(const juce::MouseEvent&) override {}
    void mouseUp(const juce::MouseEvent&) override {}
    
}; // class
}// namespace viator_gui
