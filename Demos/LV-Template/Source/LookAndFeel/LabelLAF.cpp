#include "LabelLAF.h"

LabelLAF::LabelLAF()
{
    
}

void LabelLAF::drawLabel(juce::Graphics &g, juce::Label &label)
{
    //Init
    label.setJustificationType(juce::Justification::centred);
    
    //Sizing
    auto cornerSize = 6.0f;
    auto bounds = label.getLocalBounds().toFloat().reduced (0.5f, 0.5f);
    
    //Fill
    g.setColour(label.findColour (juce::Label::backgroundColourId));
    g.fillRoundedRectangle (bounds, cornerSize);

    //Text
    const juce::Font font (getLabelFont (label));
    g.setColour (label.findColour (juce::Label::textColourId));
    g.setFont (font);
    g.drawFittedText (label.getText(), bounds.toNearestInt(), label.getJustificationType(),
                          juce::jmax (1, (int) ((float) bounds.getHeight() / font.getHeight())),
                          label.getMinimumHorizontalScale());

    //Border
    g.setColour (label.findColour (juce::Label::textColourId));
    g.drawRoundedRectangle (bounds, cornerSize, 1.0f);
}
