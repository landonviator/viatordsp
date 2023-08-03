#include <JuceHeader.h>
#include "ImageButton.h"

namespace viator_gui
{

ImageButton::ImageButton(const juce::Image& offImage,
                         const juce::Image& onImage,
                         const juce::String& offText,
                         const juce::String& onText)
{
    btnOffText = offText;
    btnOnText = onText;
    
    // button
    button.setClickingTogglesState(true);
    button.setImages(false, true, true, offImage, 1.0f, juce::Colours::transparentBlack, offImage, 1.0f, juce::Colours::transparentBlack, onImage, 1.0f, juce::Colours::transparentBlack);
    addAndMakeVisible(button);
    
    // btn label
    addAndMakeVisible(btnLabel);
    btnLabel.setJustificationType(juce::Justification::centred);
    btnLabel.setFont(juce::Font("Helvetica", 10.0f, juce::Font::FontStyleFlags::bold));
    btnLabel.setColour(juce::Label::ColourIds::textColourId, button.getToggleState() ? juce::Colours::black : juce::Colours::whitesmoke);
    btnLabel.setInterceptsMouseClicks(false, false);
    
    btnLabel.setText(button.getToggleState() ? btnOnText : btnOffText, juce::dontSendNotification);
    button.onClick = [this]()
    {
        btnLabel.setText(button.getToggleState() ? btnOnText : btnOffText, juce::dontSendNotification);
        btnLabel.setColour(juce::Label::ColourIds::textColourId, button.getToggleState() ? juce::Colours::black : juce::Colours::whitesmoke);
    };
}

ImageButton::~ImageButton()
{
}

void ImageButton::paint (juce::Graphics& g)
{
}

void ImageButton::resized()
{
    button.setBounds(getLocalBounds());
    btnLabel.setBounds(getLocalBounds());
    btnLabel.setFont(juce::Font("Helvetica", getWidth() * 0.12, juce::Font::FontStyleFlags::bold));
}

}
