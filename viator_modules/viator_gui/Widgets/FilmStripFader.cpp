#include "FilmStripFader.h"

viator_gui::FilmStripFader::FilmStripFader(int newNumFrames, const bool isHorizontal_, const juce::String labelText)
:
numFrames(newNumFrames)
{
    numFrames = newNumFrames;
    isHorizontal = isHorizontal_;
    
    setTextBoxStyle(NoTextBox, 0, 0, 0);
    setSliderStyle(juce::Slider::SliderStyle::LinearHorizontal);
    filmStrip = juce::ImageCache::getFromMemory(BinaryData::slider_horizontal_png, BinaryData::slider_horizontal_pngSize);
    
    /** Title Label*/
    addAndMakeVisible(knobTitle);
    knobTitle.setText(labelText, juce::dontSendNotification);
    knobTitle.setColour(0x1000280, juce::Colour::fromFloatRGBA(0, 0, 0, 0));
    knobTitle.setColour(0x1000282, juce::Colour::fromFloatRGBA(0, 0, 0, 0));
    knobTitle.setColour(juce::Label::ColourIds::textColourId, juce::Colours::whitesmoke.darker(1.0f));
    knobTitle.setJustificationType(juce::Justification::centred);
    
    if(isHorizontal_)
    {
        frameHeight = static_cast<float>(filmStrip.getHeight());
        frameWidth = static_cast<float>(filmStrip.getWidth()) / static_cast<float>(newNumFrames);
    }
    
    else
    {
        frameHeight = static_cast<float>(filmStrip.getHeight()) / static_cast<float>(newNumFrames);
        frameWidth = static_cast<float>(filmStrip.getWidth());
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
    
    // Backgroun
    auto ratio = 0.22902f;
    auto scalar = 0.82f;
    auto scale = juce::ImageCache::getFromMemory(BinaryData::scale_Horizontal_slider_png, BinaryData::scale_Horizontal_slider_pngSize);
    g.drawImageWithin(scale, getWidth() * 0.09f, getHeight() * 0.25f, getWidth() * scalar, getWidth() * ratio * scalar, juce::RectanglePlacement::stretchToFit);
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
    juce::Slider::resized();
    
    knobTitle.setBounds(getLocalBounds().withY(getHeight() * -0.4f));
    knobTitle.setFont(juce::Font ("Helvetica", getWidth() * 0.08f, juce::Font::FontStyleFlags::bold));
}
