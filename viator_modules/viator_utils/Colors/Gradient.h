#pragma once
#include <JuceHeader.h>

namespace viator_utils
{
class Gradient
{
public:
    
    enum class RectShape
    {
        kRounded,
        kSquared
    };
    
    static inline void addVerticalGradient (juce::Graphics& g,
                                            juce::Colour& gradientColor,
                                            juce::Rectangle<int>& rect,
                                            RectShape shape)
    {
        g.setGradientFill(juce::ColourGradient::vertical(gradientColor,
                                                         rect.getY(),
                                                         gradientColor.darker(0.2),
                                                         rect.getBottom()));
        
        if (shape == RectShape::kRounded)
        {
            g.fillRoundedRectangle(rect.toFloat(), 6.0f);
        }
        
        else
        {
            g.fillRect(rect);
        }
    }
    
    static inline void addRadialGradient (juce::Graphics& g,
                                          juce::Colour& gradientColor,
                                          juce::Rectangle<int>& rect,
                                          RectShape shape)
    {
        juce::Point<float> center = rect.getCentre().toFloat();
        juce::ColourGradient gradient(gradientColor,
                                      center.x,
                                      center.y,
                                      gradientColor.darker(0.2),
                                      rect.getRight(),
                                      rect.getBottom(),
                                      true);
        g.setGradientFill(gradient);
        
        if (shape == RectShape::kRounded)
        {
            g.fillRoundedRectangle(rect.toFloat(), 6.0f);
        }
        
        else
        {
            g.fillRect(rect);
        }
    }
};
}
