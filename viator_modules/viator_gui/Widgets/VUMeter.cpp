#include "VUMeter.h"
namespace viator_gui
{

VUMeter::VUMeter (const juce::String& sliderName, const juce::Image& filmStrip)

{
    vuMeter.setSliderStyle(juce::Slider::SliderStyle::LinearHorizontal);
    vuMeter.setTextBoxStyle(juce::Slider::TextBoxLeft, true, 1, 1);
    vuMeter.setRange(-25.0, 0.0, 0.1);
    vuMeter.setColour(juce::Slider::ColourIds::textBoxOutlineColourId, juce::Colours::transparentBlack);
    vuMeter.setColour(juce::Slider::ColourIds::backgroundColourId, juce::Colours::transparentBlack);
    vuMeter.setColour(juce::Slider::ColourIds::rotarySliderOutlineColourId, juce::Colours::transparentBlack);
    vuMeter.setColour(juce::Slider::ColourIds::textBoxTextColourId, juce::Colours::transparentBlack);
    vuMeter.setColour(juce::Slider::ColourIds::trackColourId, juce::Colours::transparentBlack);
    vuMeter.setColour(juce::Slider::ColourIds::rotarySliderFillColourId, juce::Colours::transparentBlack);
    vuMeter.setColour(juce::Slider::ColourIds::thumbColourId, juce::Colours::transparentBlack);
    addAndMakeVisible(vuMeter);
    
    vuMeter.onValueChange = [this]()
    {
        DBG("Meter: " << vuMeter.getValue());
    };
    
    // film strip
    _filmStrip = filmStrip;
    frameHeight = filmStrip.getHeight() / _numFrames;
    frameWidth = filmStrip.getWidth();
}

VUMeter::~VUMeter()
{
}

void VUMeter::paint (juce::Graphics& g)
{
    auto vuGlow = juce::ImageCache::getFromMemory(BinaryData::back_vumeter_decore_png, BinaryData::back_vumeter_decore_pngSize);

    auto vuArea = getLocalBounds().toFloat();
    auto mult = 0.68;
    auto backY = getHeight() * 0.093;
    g.drawImage(vuGlow, vuArea.withSizeKeepingCentre(getWidth() * mult, getHeight() * mult).withY(backY));
    
    if (_filmStrip.isValid())
    {
        const float sliderPos = (float) vuMeter.valueToProportionOfLength(vuMeter.getValue());
        int value = sliderPos * (_numFrames - 1);

        g.drawImage(_filmStrip, 0, 0, getWidth(), getHeight(), 0, value * frameHeight, frameWidth, frameHeight);
    }
}

void VUMeter::resized()
{
    vuMeter.setBounds(getLocalBounds());
}

}
