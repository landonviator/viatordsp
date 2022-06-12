/*
  ==============================================================================

    FullDial.cpp
    Created: 11 Jun 2022 1:41:56pm
    Author:  Landon Viator

  ==============================================================================
*/

#include "FullDial.h"
void FullDialLAF::drawRotarySlider
(
    juce::Graphics &g,
    int x,
    int y,
    int width,
    int height,
    float sliderPos,
    float rotaryStartAngle,
    float rotaryEndAngle,
    juce::Slider &slider
)
{
    /** Define color variables for customization. */
    const auto outlineColor  = slider.findColour (juce::Slider::rotarySliderOutlineColourId);
    const auto fillColor     = slider.findColour(juce::Slider::rotarySliderFillColourId);
    const auto mainColor     = slider.findColour(juce::Slider::thumbColourId).withAlpha(0.5f);
    const auto brighterColor = slider.findColour(juce::Slider::thumbColourId).withAlpha(0.6f).brighter(0.2);
    const auto trackColor    = slider.findColour(juce::Slider::ColourIds::trackColourId);
    const auto dialOutlineColor = slider.findColour (juce::Slider::backgroundColourId);

    auto dialBounds = juce::Rectangle<int> (x, y, width, height).toFloat();
    auto centre = dialBounds.getCentre();
    auto fullRadius = juce::jmin (dialBounds.getWidth() / 1.95f, dialBounds.getHeight() / 1.95f);
    
    sliderWidth = width;
    
    /** Dot color*/
    g.setColour (trackColor);
    centre = dialBounds.getCentre();

    /** Draw dots */
    /** How many dots to draw, works well as num dial intervals + 1 for small ranges, e.g. [0 - 10]*/
    for (int i = 0; i < 11; ++i)
    {
        auto dotSize = width * 0.025;
        
        /** IF you change the number of dots, do i / (num dots - 1) */
        const auto angle = juce::jmap (i / 10.0f, rotaryStartAngle, rotaryEndAngle);
        
        /** Dot distance from slider center */
        const auto point = centre.getPointOnCircumference (fullRadius - width * 0.06f, angle);
            
        /** Dot thickness*/
        g.fillEllipse (point.getX() - 3, point.getY() - 3, dotSize, dotSize);
    }
        
    fullRadius -= 10.0f;

    auto toAngle = rotaryStartAngle + sliderPos * (rotaryEndAngle - rotaryStartAngle);
    
    /** Track thickness*/
    float lineWidthMultiplier = width * 0.035;
    auto lineWidth = juce::jmin (lineWidthMultiplier, fullRadius * 0.5f);
    auto arcRadius  = fullRadius - lineWidth * 2.25;

    juce::Path backgroundArc;
    backgroundArc.addCentredArc
    (
        dialBounds.getCentreX(),
        dialBounds.getCentreY(),
        arcRadius,
        arcRadius,
        0.0f,
        rotaryStartAngle,
        rotaryEndAngle,
        true
     );

    /** Dial fill track color*/
    g.setColour (outlineColor);
    g.strokePath (backgroundArc, juce::PathStrokeType (lineWidth, juce::PathStrokeType::curved, juce::PathStrokeType::rounded));

    auto dialRadius = std:: max (fullRadius - 4.0f * lineWidth, 10.0f);
    {
        juce::Graphics::ScopedSaveState saved (g);
        if (slider.isEnabled())
        {
            juce::ColourGradient fillGradient
            (
                brighterColor,
                centre.getX() + lineWidth * 0.9f,
                centre.getY() - lineWidth * 4.0f,
                mainColor,
                centre.getX() + dialRadius,
                centre.getY() + dialRadius,
                true
            );
            
            /** Dial center color gradient*/
            g.setGradientFill (fillGradient);
        }
        
        g.fillEllipse (centre.getX() - dialRadius, centre.getY() - dialRadius, dialRadius * 2.0f, dialRadius * 2.0f);
    }
    
    /** Dial outline color*/
    g.setColour (dialOutlineColor);
    
    auto scale = 2.0f;
    
    /** Dial outline thickness*/
    g.drawEllipse (centre.getX() - dialRadius, centre.getY() - dialRadius, dialRadius * scale, dialRadius * scale, 4.5f);
            
    /** Fill Math*/
    juce::Path dialValueTrack;
    dialValueTrack.addCentredArc
    (
        dialBounds.getCentreX(),
        dialBounds.getCentreY(),
        arcRadius,
        arcRadius,
        0.0f,
        rotaryStartAngle,
        toAngle,
        true
     );

    /** Value track fill color*/
    g.setColour (fillColor);
    g.strokePath (dialValueTrack, juce::PathStrokeType (lineWidth, juce::PathStrokeType::curved, juce::PathStrokeType::rounded));
    
    /** Dial tick color*/
    g.setColour (dialOutlineColor);
    juce::Path dialTick;
    dialTick.startNewSubPath (centre.getPointOnCircumference (dialRadius - lineWidth, toAngle));
    
    /** Dial tick length*/
    dialTick.lineTo (centre.getPointOnCircumference ((dialRadius - lineWidth) * 0.6f, toAngle));
    
    /** Dial tick thickness*/
    g.strokePath (dialTick, juce::PathStrokeType (lineWidth * 0.75, juce::PathStrokeType::curved, juce::PathStrokeType::rounded));
}

void FullDialLAF::drawLabel (juce::Graphics& g, juce::Label& label)
{
    g.fillAll (label.findColour (juce::Label::backgroundColourId));

    label.setEditable(true);
    
    if (! label.isBeingEdited())
    {
        auto alpha = label.isEnabled() ? 1.0f : 0.5f;
        const juce::Font font (juce::Font ("Helvetica", sliderWidth * 0.1, juce::Font::FontStyleFlags::bold));

        g.setColour (label.findColour (juce::Label::textColourId).withMultipliedAlpha (alpha));
        g.setFont (font);

        auto textArea = getLabelBorderSize (label).subtractedFrom (label.getLocalBounds());

        g.drawFittedText (label.getText(), textArea, label.getJustificationType(),
                          juce::jmax (1, (int) ((float) textArea.getHeight() / font.getHeight())),
                          label.getMinimumHorizontalScale());

        g.setColour (label.findColour (juce::Label::outlineColourId).withMultipliedAlpha (alpha));
    }
    
    else if (label.isEnabled())
    {
        g.setColour (label.findColour (juce::Label::outlineColourId));
    }

    g.drawRect (label.getLocalBounds());
}
