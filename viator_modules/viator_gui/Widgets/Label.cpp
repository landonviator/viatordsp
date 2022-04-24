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
    
    const juce::Font font (juce::Font ("Helvetica", 16.0f, juce::Font::FontStyleFlags::bold));
    setFont(font);
    
    labelIsTransparent = isTransparent;
}

void viator_gui::Label::paint(juce::Graphics& g)
{
    if (!labelIsTransparent)
    {
        
        auto back = juce::ImageCache::getFromMemory(BinaryData::Articulations_back_png, BinaryData::Articulations_back_pngSize);
        
        g.drawImageWithin(back, 0, 0, getWidth(), getHeight(), juce::RectanglePlacement::stretchToFit);
        
        auto decor = juce::ImageCache::getFromMemory(BinaryData::Articulations_decore_png, BinaryData::Articulations_decore_pngSize);
        
        g.drawImageWithin(decor, 0, 0, getWidth(), getHeight(), juce::RectanglePlacement::stretchToFit);
        
        juce::Label::paint(g);
    }
    
    juce::Label::paint(g);
}

void viator_gui::Label::resized()
{
    juce::Label::resized();
    
    setFont(juce::Font ("Helvetica", getHeight() * 0.3, juce::Font::FontStyleFlags::bold));
    
}
