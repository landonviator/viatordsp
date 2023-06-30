#pragma once

namespace viator_gui
{

class Scope  : public juce::Component
{
public:
    Scope(int numChannels);
    ~Scope() override;

    void paint (juce::Graphics&) override;
    void resized() override;
    
    void fillBuffer(juce::AudioBuffer<float>& buffer);
    void setSamplesPerBlock(float samplesPerBlock);
    void setBufferSize(float samplesPerBlock);
    
private:
    
private:
    
    std::unique_ptr<juce::AudioVisualiserComponent> scopeModule;
    juce::Slider sampleDial;
    juce::Slider bufferDial;
    juce::Slider repaintDial;
    
    void setSliderProps(juce::Slider& dial);
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Scope)
}; // Scope

} // viator_gui
