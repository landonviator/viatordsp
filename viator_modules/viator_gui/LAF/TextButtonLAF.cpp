#include "TextButtonLAF.h"

    namespace viator_gui
    {
        CustomTextButton::CustomTextButton()
        {
        }

        void CustomTextButton::drawButtonBackground (juce::Graphics& g,
                                                     juce::Button& button,
                                                   const juce::Colour& backgroundColour,
                                                   bool shouldDrawButtonAsHighlighted,
                                                   bool shouldDrawButtonAsDown)
        {
            auto cornerSize = 6.0f;
            auto bounds = button.getLocalBounds().toFloat().reduced (0.5f, 0.5f);

            auto baseColour = backgroundColour.withMultipliedSaturation (button.hasKeyboardFocus (true) ? 1.3f : 0.9f)
                                              .withMultipliedAlpha (button.isEnabled() ? 1.0f : 0.5f);

            if (shouldDrawButtonAsDown || shouldDrawButtonAsHighlighted)
                baseColour = baseColour.contrasting (shouldDrawButtonAsDown ? 0.2f : 0.05f);

            g.setColour (baseColour);
            g.fillRoundedRectangle(bounds, cornerSize);

            g.setColour (button.findColour (juce::ComboBox::outlineColourId));
            g.drawRoundedRectangle(bounds, cornerSize, 1.0f);
        }

    juce::Font CustomTextButton::getTextButtonFont (juce::TextButton&, int buttonHeight)
        {
            return juce::Font ("Helvetica", static_cast<float>(buttonHeight) * 0.25f, juce::Font::FontStyleFlags::bold);
        }
    }
