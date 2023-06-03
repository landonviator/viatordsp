#pragma once
#include "../LAF/DialLAF.h"
#include "Label.h"

namespace viator_gui
{
class Dial  : public juce::Component
{
public:
    
    Dial (const juce::String& sliderName);
    ~Dial() override;
    
    void paint (juce::Graphics&) override;
    void resized() override;
    
    void setDialTextBoxWidth(const float newWidth);
    void setDialColors(juce::Colour mainText,
                       juce::Colour widgetFill,
                       juce::Colour auxBG,
                       juce::Colour auxText);
    
    juce::Slider& getSlider()
    {
        return dial;
    }
    
    enum class ValueType
    {
        kInt,
        kFloat
    };
    
    void setDialValueType(viator_gui::CustomDial::ValueType newValueType);

private:
    viator_gui::CustomDial _customDial;
    juce::Slider dial;
    
private:
    
    
private:
    juce::Colour _mainBackgroundColor = juce::Colour::fromRGB(33, 37, 43);
    juce::Colour _mainTextColor = juce::Colour::fromRGB(161, 168, 181).darker(0.3f);
    juce::Colour _widgetFillColor = juce::Colour::fromRGB(161, 168, 181).darker(0.3f);
    juce::Colour _auxBackgroundColor = _mainBackgroundColor.darker(1.0);
    juce::Colour _auxTextColor = juce::Colour::fromRGB(74, 81, 98).darker(0.5);
    juce::Colour _blackBackgroundColor = juce::Colour::fromRGB(33, 35, 37);
    
}; // class
}// namespace viator_gui
