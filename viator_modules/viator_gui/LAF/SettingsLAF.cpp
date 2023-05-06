#include "TextButtonLAF.h"

namespace viator_gui
{
    SettingsButton::SettingsButton()
    {
        
    }

    void SettingsButton::drawButtonBackground (juce::Graphics& g,
                                               juce::Button& button,
                                               const juce::Colour& backgroundColour,
                                               bool shouldDrawButtonAsHighlighted,
                                               bool shouldDrawButtonAsDown)
    {
        auto bounds = button.getLocalBounds().toFloat().reduced (0.5f, 0.5f);

        // Hover highlight
        if ((shouldDrawButtonAsDown || shouldDrawButtonAsHighlighted))
        {
            g.setColour (button.findColour (juce::TextButton::textColourOnId).brighter(1.0f));
        }
        
        else
        {
            g.setColour (button.findColour (juce::TextButton::textColourOnId));
        }
        
        // Wrench
        const auto thicc3 = 4.0f;
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
    } // method
} // namespace
