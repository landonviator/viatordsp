#pragma once

namespace viator_gui
{

class ToggleButton : public juce::ImageButton
{
public:
    
    ToggleButton(bool useLabel, juce::String labelText, bool isPhase);
    
    ~ToggleButton() override
    {
    }
    
    void paint(juce::Graphics& g) override;
    void resized() override;
    void setWidth(float newWidth);
    void updateLabelColor(juce::Colour newColor);
    
private:
    
    juce::Colour accentColor = juce::Colours::whitesmoke;
    
    bool _useLabel = false;
    bool _isPhase = false;
    juce::String _labelText;
};
}


