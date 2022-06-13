/*
  ==============================================================================

    PanelLAF.cpp
    Created: 9 Jun 2022 11:21:43pm
    Author:  Landon Viator

  ==============================================================================
*/

#include "PanelLAF.h"
void CustomPanel::drawGroupComponentOutline
(
 juce::Graphics& g, int width, int height,
    const juce::String& text, const juce::Justification& position,
 juce::GroupComponent& group
)
{
    const float textH = 24.0f;
    const float indent = 3.0f;
    const float textEdgeGap = 4.0f;
    auto cs = 5.0f;

    juce::Font f (juce::Font (juce::Font ("Helvetica", 24.0f, juce::Font::FontStyleFlags::bold)));

    juce::Path p;
    auto x = indent;
    auto y = f.getAscent() - 3.0f;
    auto w = juce::jmax (0.0f, (float) width - x * 2.0f);
    auto h = juce::jmax (0.0f, (float) height - y  - indent);
    cs = juce::jmin (cs, w * 0.5f, h * 0.5f);
    auto cs2 = 2.0f * cs;

    auto textW = text.isEmpty() ? 0
                                : juce::jlimit (0.0f,
                                          juce::jmax (0.0f, w - cs2 - textEdgeGap * 2),
                                          (float) f.getStringWidth (text) + textEdgeGap * 2.0f);
    auto textX = cs + textEdgeGap;

    if (position.testFlags (juce::Justification::horizontallyCentred))
        textX = cs + (w - cs2 - textW) * 0.5f;
    else if (position.testFlags (juce::Justification::right))
        textX = w - cs - textW - textEdgeGap;
    
    /** Background Layer*/
    //g.setColour(juce::Colours::black.withAlpha(0.1f));
    //g.fillRect(x, y, w, h);

    p.startNewSubPath (x + textX + textW, y);
    p.lineTo (x + w - cs, y);

    p.addArc (x + w - cs2, y, cs2, cs2, 0, juce::MathConstants<float>::halfPi);
    p.lineTo (x + w, y + h - cs);

    p.addArc (x + w - cs2, y + h - cs2, cs2, cs2, juce::MathConstants<float>::halfPi, juce::MathConstants<float>::pi);
    p.lineTo (x + cs, y + h);

    p.addArc (x, y + h - cs2, cs2, cs2, juce::MathConstants<float>::pi, juce::MathConstants<float>::pi * 1.5f);
    p.lineTo (x, y + cs);

    p.addArc (x, y, cs2, cs2, juce::MathConstants<float>::pi * 1.5f, juce::MathConstants<float>::twoPi);
    p.lineTo (x + textX, y);

    auto alpha = group.isEnabled() ? 1.0f : 0.5f;

    g.setColour (group.findColour (juce::GroupComponent::outlineColourId)
                    .withMultipliedAlpha (alpha));

    g.strokePath (p, juce::PathStrokeType (1.0f));

    g.setColour (group.findColour (juce::GroupComponent::textColourId)
                    .withMultipliedAlpha (alpha));
    g.setFont (f);
    g.drawText (text,
                juce::roundToInt (x + textX), 6,
                juce::roundToInt (textW),
                juce::roundToInt (textH),
                juce::Justification::centred, true);
}

