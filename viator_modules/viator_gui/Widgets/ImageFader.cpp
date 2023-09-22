#include "ImageFader.h"
namespace viator_gui
{

ImageFader::ImageFader ()
{
    setColour(juce::Slider::ColourIds::textBoxOutlineColourId, juce::Colours::transparentBlack);
    setColour(juce::Slider::ColourIds::backgroundColourId, juce::Colours::transparentBlack);
    setColour(juce::Slider::ColourIds::rotarySliderOutlineColourId, juce::Colours::transparentBlack);
    setColour(juce::Slider::ColourIds::textBoxTextColourId, juce::Colours::whitesmoke.withAlpha(0.5f));
    setColour(juce::Slider::ColourIds::trackColourId, juce::Colours::transparentBlack);
    setColour(juce::Slider::ColourIds::rotarySliderFillColourId, juce::Colours::transparentBlack);
    setColour(juce::Slider::ColourIds::thumbColourId, juce::Colours::transparentBlack);
    setLookAndFeel(&_customSliderLabel);
}

ImageFader::~ImageFader()
{
    setLookAndFeel(nullptr);
}

void ImageFader::paint (juce::Graphics& g)
{
    // alert dev that they didn't set an image
    if (!_mainImage.isValid() || _numFrames == 0)
    {
        g.setColour(juce::Colours::whitesmoke);
        g.setFont(12.0f);
        g.drawText("No image or num frames.", getLocalBounds(), juce::Justification::centred);
    }

    // do the film strip
    else
    {
        const float sliderPos = (float) valueToProportionOfLength(getValue());
        int value = sliderPos * (_numFrames - 1);

        g.drawImage(_mainImage, 0, 0, getWidth(), getHeight(), 0, value * _frameHeight, _frameWidth, _frameHeight);
    }
}

void ImageFader::resized()
{
    auto type = getSliderStyle() == LinearVertical;
    auto mult = type ? 0.05 : 0.15;
    setTextBoxStyle(TextBoxBelow, true, getWidth(), getHeight() * mult);
    juce::Slider::resized();
}

void ImageFader::setFaderImageAndNumFrames(const juce::Image main, const int numFrames)
{
    _mainImage = main;
    _numFrames = numFrames;
    
    _frameHeight = _mainImage.getHeight() / _numFrames;
    _frameWidth = _mainImage.getWidth();
    
    repaint();
}

void ImageFader::setDialValueType(CustomDialLabel::ValueType newValueType)
{
    _customSliderLabel.setDialValueType(newValueType);
    repaint();
}

}
