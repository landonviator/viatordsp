/*
  ==============================================================================

    MenuLAF.cpp
    Created: 13 Jul 2022 10:36:58pm
    Author:  Landon Viator

  ==============================================================================
*/

#include "MenuLAF.h"

void juce::Custom_Menu_Boy::positionComboBoxText (ComboBox& box, Label& label)
{
    label.setBounds (1,
                     1,
                     box.getWidth() * 0.9,
                     box.getHeight() * 1.1);

    label.setFont (Font (juce::Font ("Helvetica", box.getWidth() * 0.08, juce::Font::FontStyleFlags::bold)));
}

void juce::Custom_Menu_Boy::drawComboBox (Graphics& g, int width, int height, bool,
                                   int, int, int, int, ComboBox& box)
{
    auto cornerSize = box.findParentComponentOfClass<ChoicePropertyComponent>() != nullptr ? 0.0f : 6.0f;
    Rectangle<int> boxBounds (0, 0, width, height);

    g.setColour (box.findColour (ComboBox::backgroundColourId));
    g.fillRoundedRectangle (boxBounds.toFloat(), cornerSize);

    g.setColour (box.findColour (ComboBox::outlineColourId));
    g.drawRoundedRectangle (boxBounds.toFloat().reduced (0.5f, 0.5f), cornerSize, width * 0.015);

    Rectangle<int> arrowZone (width - 30, 0, 20, height);
    Path path;
    path.startNewSubPath ((float) arrowZone.getX() + 3.0f, (float) arrowZone.getCentreY() - 2.0f);
    path.lineTo ((float) arrowZone.getCentreX(), (float) arrowZone.getCentreY() + 3.0f);
    path.lineTo ((float) arrowZone.getRight() - 3.0f, (float) arrowZone.getCentreY() - 2.0f);

    g.setColour (box.findColour (ComboBox::arrowColourId).withAlpha ((box.isEnabled() ? 0.9f : 0.2f)));
    g.strokePath (path, PathStrokeType (2.0f));
}
