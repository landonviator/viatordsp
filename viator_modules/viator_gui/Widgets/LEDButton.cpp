#include "LEDButton.h"

viator_gui::LEDButton::LEDButton()
{
    setClickingTogglesState(true);
    
//    setImages(false, true, true, juce::ImageCache::getFromMemory(BinaryData::led_off_png, BinaryData::led_off_pngSize), 1.0f, juce::Colours::transparentBlack, juce::ImageCache::getFromMemory(BinaryData::led_off_png, BinaryData::led_off_pngSize), 0.8f, juce::Colours::transparentBlack, juce::ImageCache::getFromMemory(BinaryData::led_on_png, BinaryData::led_on_pngSize), 1.0f, juce::Colours::transparentBlack);
}

void viator_gui::LEDButton::paint(juce::Graphics& g)
{
    juce::Button::paint(g);
}

void viator_gui::LEDButton::resized()
{
    juce::Button::resized();
}
