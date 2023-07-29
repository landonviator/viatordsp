#pragma once

namespace viator_gui
{

class VUMeter  : public juce::Component
{
public:
    
    VUMeter ();
    ~VUMeter() override;
    
    void paint (juce::Graphics&) override;
    void resized() override;
    
    juce::Slider& getVUMeter(){return vuMeter;};
    void setVUImages(const juce::Image& main, const juce::Image& grid, const juce::Image& bg);
    
private:
    
    juce::Image _mainVUImage;
    juce::Image _vuGridImage;
    juce::Image _vuBGImage;
    const int _numFrames = 129;
    int frameWidth;
    int frameHeight;
    juce::Slider vuMeter;
    
    void mouseDown(const juce::MouseEvent&) override {}
    void mouseDrag(const juce::MouseEvent&) override {}
    void mouseUp(const juce::MouseEvent&) override {}
    
}; // class
}// namespace viator_gui
