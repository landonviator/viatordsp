#include "ToggleButton.h"

viator_gui::ToggleButton::ToggleButton(bool isLargeButton, juce::String labelText)
{
    setClickingTogglesState(true);
    
    if (isLargeButton)
    {
//        setImages(false, true, true, juce::ImageCache::getFromMemory(BinaryData::button_middle_off_png, BinaryData::button_middle_off_pngSize), 1.0f, juce::Colours::transparentBlack, juce::ImageCache::getFromMemory(BinaryData::button_middle_off_png, BinaryData::button_middle_off_pngSize), 0.8f, juce::Colours::transparentBlack, juce::ImageCache::getFromMemory(BinaryData::button_middle_on_png, BinaryData::button_middle_on_pngSize), 1.0f, juce::Colours::transparentBlack);
    }
    
    else
    {
//        setImages(false, true, true, juce::ImageCache::getFromMemory(BinaryData::button_small_off_png, BinaryData::button_small_off_pngSize), 1.0f, juce::Colours::transparentBlack, juce::ImageCache::getFromMemory(BinaryData::button_small_off_png, BinaryData::button_small_off_pngSize), 0.8f, juce::Colours::transparentBlack, juce::ImageCache::getFromMemory(BinaryData::button_small_on_png, BinaryData::button_small_on_pngSize), 1.0f, juce::Colours::transparentBlack);
    }
    
    addAndMakeVisible(label);
    label.setText(labelText, juce::dontSendNotification);
    label.setJustificationType(juce::Justification::centredBottom);
    label.attachToComponent(this, false);
}

void viator_gui::ToggleButton::paint(juce::Graphics& g)
{
    juce::Button::paint(g);
}

void viator_gui::ToggleButton::resized()
{
    label.setFont(getWidth() * 0.15);
}

void viator_gui::ToggleButton::updateLabelColor(juce::Colour newColor)
{
    if (newColor == juce::Colours::black || newColor == juce::Colour::fromRGB(56, 72, 92))
    {
        label.setColour(juce::Label::ColourIds::textColourId, juce::Colours::whitesmoke.withAlpha(0.6f));
        accentColor = juce::Colours::whitesmoke.withAlpha(0.6f);
    }
    
    else
    {
        label.setColour(juce::Label::ColourIds::textColourId, newColor);
        accentColor = newColor;
    }
    
    repaint();
}
