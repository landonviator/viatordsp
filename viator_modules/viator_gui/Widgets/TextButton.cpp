#include <JuceHeader.h>
#include "TextButton.h"

namespace viator_gui
{

TextButton::TextButton()
{
    setClickingTogglesState(true);
    initButtonColors();
}

TextButton::TextButton(const juce::String& name)
{
    setButtonText(name);
    setName(name);
}

TextButton::~TextButton()
{
    setLookAndFeel(nullptr);
}

void TextButton::paint (juce::Graphics& g)
{
    juce::TextButton::paint(g);
}

void TextButton::resized()
{
    juce::TextButton::resized();
}

void TextButton::initButtonColors()
{
    setColour(juce::TextButton::ColourIds::buttonColourId, juce::Colours::transparentBlack);
    setColour(juce::TextButton::ColourIds::buttonOnColourId, juce::Colours::transparentBlack);
    setColour(juce::ComboBox::outlineColourId, juce::Colours::transparentBlack);
    setColour(juce::TextButton::ColourIds::textColourOnId, viator_utils::gui_utils::Colors::_textColor);
    setColour(juce::TextButton::ColourIds::textColourOffId, viator_utils::gui_utils::Colors::_textColor);
}

void TextButton::setButtonStyle(const ButtonStyle &newStyle)
{
    _buttonStyle = newStyle;
    
    switch(_buttonStyle)
    {
        case ButtonStyle::kSettings:
        {
            initButtonColors();
            setLookAndFeel(&_customLAF);
            setButtonText("");
            repaint();
            break;
        }
            
        case ButtonStyle::kNormal:
        {
            initButtonColors();
            setLookAndFeel(&_customTextButton);
            repaint();
            break;
        }
    }
}

}
