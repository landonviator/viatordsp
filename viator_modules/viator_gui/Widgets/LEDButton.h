#pragma once

namespace viator_gui
{

class LEDButton : public juce::ImageButton
{
public:
    
    LEDButton();
    
    ~LEDButton() override
    {
    }
    
    void paint(juce::Graphics& g) override;
    
    void resized() override;
    
private:
    
};
}

