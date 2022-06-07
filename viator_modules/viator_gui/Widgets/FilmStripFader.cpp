#include "FilmStripFader.h"

viator_gui::FilmStripFader::FilmStripFader(int newNumFrames, const bool isHorizontal_, const juce::String labelText)
:
numFrames(newNumFrames)
{
    numFrames = newNumFrames;
    isHorizontal = isHorizontal_;
    
    /** Slider stuff*/
    setTextBoxStyle(NoTextBox, 0, 0, 0);
    setSliderStyle(juce::Slider::SliderStyle::LinearHorizontal);
    //filmStrip = juce::ImageCache::getFromMemory(BinaryData::slider_horizontal_png, BinaryData::slider_horizontal_pngSize);
    
    /** Title Label*/
    addAndMakeVisible(knobTitle);
    knobTitle.setText(labelText, juce::dontSendNotification);
    knobTitle.setColour(juce::Label::ColourIds::backgroundColourId, juce::Colours::transparentBlack);
    knobTitle.setColour(juce::Label::ColourIds::outlineColourId, juce::Colours::transparentBlack);
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
    // Backgroun
//    auto ratio = 0.22902f;
//    auto scalar = 0.82f;
//    auto scale = juce::ImageCache::getFromMemory(BinaryData::scale_Horizontal_slider_png, BinaryData::scale_Horizontal_slider_pngSize);
//    g.drawImageWithin(scale, getWidth() * 0.09f, getHeight() * 0.25f, getWidth() * scalar, getWidth() * ratio * scalar, juce::RectanglePlacement::stretchToFit);
//    
//    int value = (getValue() - getMinimum()) / (getMaximum() - getMinimum()) * (numFrames - 1);
//    
//    if(isHorizontal)
//    {
//        g.drawImage(filmStrip, 0, 0, getWidth(), getHeight(),
//                            value * frameWidth, 0, frameWidth, frameHeight);
//    }
//            
//    else
//    {
//        g.drawImage(filmStrip, 0, 0, getWidth(), getHeight(),
//                            0, value * frameHeight, frameWidth, frameHeight);
//    }
//    
//    //Number labels
//    g.setColour(accentColor);
//    g.setFont(juce::Font ("Helvetica", getWidth() * 0.05f, juce::Font::FontStyleFlags::bold));
//    auto size = getWidth() * 0.16f;
//    auto x1 = getWidth() * 0.017f;
//    auto y1 = getHeight() * -0.05f;
//    g.drawFittedText("0", x1, y1, size, size, juce::Justification::centred, 1);
//    auto x2 = getWidth() * 0.83f;
//    auto y2 = getHeight() * -0.05f;
//    g.drawFittedText("100", x2, y2, size, size, juce::Justification::centred, 1);
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
    
    auto size = getWidth() * 0.17f;
    knobTitle.setBounds(getLocalBounds().withSizeKeepingCentre(size, size).withY(getHeight() * -0.12f));
    knobTitle.setFont(juce::Font ("Helvetica", getWidth() * 0.08f, juce::Font::FontStyleFlags::bold));
}

void viator_gui::FilmStripFader::updateLabelColor(juce::Colour newColor)
{
    if (newColor == juce::Colours::black || newColor == juce::Colour::fromRGB(56, 72, 92))
    {
        knobLabel.setColour(juce::Label::ColourIds::textColourId, juce::Colours::whitesmoke.withAlpha(0.6f));
        knobTitle.setColour(juce::Label::ColourIds::textColourId, juce::Colours::whitesmoke.withAlpha(0.6f));
        accentColor = juce::Colours::whitesmoke.withAlpha(0.6f);
    }
    
    else
    {
        knobLabel.setColour(juce::Label::ColourIds::textColourId, newColor);
        knobTitle.setColour(juce::Label::ColourIds::textColourId, newColor);
        accentColor = newColor;
    }
    
    repaint();
}
