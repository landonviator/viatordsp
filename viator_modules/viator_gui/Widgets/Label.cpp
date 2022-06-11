#include "Label.h"

viator_gui::Label::Label()
{
    
}

viator_gui::Label::Label(bool isTransparent, juce::String text)
{
    setText(text, juce::dontSendNotification);
    setColour(0x1000280, juce::Colour::fromFloatRGBA(0, 0, 0, 0));
    setColour(0x1000282, juce::Colour::fromFloatRGBA(0, 0, 0, 0));
    setColour(juce::Label::ColourIds::textColourId, juce::Colours::whitesmoke.darker(1.0f));
    setJustificationType(juce::Justification::centred);
    setFont(juce::Font ("Helvetica", getWidth() * 0.1, juce::Font::FontStyleFlags::bold));
    
    labelIsTransparent = isTransparent;
}

void viator_gui::Label::paint(juce::Graphics& g)
{
    if (!labelIsTransparent)
    {
        
//        auto back = juce::ImageCache::getFromMemory(BinaryData::Articulations_back_png, BinaryData::Articulations_back_pngSize);
//        
//        g.drawImageWithin(back, 0, 0, getWidth(), getHeight(), juce::RectanglePlacement::stretchToFit);
//        
//        auto decor = juce::ImageCache::getFromMemory(BinaryData::Articulations_decore_png, BinaryData::Articulations_decore_pngSize);
//        
//        g.drawImageWithin(decor, 0, 0, getWidth(), getHeight(), juce::RectanglePlacement::stretchToFit);
        
        juce::Label::paint(g);
    }
    
    else
    {
        juce::Label::paint(g);
    }
}

void viator_gui::Label::resized()
{
    juce::Label::resized();
    
    if (autoResize)
    {
        setFont(juce::Font ("Helvetica", getWidth() * 0.1, juce::Font::FontStyleFlags::bold));
    }
}

void viator_gui::Label::updateLabelColor(juce::Colour newColor)
{
    if (newColor == juce::Colours::black || newColor == juce::Colour::fromRGB(56, 72, 92))
    {
        setColour(juce::Label::ColourIds::textColourId, juce::Colours::whitesmoke.withAlpha(0.6f));
    }
    
    else
    {
        setColour(juce::Label::ColourIds::textColourId, newColor);
    }
}
