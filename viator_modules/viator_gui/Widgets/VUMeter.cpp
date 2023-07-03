#include "VUMeter.h"
namespace viator_gui
{

VUMeter::VUMeter (const juce::String& sliderName, const juce::Image& filmStrip)

{
    vuMeter.setSliderStyle(juce::Slider::SliderStyle::LinearHorizontal);
    vuMeter.setTextBoxStyle(juce::Slider::TextBoxLeft, true, 1, 1);
    vuMeter.setRange(-22.0, 6.0, 0.1);
    vuMeter.setSkewFactor(1.3);
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
//    auto vuGlow = juce::ImageCache::getFromMemory(BinaryData::back_vumeter_decore_png, BinaryData::back_vumeter_decore_pngSize);
//    auto vuGrid = juce::ImageCache::getFromMemory(BinaryData::scale_vumeter_png, BinaryData::scale_vumeter_pngSize);
//    
//    auto vuArea = getLocalBounds().toFloat();
//    g.drawImage(vuGlow, vuArea);
//    
//    auto gridScalar = 1.0;
//    g.drawImage(vuGrid, vuArea.withSizeKeepingCentre(getWidth() * gridScalar, getWidth() * 0.3555 * gridScalar));
//    
//    if (_filmStrip.isValid())
//    {
//        const float sliderPos = (float) vuMeter.valueToProportionOfLength(vuMeter.getValue());
//        int value = sliderPos * (_numFrames - 1);
//
//        g.drawImage(_filmStrip, 0, 0, getWidth(), getWidth() * 0.7, 0, value * frameHeight, getWidth(), getWidth() * 0.7);
//    }
}

void VUMeter::resized()
{
    vuMeter.setBounds(getLocalBounds());
}

}
