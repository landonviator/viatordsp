#include "BorderLAF.h"

namespace viator_gui
{

CustomBorder::CustomBorder()
{
}

void CustomBorder::drawGroupComponentOutline (juce::Graphics& g, int width, int height,
                                                const juce::String& text, const juce::Justification& position,
                                              juce::GroupComponent& group)
{
    const float textH = 15.0f;
    const float indent = 3.0f;
    const float textEdgeGap = 4.0f;
    auto cs = 5.0f;

    float fontSize;
    
    if (group.getWidth() > group.getHeight())
    {
        fontSize = group.getWidth() * 0.02f;
    }
    
    else
    {
        fontSize = group.getHeight() * 0.024f;
    }
    
    juce::Font f (juce::Font("Helvetica", fontSize, juce::Font::FontStyleFlags::bold));

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

    g.setGradientFill(juce::ColourGradient::vertical(juce::Colour::fromRGB(150, 96, 90), group.getHeight(), juce::Colour::fromRGB(130, 60, 130), group.getHeight() * 0.5));
//    g.setColour (group.findColour (juce::GroupComponent::outlineColourId)
//                    .withMultipliedAlpha (alpha));

    float strokeSize;
    if (group.getWidth() > group.getHeight())
    {
        strokeSize = group.getWidth() * 0.0025f;
    }
    
    else
    {
        strokeSize = group.getHeight() * 0.0025f;
    }
    
    g.strokePath (p, juce::PathStrokeType (strokeSize));

    g.setColour (group.findColour (juce::GroupComponent::textColourId)
                    .withMultipliedAlpha (alpha));
    g.setFont (f);
    g.drawText (text,
                juce::roundToInt (x + textX), 0,
                juce::roundToInt (textW),
                juce::roundToInt (textH),
                juce::Justification::centredTop, true);
}

}
