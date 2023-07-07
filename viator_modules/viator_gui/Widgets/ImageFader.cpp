#include "ImageFader.h"
namespace viator_gui
{

ImageFader::ImageFader (int numFrames, const juce::Image& filmStrip)

{
    vuMeter.setSliderStyle(juce::Slider::SliderStyle::LinearVertical);
    vuMeter.setTextBoxStyle(juce::Slider::TextBoxLeft, true, 1, 1);
    vuMeter.setColour(juce::Slider::ColourIds::textBoxOutlineColourId, juce::Colours::transparentBlack);
    vuMeter.setColour(juce::Slider::ColourIds::backgroundColourId, juce::Colours::transparentBlack);
    vuMeter.setColour(juce::Slider::ColourIds::rotarySliderOutlineColourId, juce::Colours::transparentBlack);
    vuMeter.setColour(juce::Slider::ColourIds::textBoxTextColourId, juce::Colours::transparentBlack);
    vuMeter.setColour(juce::Slider::ColourIds::trackColourId, juce::Colours::transparentBlack);
    vuMeter.setColour(juce::Slider::ColourIds::rotarySliderFillColourId, juce::Colours::transparentBlack);
    vuMeter.setColour(juce::Slider::ColourIds::thumbColourId, juce::Colours::transparentBlack);
    addAndMakeVisible(vuMeter);
    
    // film strip
    _numFrames = numFrames;
    _filmStrip = filmStrip;
    frameHeight = filmStrip.getHeight() / _numFrames;
    frameWidth = filmStrip.getWidth();
}

ImageFader::~ImageFader()
{
}

void ImageFader::paint (juce::Graphics& g)
{
    if (_filmStrip.isValid())
    {
        const float sliderPos = (float) vuMeter.valueToProportionOfLength(vuMeter.getValue());
        int value = sliderPos * (_numFrames - 1);

        g.drawImage(_filmStrip, 0, 0, getWidth(), getHeight(), 0, value * frameHeight, frameWidth, frameHeight);
    }
}

void ImageFader::resized()
{
    vuMeter.setBounds(getLocalBounds());
}

}
