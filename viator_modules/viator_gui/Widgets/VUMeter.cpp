#include "VUMeter.h"
namespace viator_gui
{

VUMeter::VUMeter (const juce::String& sliderName, const juce::Image& filmStrip)

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
    auto vuGlow = juce::ImageCache::getFromMemory(BinaryData::back_vumeter_decore5_png, BinaryData::back_vumeter_decore5_pngSize);
    auto vuGrid = juce::ImageCache::getFromMemory(BinaryData::scale_vumeterno_name_png, BinaryData::scale_vumeterno_name_pngSize);

    auto vuArea = getLocalBounds().toFloat();
    auto multGlow = 0.68;
    auto backY = getHeight() * 0.093 + 10;
    g.drawImage(vuGlow, vuArea.withSizeKeepingCentre(getWidth() * multGlow, getHeight() * multGlow).withY(backY));
    
    auto multGridWidth = 0.6;
    auto multGridHeight = multGridWidth * 0.6;
    auto scaleY = getHeight() * 0.2 + 10;
    g.drawImage(vuGrid, vuArea.withSizeKeepingCentre(getWidth() * multGridWidth, getHeight() * multGridHeight).withY(scaleY));
    
    if (_filmStrip.isValid())
    {
        const float sliderPos = (float) vuMeter.valueToProportionOfLength(vuMeter.getValue());
        int value = sliderPos * (_numFrames - 1);

        g.drawImage(_filmStrip, 0, 10, getWidth(), getHeight(), 0, value * frameHeight, frameWidth, frameHeight);
    }
}

void VUMeter::resized()
{
    vuMeter.setBounds(getLocalBounds());
}

}
