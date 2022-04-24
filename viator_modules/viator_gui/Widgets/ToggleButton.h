#pragma once

namespace viator_gui
{

class ToggleButton : public juce::ImageButton
{
public:
    
    ToggleButton(bool isLargeButton, juce::String labelText);
    
    ~ToggleButton() override
    {
    }
    
    void paint(juce::Graphics& g) override;
    
    void resized() override;
    
private:
    
    viator_gui::Label label {true, ""};
    
};
}


