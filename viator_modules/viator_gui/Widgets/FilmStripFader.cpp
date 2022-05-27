#include "FilmStripFader.h"

viator_gui::FilmStripFader::FilmStripFader(int newNumFrames, const bool isHorizontal_)
:
numFrames(newNumFrames)
{
    numFrames = newNumFrames;
    isHorizontal = isHorizontal_;
    
    setTextBoxStyle(NoTextBox, 0, 0, 0);
    setRange(0.0, 10.0, 0.01);
    setSliderStyle(juce::Slider::SliderStyle::LinearHorizontal);
    filmStrip = juce::ImageCache::getFromMemory(BinaryData::slider_horizontal_png, BinaryData::slider_horizontal_pngSize);
    
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
    if(isHorizontal_)
    {
        frameHeight = filmStrip.getHeight();
        frameWidth = filmStrip.getWidth() / newNumFrames;
    }
    
    else
    {
        frameHeight = filmStrip.getHeight() / newNumFrames;
        frameWidth = filmStrip.getWidth();
    }
}

void viator_gui::FilmStripFader::paint(juce::Graphics &g)
{
    int value = (getValue() - getMinimum()) / (getMaximum() - getMinimum()) * (numFrames - 1);
    
    if(isHorizontal)
    {
        g.drawImage(filmStrip, 0, 0, getWidth(), getHeight(),
                            value * frameWidth, 0, frameWidth, frameHeight);
    }
            
    else
    {
        g.drawImage(filmStrip, 0, 0, getWidth(), getHeight(),
                            0, value * frameHeight, frameWidth, frameHeight);
    }
}
            
int viator_gui::FilmStripFader::getFrameWidth()
{
    return filmStrip.isValid() ? frameWidth  : 100;
    
}

int viator_gui::FilmStripFader::getFrameHeight()
{
    return filmStrip.isValid() ? frameHeight : 24;
}
    

void viator_gui::FilmStripFader::resized()
{
    //knobLabel.setBounds(getLocalBounds().reduced(0, getHeight() * 0.35).withY(getHeight() * 0.7));
    //knobLabel.setFont(getWidth() * 0.12);
    //knobTitle.setFont(juce::Font ("Helvetica", getHeight() * 0.12, juce::Font::FontStyleFlags::bold));
}
