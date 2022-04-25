#include "FilmStripKnob.h"

viator_gui::FilmStripKnob::FilmStripKnob(const int numFrames, const bool isThisKnobSmall, const juce::String labelText)
:
numFrames_(numFrames),
isKnobSmall(isThisKnobSmall)
{
    setSliderStyle(juce::Slider::SliderStyle::RotaryVerticalDrag);
    
    if (isKnobSmall)
    {
        filmStrip = juce::ImageCache::getFromMemory(BinaryData::knob_small_png, BinaryData::knob_small_pngSize);
    }
    
    else
    {
        filmStrip = juce::ImageCache::getFromMemory(BinaryData::knob_middle_png, BinaryData::knob_middle_pngSize);
    }
    
    frameHeight = filmStrip.getHeight() / numFrames_;
    frameWidth = filmStrip.getWidth();
    
    addAndMakeVisible(knobLabel);
    knobLabel.setText(std::to_string(std::ceil(getValue() * 100.0) / 100.0), juce::dontSendNotification);
    knobLabel.setJustificationType(juce::Justification::centred);
    knobLabel.setColour(juce::Label::ColourIds::backgroundColourId, juce::Colours::black.withAlpha(0.5f));
    onValueChange = [this]()
    {
        knobLabel.setText(std::to_string(std::ceil(getValue() * 100.0) / 100.0), juce::dontSendNotification);
    };
}

void viator_gui::FilmStripKnob::paint(juce::Graphics &g)
{
    const float sliderPos = (float) valueToProportionOfLength(getValue());

    int value = sliderPos * (numFrames_ - 1);
    
    if (isKnobSmall)
    {
        g.drawImage(filmStrip, 0, 0, getWidth(), getHeight() * 0.9, 0, value * frameHeight, frameWidth, frameHeight);
        
        auto background = juce::ImageCache::getFromMemory(BinaryData::scale_knob_small__png, BinaryData::scale_knob_small__pngSize);
        g.drawImageWithin(background, getWidth() * 0.17, getHeight() * 0.05, getWidth() / 1.5, getHeight() / 1.5, juce::RectanglePlacement::centred);
    }
    
    else
    {
        g.drawImage(filmStrip, 0, 0, getWidth(), getHeight(), 0, value * frameHeight, frameWidth, frameHeight);
        
        auto background = juce::ImageCache::getFromMemory(BinaryData::scale_knob_middle_png, BinaryData::scale_knob_middle_pngSize);
        g.drawImageWithin(background, getWidth() * 0.17, getHeight() * 0.125, getWidth() / 1.5, getHeight() / 1.5, juce::RectanglePlacement::centred);
    }
}

void viator_gui::FilmStripKnob::resized()
{
    knobLabel.setBounds(getLocalBounds().reduced(0, getHeight() * 0.35).withY(getHeight() * 0.7));
    knobLabel.setFont(getWidth() * 0.12);
}
