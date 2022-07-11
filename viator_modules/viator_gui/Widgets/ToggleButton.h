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
    void setWidth(float newWidth);
    void updateLabelColor(juce::Colour newColor);
    
private:
    
    viator_gui::Label label {""};
    juce::Colour accentColor = juce::Colours::whitesmoke;
};
}


