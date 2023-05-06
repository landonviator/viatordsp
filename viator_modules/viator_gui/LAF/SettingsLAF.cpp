#include "TextButtonLAF.h"

namespace juce
{
    CustomTextButton::CustomTextButton()
    {
        
    }

    void CustomTextButton::drawButtonBackground (Graphics& g,
                                               Button& button,
                                               const Colour& backgroundColour,
                                               bool shouldDrawButtonAsHighlighted,
                                               bool shouldDrawButtonAsDown)
    {
        auto cornerSize = 6.0f;
        auto bounds = button.getLocalBounds().toFloat().reduced (0.5f, 0.5f);
        auto baseColour = backgroundColour.withMultipliedSaturation (button.hasKeyboardFocus (true) ? 1.3f : 0.9f)
                                          .withMultipliedAlpha (button.isEnabled() ? 1.0f : 0.5f);

        g.setColour (baseColour);
        g.fillRoundedRectangle (bounds, cornerSize);

        g.setColour (button.findColour (ComboBox::outlineColourId));
        g.drawRoundedRectangle (bounds, cornerSize, 1.0f);
        
        // Hover highlight
        if ((shouldDrawButtonAsDown || shouldDrawButtonAsHighlighted))
        {
            g.setColour (button.findColour (TextButton::textColourOnId).brighter(shouldDrawButtonAsDown ? 0.0f : 0.35f));
        }
        
        else
        {
            g.setColour (button.findColour (TextButton::textColourOnId));
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
