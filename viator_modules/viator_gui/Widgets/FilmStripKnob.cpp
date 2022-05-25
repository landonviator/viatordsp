#include "FilmStripKnob.h"

viator_gui::FilmStripKnob::FilmStripKnob(const int knobSize, const juce::String labelSuffix, const juce::String labelText)
: _knobSize(knobSize)
{
    setSliderStyle(juce::Slider::SliderStyle::RotaryVerticalDrag);
    
    switch (_knobSize)
    {
        case 0:
        {
            filmStrip = juce::ImageCache::getFromMemory(BinaryData::knob_small_png, BinaryData::knob_small_pngSize);
            frameHeight = filmStrip.getHeight() / 129;
            break;
        }
            
        case 1:
        {
            filmStrip = juce::ImageCache::getFromMemory(BinaryData::knob_middle_png, BinaryData::knob_middle_pngSize);
            frameHeight = filmStrip.getHeight() / 129;
            break;
        }
            
        case 2:
        {
            filmStrip = juce::ImageCache::getFromMemory(BinaryData::knob_big_png, BinaryData::knob_big_pngSize);
            frameHeight = filmStrip.getHeight() / 257;
            break;
        }
    }
    
    frameWidth = filmStrip.getWidth();
    
    /** Text Box Label*/
    addAndMakeVisible(knobLabel);
    knobLabel.setText(juce::String (getValue(), 2)  + labelSuffix, juce::dontSendNotification);
    knobLabel.setJustificationType(juce::Justification::centred);
    onValueChange = [this, labelSuffix]()
    {
        knobLabel.setText(juce::String (getValue(), 2) + labelSuffix, juce::dontSendNotification);
    };
    
    /** Title Label*/
    addAndMakeVisible(knobTitle);
    knobTitle.setText(labelText, juce::dontSendNotification);
    knobTitle.setColour(0x1000280, juce::Colour::fromFloatRGBA(0, 0, 0, 0));
    knobTitle.setColour(0x1000282, juce::Colour::fromFloatRGBA(0, 0, 0, 0));
    knobTitle.setColour(juce::Label::ColourIds::textColourId, juce::Colours::whitesmoke.darker(1.0f));
    knobTitle.setJustificationType(juce::Justification::centred);
    knobTitle.attachToComponent(this, false);
}

void viator_gui::FilmStripKnob::paint(juce::Graphics &g)
{
    const float sliderPos = (float) valueToProportionOfLength(getValue());

    int value;
    
    switch (_knobSize)
    {
        case 0:
        {
            value = sliderPos * (129 - 1);
            g.drawImage(filmStrip, 0, 0, getWidth(), getHeight() * 0.9, 0, value * frameHeight, frameWidth, frameHeight);
            auto background = juce::ImageCache::getFromMemory(BinaryData::scale_knob_small__png, BinaryData::scale_knob_small__pngSize);
            g.drawImageWithin(background, getWidth() * 0.17, getHeight() * 0.05, getWidth() / 1.5, getHeight() / 1.5, juce::RectanglePlacement::centred);
            break;
        }
            
        case 1:
        {
            value = sliderPos * (129 - 1);
            g.drawImage(filmStrip, 0, 0, getWidth(), getHeight(), 0, value * frameHeight, frameWidth, frameHeight);
            auto background = juce::ImageCache::getFromMemory(BinaryData::scale_knob_middle_png, BinaryData::scale_knob_middle_pngSize);
            g.drawImageWithin(background, getWidth() * 0.17, getHeight() * 0.125, getWidth() / 1.5, getHeight() / 1.5, juce::RectanglePlacement::centred);
            break;
        }
            
        case 2:
        {
            auto size = 1.07;
            auto x = 0.03;
            auto y = -0.025;
            
            value = sliderPos * (257 - 1);
            g.drawImage(filmStrip, 0, 0, getWidth(), getHeight(), 0, value * frameHeight, frameWidth, frameHeight);
            auto background = juce::ImageCache::getFromMemory(BinaryData::scale_knob_big_png, BinaryData::scale_knob_big_pngSize);
            g.drawImageWithin(background,
                              getWidth() * x,
                              getHeight() * y,
                              getWidth() / size,
                              getHeight() / size,
                              juce::RectanglePlacement::centred);
            break;
        }
    }
}

void viator_gui::FilmStripKnob::resized()
{
    if (_knobSize == 2)
    {
        knobLabel.setColour(juce::Label::ColourIds::backgroundColourId, juce::Colours::whitesmoke.withAlpha(0.25f));
        knobLabel.setBounds(getLocalBounds().reduced(0, getHeight() * JUCE_LIVE_CONSTANT(0.5f)).withY(
                                                                                                      getHeight() * JUCE_LIVE_CONSTANT(0.5f)));
        knobLabel.setFont(getWidth() * 0.1);
        knobTitle.setFont(juce::Font ("Helvetica", getWidth() * 0.1, juce::Font::FontStyleFlags::bold));
    }
    
    else
    {
        knobLabel.setBounds(getLocalBounds().reduced(0, getHeight() * 0.35).withY(getHeight() * 0.7));
        knobLabel.setFont(getWidth() * 0.12);
        knobTitle.setFont(juce::Font ("Helvetica", getHeight() * 0.12, juce::Font::FontStyleFlags::bold));
    }
}
