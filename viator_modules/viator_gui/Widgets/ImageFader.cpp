#include "ImageFader.h"
namespace viator_gui
{

ImageFader::ImageFader ()
{
    _fader.setSliderStyle(juce::Slider::SliderStyle::LinearVertical);
    _fader.setTextBoxStyle(juce::Slider::TextBoxLeft, true, 1, 1);
    _fader.setColour(juce::Slider::ColourIds::textBoxOutlineColourId, juce::Colours::transparentBlack);
    _fader.setColour(juce::Slider::ColourIds::backgroundColourId, juce::Colours::transparentBlack);
    _fader.setColour(juce::Slider::ColourIds::rotarySliderOutlineColourId, juce::Colours::transparentBlack);
    _fader.setColour(juce::Slider::ColourIds::textBoxTextColourId, juce::Colours::transparentBlack);
    _fader.setColour(juce::Slider::ColourIds::trackColourId, juce::Colours::transparentBlack);
    _fader.setColour(juce::Slider::ColourIds::rotarySliderFillColourId, juce::Colours::transparentBlack);
    _fader.setColour(juce::Slider::ColourIds::thumbColourId, juce::Colours::transparentBlack);
    addAndMakeVisible(_fader);
}

ImageFader::~ImageFader()
{
}

void ImageFader::paint (juce::Graphics& g)
{
    if (!_mainImage.isValid() || _numFrames == 0)
    {
        g.setColour(juce::Colours::whitesmoke);
        g.setFont(12.0f);
        g.drawText("No image or num frames.", getLocalBounds(), juce::Justification::centred);
    }
    
    else
    {
        const float sliderPos = (float) _fader.valueToProportionOfLength(_fader.getValue());
        int value = sliderPos * (_numFrames - 1);

        g.drawImage(_mainImage, 0, 0, getWidth(), getHeight(), 0, value * _frameHeight, _frameWidth, _frameHeight);
    }
}

void ImageFader::resized()
{
    _fader.setBounds(getLocalBounds());
}

void ImageFader::setFaderImageAndNumFrames(const juce::Image main, const int numFrames)
{
    _mainImage = main;
    _numFrames = numFrames;
    
    _frameHeight = _mainImage.getHeight() / _numFrames;
    _frameWidth = _mainImage.getWidth();
    
    repaint();
}

}
