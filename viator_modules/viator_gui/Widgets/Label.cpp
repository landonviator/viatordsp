#include "Label.h"

void viator_gui::Label::paint(juce::Graphics& g)
{
    auto back = juce::ImageCache::getFromMemory(BinaryData::Articulations_back_png, BinaryData::Articulations_back_pngSize);
    
    g.drawImageWithin(back, 0, 0, getWidth(), getHeight(), juce::RectanglePlacement::stretchToFit);
    
    auto decor = juce::ImageCache::getFromMemory(BinaryData::Articulations_decore_png, BinaryData::Articulations_decore_pngSize);
    
    g.drawImageWithin(decor, 0, 0, getWidth(), getHeight(), juce::RectanglePlacement::stretchToFit);
    
    juce::Label::paint(g);
    
}

void viator_gui::Label::resized()
{
    juce::Label::resized();
    
    /** Just make the Label a square, bud*/
    jassert(getWidth() == getHeight());
    setFont(juce::Font ("Helvetica", getHeight() * 0.3, juce::Font::FontStyleFlags::bold));
    
}
