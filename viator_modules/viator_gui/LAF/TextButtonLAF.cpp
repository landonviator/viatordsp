/*
  ==============================================================================

    TextButtonLAF.cpp
    Created: 5 Sep 2022 7:12:07pm
    Author:  Landon Viator

  ==============================================================================
*/

#include "TextButtonLAF.h"

namespace juce
{
    namespace viator_gui
    {
        CustomTextButton::CustomTextButton()
        {
            buttonDropShadow.radius = 2;
            buttonDropShadow.offset = juce::Point<int> (0, 0);
            buttonDropShadow.colour = juce::Colours::black.withAlpha(1.0f);
        }

        void CustomTextButton::drawButtonBackground (Graphics& g,
                                                   Button& button,
                                                   const Colour& backgroundColour,
                                                   bool shouldDrawButtonAsHighlighted,
                                                   bool shouldDrawButtonAsDown)
        {
            buttonDropShadower = std::make_unique<juce::DropShadower>(buttonDropShadow);
            buttonDropShadower->setOwner(&button);
            
            auto cornerSize = 9.0f;
            auto bounds = button.getLocalBounds().toFloat().reduced (0.5f, 0.5f);

            auto baseColour = backgroundColour.withMultipliedSaturation (button.hasKeyboardFocus (true) ? 1.3f : 0.9f)
                                              .withMultipliedAlpha (button.isEnabled() ? 1.0f : 0.5f);

            if (shouldDrawButtonAsDown || shouldDrawButtonAsHighlighted)
                baseColour = baseColour.contrasting (shouldDrawButtonAsDown ? 0.2f : 0.05f);

            g.setColour (baseColour);

           // g.fillRoundedRectangle (bounds, cornerSize);
            g.fillRect(bounds);

            g.setColour (button.findColour (ComboBox::outlineColourId));
            //g.drawRoundedRectangle (bounds, cornerSize, 1.5f);
            g.drawRoundedRectangle(bounds, 0.0f, 1.0f);
        }

        Font CustomTextButton::getTextButtonFont (TextButton&, int buttonHeight)
        {
            return Font ("Helvetica", static_cast<float>(buttonHeight) * 0.5f, juce::Font::FontStyleFlags::bold);
        }
    }
}
