#include "VUMeter.h"
namespace viator_gui
{

VUMeter::VUMeter ()

{
    setInterceptsMouseClicks(false, false);
    vuMeter.setSliderStyle(juce::Slider::SliderStyle::LinearHorizontal);
    vuMeter.setTextBoxStyle(juce::Slider::TextBoxLeft, true, 1, 1);
    vuMeter.setRange(-20.0, 3.0, 0.1);
    vuMeter.setSkewFactor(1.85);
    vuMeter.setColour(juce::Slider::ColourIds::textBoxOutlineColourId, juce::Colours::transparentBlack);
    vuMeter.setColour(juce::Slider::ColourIds::backgroundColourId, juce::Colours::transparentBlack);
    vuMeter.setColour(juce::Slider::ColourIds::rotarySliderOutlineColourId, juce::Colours::transparentBlack);
    vuMeter.setColour(juce::Slider::ColourIds::textBoxTextColourId, juce::Colours::transparentBlack);
    vuMeter.setColour(juce::Slider::ColourIds::trackColourId, juce::Colours::transparentBlack);
    vuMeter.setColour(juce::Slider::ColourIds::rotarySliderFillColourId, juce::Colours::transparentBlack);
    vuMeter.setColour(juce::Slider::ColourIds::thumbColourId, juce::Colours::transparentBlack);
    addAndMakeVisible(vuMeter);
}

VUMeter::~VUMeter()
{
}

void VUMeter::paint (juce::Graphics& g)
{
    if (!_mainVUImage.isValid() || !_vuGridImage.isValid() || !_vuBGImage.isValid())
    {
        g.setColour(juce::Colours::whitesmoke);
        g.setFont(12.0f);
        g.drawText("You didn't set the images.", getLocalBounds(), juce::Justification::centred);
    }
    
    auto vuArea = getLocalBounds().toFloat();
    auto multGlow = 0.68;
    auto backY = getHeight() * 0.093 + 10;
    g.drawImage(_vuBGImage, vuArea.withSizeKeepingCentre(getWidth() * multGlow, getHeight() * multGlow).withY(backY));
    
    auto multGridWidth = 0.6;
    auto multGridHeight = multGridWidth * 0.6;
    auto scaleY = getHeight() * 0.2 + 10;
    g.drawImage(_vuGridImage, vuArea.withSizeKeepingCentre(getWidth() * multGridWidth, getHeight() * multGridHeight).withY(scaleY));
    
    const float sliderPos = (float) vuMeter.valueToProportionOfLength(vuMeter.getValue());
    int value = sliderPos * (_numFrames - 1);

    g.drawImage(_mainVUImage, 0, 10, getWidth(), getHeight(), 0, value * frameHeight, frameWidth, frameHeight);
}

void VUMeter::resized()
{
    vuMeter.setBounds(getLocalBounds());
}

void VUMeter::setVUImages(const juce::Image &main, const juce::Image &grid, const juce::Image &bg)
{
    // apply images
    _mainVUImage = main;
    _vuGridImage = grid;
    _vuBGImage = bg;
    
    // update sizes
    frameHeight = _mainVUImage.getHeight() / _numFrames;
    frameWidth = _mainVUImage.getWidth();
    
    // update vu image draw
    repaint();
}

}
