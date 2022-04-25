#include "FilmStripFader.h"

viator_gui::FilmStripFader::FilmStripFader(int newNumFrames, const bool isThisKnobSmall, const juce::String labelSuffix, const juce::String labelText)
:
numFrames(newNumFrames)
{
    setSliderStyle(juce::Slider::SliderStyle::LinearVertical);
    
    
        filmStrip = juce::ImageCache::getFromMemory(BinaryData::slider_vertical_png, BinaryData::slider_vertical_pngSize);
    
//    frameHeight = filmStrip.getHeight() / numFrames_;
//    frameWidth = filmStrip.getWidth();
//
//    /** Text Box Label*/
//    addAndMakeVisible(knobLabel);
//    knobLabel.setText(juce::String (getValue(), 2)  + labelSuffix, juce::dontSendNotification);
//    knobLabel.setJustificationType(juce::Justification::centred);
//    onValueChange = [this, labelSuffix]()
//    {
//        knobLabel.setText(juce::String (getValue(), 2) + labelSuffix, juce::dontSendNotification);
//    };
//
//    /** Title Label*/
//    addAndMakeVisible(knobTitle);
//    knobTitle.setText(labelText, juce::dontSendNotification);
//    knobTitle.setColour(0x1000280, juce::Colour::fromFloatRGBA(0, 0, 0, 0));
//    knobTitle.setColour(0x1000282, juce::Colour::fromFloatRGBA(0, 0, 0, 0));
//    knobTitle.setColour(juce::Label::ColourIds::textColourId, juce::Colours::whitesmoke.darker(1.0f));
//    knobTitle.setJustificationType(juce::Justification::centred);
//    knobTitle.attachToComponent(this, false);
    
    sideLength = filmStrip.getWidth();
    numFrames = filmStrip.getHeight() / sideLength;
}

void viator_gui::FilmStripFader::paint(juce::Graphics &g)
{
    int imageNumber = static_cast<std::size_t>(0.5 + (getValue() - getMinimum()) / (getMaximum() - getMinimum()) * (numFrames - 1));
    g.drawImage(filmStrip, 0, 0, sideLength, sideLength, 0, imageNumber * sideLength, sideLength, sideLength);
        //auto background = juce::ImageCache::getFromMemory(BinaryData::scale_knob_middle_png, BinaryData::scale_knob_middle_pngSize);
        //g.drawImageWithin(background, getWidth() * 0.17, getHeight() * 0.125, getWidth() / 1.5, getHeight() / 1.5, juce::RectanglePlacement::centred);
    
}

void viator_gui::FilmStripFader::resized()
{
    knobLabel.setBounds(getLocalBounds().reduced(0, getHeight() * 0.35).withY(getHeight() * 0.7));
    knobLabel.setFont(getWidth() * 0.12);
    knobTitle.setFont(juce::Font ("Helvetica", getHeight() * 0.12, juce::Font::FontStyleFlags::bold));
}
