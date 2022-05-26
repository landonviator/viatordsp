#include "MenuSliderLAF.h"

MenuSliderLAF::MenuSliderLAF()
{
    
}

void MenuSliderLAF::drawLinearSlider (juce::Graphics& g, int x, int y, int width, int height,
                                      float sliderPos,
                                      float minSliderPos,
                                      float maxSliderPos,
                                      const juce::Slider::SliderStyle style,
                                      juce::Slider& slider)
{
    auto trackWidth = slider.isHorizontal() ? (float) height * 0.25f : (float) width * 0.25f;

    juce::Point<float> startPoint (slider.isHorizontal() ? (float) x : (float) x + (float) width * 0.5f,
                                 slider.isHorizontal() ? (float) y + (float) height * 0.5f : (float) (height + y));

    juce::Point<float> endPoint (slider.isHorizontal() ? (float) (width + x) : startPoint.x,
                               slider.isHorizontal() ? startPoint.y : (float) y);

    auto trackColor = juce::Colour::fromRGB(54, 57, 63);
    
    juce::Path backgroundTrack;
    backgroundTrack.startNewSubPath (startPoint);
    backgroundTrack.lineTo (endPoint);
    g.setColour (trackColor);
    g.strokePath (backgroundTrack, { trackWidth, juce::PathStrokeType::curved, juce::PathStrokeType::rounded });

    juce::Path valueTrack;
    juce::Point<float> minPoint, maxPoint;

    auto kx = slider.isHorizontal() ? sliderPos : ((float) x + (float) width * 0.5f);
    auto ky = slider.isHorizontal() ? ((float) y + (float) height * 0.5f) : sliderPos;

    minPoint = startPoint;
    maxPoint = { kx, ky };

    auto thumbWidth = getSliderThumbRadius (slider) * 2.0f;

    valueTrack.startNewSubPath (minPoint);
    valueTrack.lineTo (maxPoint);
    g.setColour (trackColor);
    g.strokePath (valueTrack, { trackWidth, juce::PathStrokeType::curved, juce::PathStrokeType::rounded });

    //Thumb border
    g.setColour(juce::Colours::black.brighter(0.1f));
    
    auto thumbBounds = juce::Rectangle<float> (static_cast<float> (thumbWidth), static_cast<float> (thumbWidth)).withCentre (maxPoint);
    g.drawRoundedRectangle(thumbBounds, 8.0f, 2.0f);
    
    auto centre = thumbBounds.getCentre();
    float lineWidthMultiplier = thumbBounds.getWidth() * 0.035;
    auto lineWidth = juce::jmin (lineWidthMultiplier, thumbBounds.getWidth() * 0.5f);
    
    //Thumb
    juce::ColourGradient fillGradient
    (
        juce::Colour::fromFloatRGBA(0.392f, 0.584f, 0.929f, 1.0f).darker(0.6),
        centre.getX() + lineWidth * -2.0,
        centre.getY() - lineWidth * 1.7f,
        juce::Colour::fromFloatRGBA(0.392f, 0.584f, 0.929f, 1.0f).darker(1.0f),
        centre.getX() + thumbBounds.getWidth() * 0.5,
        centre.getY() + thumbBounds.getWidth() * 0.5,
        true
    );
    
    /** Dial center color gradient*/
    g.setGradientFill (fillGradient);
    //g.setColour (juce::Colour::fromFloatRGBA(0.392f, 0.584f, 0.929f, 1.0f).darker(1.0f));
    g.fillRoundedRectangle(juce::Rectangle<float> (static_cast<float> (thumbWidth), static_cast<float> (thumbWidth)).withCentre (maxPoint), 8.0f);
    
    slider.setColour(juce::Slider::ColourIds::textBoxOutlineColourId, juce::Colours::transparentBlack);
}
