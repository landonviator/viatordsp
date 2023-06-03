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
        const auto multiplier = 0.5;
        auto cornerSize = 6.0f;
        auto bounds = button.getLocalBounds().withSizeKeepingCentre(button.getWidth() * multiplier, button.getHeight() * multiplier).toFloat();

        // Hover highlight
        auto baseColour = backgroundColour.withMultipliedSaturation (button.hasKeyboardFocus (true) ? 1.3f : 0.9f)
            .withMultipliedAlpha (button.isEnabled() ? 1.0f : 0.5f);
        
        if (shouldDrawButtonAsDown || shouldDrawButtonAsHighlighted)
            baseColour = baseColour.contrasting (shouldDrawButtonAsDown ? 0.2f : 0.05f);
        
        g.setColour (baseColour);
        g.fillRoundedRectangle(button.getLocalBounds().toFloat(), cornerSize);
        
        g.setColour (button.findColour (juce::ComboBox::outlineColourId));
        g.drawRoundedRectangle(bounds, cornerSize, 1.0f);
        
        if (shouldDrawButtonAsDown || shouldDrawButtonAsHighlighted)
        {
            if (button.getToggleState())
                g.setColour(juce::Colour::fromRGB(187, 129, 212).brighter(1.0f));
            else
                g.setColour(button.findColour(juce::TextButton::textColourOnId).brighter(1.0f));
        }
        else
        {
            if (button.getToggleState())
                g.setColour(juce::Colour::fromRGB(187, 129, 212));
            else
                g.setColour(button.findColour(juce::TextButton::textColourOnId));
        }
        
        // Wrench
        auto thicc3 = juce::jlimit(1.0f, 4.0f, juce::jmap(static_cast<float>(button.getWidth()), 15.0f, 60.0f, 1.0f, 4.0f));
        
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

            g.strokePath(path, juce::PathStrokeType(thicc3));
            
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
