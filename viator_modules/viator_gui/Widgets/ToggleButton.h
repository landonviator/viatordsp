#pragma once

namespace viator_gui
{

class ToggleButton : public juce::ImageButton
{
public:
    
    ToggleButton(bool isLargeButton);
    
    ~ToggleButton() override
    {
    }
    
    void paint(juce::Graphics& g) override;
    
    void resized() override;
    
private:
    
};
}


