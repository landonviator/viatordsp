/*
  ==============================================================================

    Buttons.cpp
    Created: 24 Jun 2022 8:54:30pm
    Author:  Landon Viator

  ==============================================================================
*/

#include "Buttons.h"

ButtonStyle::ButtonStyle()
{
    
}

void ButtonStyle::drawButtonBackground
(
    juce::Graphics &g,
    juce::Button &button,
    const juce::Colour &backgroundColour,
    bool shouldDrawButtonAsHighlighted,
    bool shouldDrawButtonAsDown
)
{
    
    const bool isOver = button.isMouseOver();
    const bool isDown = button.isMouseButtonDown();
    const auto thicc3 = 4.f;

    auto bounds = button.getLocalBounds().toFloat();

    const auto x = bounds.getX();
    const auto y = bounds.getY();
    const auto w = bounds.getWidth();
    const auto h = bounds.getHeight();
    const auto btm = y + h;
    const auto rght = x + w;

    const auto tickWidth = .2f;
    const auto rad = w * tickWidth;
    const auto angle0 = 0.f - 3.14 * 0.25;
    const auto angle1 = 3.14 * 0.5 + 3.14 * 0.25;
    
    if (button.isMouseOver())
    {
        g.setColour(button.findColour(juce::TextButton::ColourIds::buttonColourId).brighter(0.6f));
    }
    
    else
    {
        g.setColour(button.findColour(juce::TextButton::ColourIds::buttonColourId).brighter(0.2f));
    }
    
    if (button.getToggleState())
    {
        g.setColour(button.findColour(juce::TextButton::ColourIds::textColourOnId).brighter(1.0f));
    }
    
    {
        const auto centreX = x;
        const auto centreY = btm;

        juce::Path path;
        
        path.addCentredArc
        (
            centreX, centreY,
            rad, rad,
            0.f, angle0, angle1,
            true
        );

        g.strokePath(path, juce::PathStrokeType(4.0f));
        
    }

    {
        const auto centreX = rght;
        const auto centreY = y;
        juce::Path path;
        
        path.addCentredArc
        (
            centreX, centreY,
            rad, rad,
            3.14, angle0, angle1,
            true
        );

        g.strokePath(path, juce::PathStrokeType(4.0f));
        
    }

    {
        const auto padding = rad;

        const auto x0 = x + padding;
        const auto y0 = btm - padding;
        const auto x1 = rght - padding;
        const auto y1 = y + padding;

        g.drawLine(x0, y0, x1, y1, thicc3);
    }
}
