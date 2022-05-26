#include "ColorButtonLAF.h"

ColorButtonLAF::ColorButtonLAF()
{
    
}

void ColorButtonLAF::drawButtonBackground (juce::Graphics& g,
                                           juce::Button& button,
                                        const juce::Colour& backgroundColour,
                                        bool shouldDrawButtonAsHighlighted,
                                        bool shouldDrawButtonAsDown)
{
    button.setClickingTogglesState(false);
    
    auto bounds = button.getLocalBounds().toFloat().reduced (0.5f, 0.5f);
    
    auto baseColour = backgroundColour.withMultipliedSaturation (button.hasKeyboardFocus (true) ? 1.3f : 0.9f).withMultipliedAlpha (button.isEnabled() ? 1.0f : 0.5f);
    
    if (shouldDrawButtonAsDown || shouldDrawButtonAsHighlighted)
        baseColour = baseColour.contrasting (shouldDrawButtonAsDown ? 0.2f : 0.05f);
    
    g.setColour (baseColour);
    g.fillEllipse(bounds);
}
