#include "FilmStripKnob.h"

viator_gui::FilmStripKnob::FilmStripKnob(int knobType, const juce::String labelSuffix, double rangeMin, double rangeMax)
: _knobType(knobType)
{
    setSliderStyle(juce::Slider::SliderStyle::RotaryVerticalDrag);
    setRange(rangeMin, rangeMax, 0.01);
    
    switch (_knobType)
    {
        case 0:
        {
            filmStrip = juce::ImageCache::getFromMemory(BinaryData::Knob_04_png, BinaryData::Knob_04_pngSize);
            frameHeight = filmStrip.getHeight() / 257;
            break;
        }
            
        case 1:
        {
            filmStrip = juce::ImageCache::getFromMemory(BinaryData::Knob_03_png, BinaryData::Knob_03_pngSize);
            frameHeight = filmStrip.getHeight() / 257;
            break;
        }
            
        case 2:
        {
            filmStrip = juce::ImageCache::getFromMemory(BinaryData::Knob_01_png, BinaryData::Knob_01_pngSize);
            frameHeight = filmStrip.getHeight() / 257;
            break;
        }
    }
    
    frameWidth = filmStrip.getWidth();
    
    /** Text Box Label*/
    addAndMakeVisible(knobLabel);
    knobLabel.setText(juce::String (getValue(), 2) + labelSuffix, juce::dontSendNotification);
    onValueChange = [this, labelSuffix]()
    {
        knobLabel.setText(juce::String (getValue(), 2) + labelSuffix, juce::dontSendNotification);
    };
}

void viator_gui::FilmStripKnob::paint(juce::Graphics &g)
{
    const float sliderPos = (float) valueToProportionOfLength(getValue());

    int value;
    
    value = sliderPos * (257 - 1);
    g.drawImage(filmStrip,
                getWidth() * 0.1,
                getHeight() * 0.08,
                getWidth() * 0.8,
                getHeight() * 0.8, 0, value * frameHeight, frameWidth, frameHeight);
}

void viator_gui::FilmStripKnob::resized()
{
    knobLabel.setBounds(0,
                        getHeight() * 0.8,
                        getWidth(),
                        getHeight() * 0.25f);
}

void viator_gui::FilmStripKnob::updateLabelColor(juce::Colour newColor)
{
    knobLabel.setColour(juce::Label::ColourIds::textColourId, newColor);
}

void viator_gui::FilmStripKnob::setLabelAsInt(bool isLabelInt)
{
}
