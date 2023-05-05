#include "FaderLAF.h"

namespace viator_gui
{
    CustomFader::CustomFader()
    {
        
    }

    void CustomFader::drawLinearSlider (juce::Graphics& g, int x, int y, int width, int height,
                                           float sliderPos,
                                           float minSliderPos,
                                           float maxSliderPos,
                                           const juce::Slider::SliderStyle style, juce::Slider& slider)
    {
        _sliderWidth = width;
        
        auto isThreeVal = (style == juce::Slider::SliderStyle::ThreeValueVertical || style == juce::Slider::SliderStyle::ThreeValueHorizontal);

        auto trackWidth = juce::jmin (6.0f, slider.isHorizontal() ? (float) height * 0.25f : (float) width * 0.25f);

        juce::Point<float> startPoint (slider.isHorizontal() ? (float) x : (float) x + (float) width * 0.5f,
                                 slider.isHorizontal() ? (float) y + (float) height * 0.5f : (float) (height + y));

        juce::Point<float> endPoint (slider.isHorizontal() ? (float) (width + x) : startPoint.x,
                               slider.isHorizontal() ? startPoint.y : (float) y);

        juce::Path backgroundTrack;
        backgroundTrack.startNewSubPath (startPoint);
        backgroundTrack.lineTo (endPoint);
        g.setColour (slider.findColour (juce::Slider::backgroundColourId));
        g.strokePath (backgroundTrack, { trackWidth, juce::PathStrokeType::curved, juce::PathStrokeType::rounded });

        juce::Path valueTrack;
        juce::Point<float> minPoint, maxPoint, thumbPoint;

        auto kx = slider.isHorizontal() ? sliderPos : ((float) x + (float) width * 0.5f);
        auto ky = slider.isHorizontal() ? ((float) y + (float) height * 0.5f) : sliderPos;

        minPoint = startPoint;
        maxPoint = { kx, ky };
        
        valueTrack.startNewSubPath (minPoint);
        valueTrack.lineTo (isThreeVal ? thumbPoint : maxPoint);
        g.setColour (slider.findColour (juce::Slider::trackColourId));
        g.strokePath (valueTrack, { trackWidth, juce::PathStrokeType::curved, juce::PathStrokeType::rounded });

        auto thumbWidth = width * 0.45f;
        
        // Create a path for the thumb
        juce::Path thumbPath;
        thumbPath.addRoundedRectangle (-thumbWidth * 0.5f, -thumbWidth * 0.25f, thumbWidth, thumbWidth * 0.35, 2.0f);

        // Calculate the bounds of the thumb
        auto thumbBounds = thumbPath.getBounds().toFloat();
        thumbBounds.setCentre (maxPoint);

        // Fill the thumb path with a solid color
        auto thumbColor = slider.findColour (juce::Slider::thumbColourId);
        g.setColour (thumbColor);
        g.fillPath (thumbPath, juce::AffineTransform::translation(maxPoint.x, maxPoint.y));

        // Apply a gradient fill to the thumb path with a small height offset
        g.setGradientFill(juce::ColourGradient::vertical(thumbColor,
                                                         thumbBounds.getY() - 6.0f,
                                                         thumbColor.darker(1.0),
                                                         thumbBounds.getBottom() + 1.0f));
        g.fillPath (thumbPath, juce::AffineTransform::translation(maxPoint.x, maxPoint.y));

    }

    void CustomFader::drawLabel (juce::Graphics& g, juce::Label& label)
    {
        g.fillAll (label.findColour (juce::Label::backgroundColourId));

        label.setEditable(true);
        
        if (! label.isBeingEdited())
        {
            auto alpha = label.isEnabled() ? 1.0f : 0.5f;
            const juce::Font font (juce::Font ("Helvetica", _sliderWidth * 0.1, juce::Font::FontStyleFlags::bold));

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
}
