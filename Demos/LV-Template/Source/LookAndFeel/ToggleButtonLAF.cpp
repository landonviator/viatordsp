/*
  ==============================================================================

    ToggleButtonLAF.cpp
    Created: 22 May 2022 2:44:51pm
    Author:  Landon Viator

  ==============================================================================
*/

#include "ToggleButtonLAF.h"

ToggleButtonLAF::ToggleButtonLAF()
{
    
}

void ToggleButtonLAF::drawButtonBackground (juce::Graphics& g,
                                              juce::Button& button,
                                           const juce::Colour& backgroundColour,
                                           bool shouldDrawButtonAsHighlighted,
                                           bool shouldDrawButtonAsDown)
{
    button.setClickingTogglesState(true);
    
    auto cornerSize = 6.0f;
    auto bounds = button.getLocalBounds().toFloat().reduced (0.5f, 0.5f);
    
    auto baseColour = backgroundColour.withMultipliedSaturation (button.hasKeyboardFocus (true) ? 1.3f : 0.9f).withMultipliedAlpha (button.isEnabled() ? 1.0f : 0.5f);
    
    if (shouldDrawButtonAsDown || shouldDrawButtonAsHighlighted)
        baseColour = baseColour.contrasting (shouldDrawButtonAsDown ? 0.2f : 0.05f);
    
    g.setColour (baseColour);
    
    g.fillRoundedRectangle (bounds, cornerSize);
    
    g.setColour (button.findColour (juce::ComboBox::outlineColourId));
    g.drawRoundedRectangle (bounds, cornerSize, 4.0f);
    
    //Tick
    auto tickX = bounds.getWidth() * 0.255;
    auto tickY = bounds.getHeight() * 0.14f;

    drawTickBox (g, button, tickX, tickY,
                 bounds.getWidth() * 0.5, bounds.getHeight() * 0.75,
                 button.getToggleState(),
                 button.isEnabled(),
                 shouldDrawButtonAsHighlighted,
                 shouldDrawButtonAsDown);
}

void ToggleButtonLAF::drawTickBox (juce::Graphics& g, juce::Component& component,
                                   float x, float y, float w, float h,
                                   const bool ticked,
                                   const bool isEnabled,
                                   const bool shouldDrawButtonAsHighlighted,
                                   const bool shouldDrawButtonAsDown)
{
    juce::ignoreUnused (isEnabled, shouldDrawButtonAsHighlighted, shouldDrawButtonAsDown);

    juce::Rectangle<float> tickBounds (x, y, w, h);

    g.setColour (component.findColour (juce::ToggleButton::tickDisabledColourId));

    if (ticked)
    {
        g.setColour (component.findColour (juce::ToggleButton::tickColourId));
        auto tick = getTickShape (0.75f);
        g.fillPath (tick, tick.getTransformToScaleToFit (tickBounds.reduced (4, 5).toFloat(), false));
    }
}
