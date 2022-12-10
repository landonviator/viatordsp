#include "WindowSlider.h"

viator_gui::WindowSlider::WindowSlider()
{
    _minPopup.setColour(juce::Label::ColourIds::backgroundColourId, juce::Colours::whitesmoke.withAlpha(0.25f));
    _minPopup.setColour(juce::Label::ColourIds::textColourId, juce::Colour::fromRGB(107, 208, 234));
    _minPopup.setJustificationType(juce::Justification::centred);
    addAndMakeVisible(_minPopup);
    _minPopup.setVisible(false);
    
    _maxPopup.setColour(juce::Label::ColourIds::backgroundColourId, juce::Colours::whitesmoke.withAlpha(0.25f));
    _maxPopup.setColour(juce::Label::ColourIds::textColourId, juce::Colour::fromRGB(107, 208, 234));
    _maxPopup.setJustificationType(juce::Justification::centred);
    addAndMakeVisible(_maxPopup);
    _maxPopup.setVisible(false);
}

void viator_gui::WindowSlider::resized()
{
    juce::Slider::resized();
    setPopupPosition();
}

void viator_gui::WindowSlider::mouseMove (const juce::MouseEvent &)
{
}

void viator_gui::WindowSlider::mouseEnter (const juce::MouseEvent &)
{
    _minPopup.setVisible(true);
    _maxPopup.setVisible(true);
}

void viator_gui::WindowSlider::mouseExit (const juce::MouseEvent &)
{
    _minPopup.setVisible(false);
    _maxPopup.setVisible(false);
}

void viator_gui::WindowSlider::setPopupPosition()
{
    const auto labelSize = getWidth() * 0.06;
    auto isMaxTopEnd = getMaxValue() > getMaximum() * 0.5;
    auto isMinTopEnd = getMinValue() > getMaximum() * 0.5;
    
    if (isMaxTopEnd)
    {
        _maxPopup.setBounds(getPositionOfValue(getMaxValue()) - labelSize, getHeight() * 0.8, labelSize, labelSize);
    }
    
    else if (!isMaxTopEnd)
    {
        _maxPopup.setBounds(getPositionOfValue(getMaxValue()), getHeight() * 0.8, labelSize, labelSize);
    }
    
    if (isMinTopEnd)
    {
        _minPopup.setBounds(getPositionOfValue(getMinValue()) - labelSize, 0, labelSize, labelSize);
    }
    
    else if (!isMinTopEnd)
    {
        _minPopup.setBounds(getPositionOfValue(getMinValue()), 0, labelSize, labelSize);
    }
    
    _minPopup.setText(juce::String(static_cast<int>(getMinValue())), juce::dontSendNotification);
    _minPopup.setFont(_minPopup.getHeight() * 0.25);
    _maxPopup.setText(juce::String(static_cast<int>(getMaxValue())), juce::dontSendNotification);
    _maxPopup.setFont(_minPopup.getHeight() * 0.25);
}
