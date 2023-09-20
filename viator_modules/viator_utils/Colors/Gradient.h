#pragma once

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
                                          RectShape shape,
                                          double contrast)
    {
        juce::Point<float> center = rect.getCentre().toFloat();
        juce::ColourGradient gradient(gradientColor.brighter(contrast),
                                      center.x,
                                      center.y,
                                      gradientColor.darker(contrast),
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
