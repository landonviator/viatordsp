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
    Label(juce::String text);
    
    ~Label() override
    {
    }
    
    void paint(juce::Graphics& g) override;
    void resized() override;
    
private:
    
};
}
