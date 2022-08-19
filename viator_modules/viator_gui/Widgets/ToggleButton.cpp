#include "ToggleButton.h"

viator_gui::ToggleButton::ToggleButton(bool useLabel, juce::String labelText, bool isPhase)
{
    setClickingTogglesState(true);
    _useLabel = useLabel;
    _isPhase = isPhase;
    _labelText = labelText;
    
    setImages(false, true, true, juce::ImageCache::getFromMemory(BinaryData::button_middle_off_png, BinaryData::button_middle_off_pngSize), 1.0f, juce::Colours::transparentBlack, juce::ImageCache::getFromMemory(BinaryData::button_middle_off_png, BinaryData::button_middle_off_pngSize), 0.8f, juce::Colours::transparentBlack, juce::ImageCache::getFromMemory(BinaryData::button_middle_on_png, BinaryData::button_middle_on_pngSize), 1.0f, juce::Colours::transparentBlack);
    
    setColour(juce::ToggleButton::ColourIds::tickDisabledColourId, juce::Colours::black);
}

void viator_gui::ToggleButton::paint(juce::Graphics& g)
{
    juce::Button::paint(g);
    
    if (_isPhase && !_useLabel)
    {
        juce::Path button;
        
        auto bounds = getLocalBounds();
        
        auto mult = 7.4;
        
        auto size = juce::jmin(bounds.getWidth(), bounds.getHeight());
        auto sr = bounds.withSizeKeepingCentre(size / mult, size / mult).toFloat();
        
        button.addEllipse(sr);
        
        button.startNewSubPath(sr.getX(), sr.getY() + sr.getHeight());
        button.lineTo(sr.getX() + sr.getWidth(), sr.getY());
        
        juce::PathStrokeType pst(2.0f, juce::PathStrokeType::JointStyle::curved);
        
        auto color =
        getToggleState() ? findColour(juce::ToggleButton::tickColourId) : findColour(juce::ToggleButton::tickDisabledColourId);
        
        g.setColour(color);
        g.strokePath(button, pst);
    }
    
    else
    {
        auto color =
        getToggleState() ? findColour(juce::ToggleButton::tickColourId) : findColour(juce::ToggleButton::tickDisabledColourId);
        
        g.setColour(color);
        g.setFont(juce::Font ("Helvetica", getWidth() * 0.13, juce::Font::FontStyleFlags::bold));
        g.drawText(_labelText, getLocalBounds(), juce::Justification::centred);
    }
}

void viator_gui::ToggleButton::resized()
{
}

void viator_gui::ToggleButton::updateLabelColor(juce::Colour newColor)
{
    if (_useLabel)
    {
        if (newColor == juce::Colours::black || newColor == juce::Colour::fromRGB(56, 72, 92))
        {
            accentColor = juce::Colours::whitesmoke.withAlpha(0.6f);
        }
        
        else
        {
            accentColor = newColor;
        }
    }
}
