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
    
    // btn label
    addAndMakeVisible(btnLabel);
    btnLabel.setJustificationType(juce::Justification::centred);
    btnLabel.setFont(juce::Font("Helvetica", 10.0f, juce::Font::FontStyleFlags::bold));
    btnLabel.setColour(juce::Label::ColourIds::textColourId, viator_utils::gui_utils::Colors::_textColor);
    
    // button
    button.setClickingTogglesState(true);
    button.setImages(false, true, true, offImage, 1.0f, juce::Colours::transparentBlack, offImage, 1.0f, juce::Colours::transparentBlack, onImage, 1.0f, juce::Colours::transparentBlack);
    addAndMakeVisible(button);
    
    button.getToggleState() ? btnText = btnOnText : btnText = btnOffText;
    btnLabel.setText(btnText, juce::dontSendNotification);
    button.onClick = [this]()
    {
        button.getToggleState() ? btnText = btnOnText : btnText = btnOffText;
        btnLabel.setText(btnText, juce::dontSendNotification);
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
    btnLabel.setBounds(0, 0, getWidth(), getHeight() * 0.5);
    button.setBounds(0, btnLabel.getBottom(), getWidth(), getHeight() * 0.5);
    btnLabel.setFont(juce::Font("Helvetica", getWidth() * 0.1, juce::Font::FontStyleFlags::bold));
}

}
