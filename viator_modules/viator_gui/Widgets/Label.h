/*
  ==============================================================================

    Label.h
    Created: 1 Aug 2021 1:17:17am
    Author:  landon viator

  ==============================================================================
*/

#pragma once

namespace viator_gui
{

class Label : public juce::Label
{
public:
    
    Label();
    Label(bool isTransparent, juce::String text);
    
    ~Label() override
    {
    }
    
    void paint(juce::Graphics& g) override;
    void resized() override;
    void updateLabelColor(juce::Colour newColor);
    
private:
    
    bool labelIsTransparent = false;
    bool autoResize = true;
};
}
