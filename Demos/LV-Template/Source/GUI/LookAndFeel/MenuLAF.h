/*
  ==============================================================================

    MenuLAF.h
    Created: 13 Jul 2022 10:36:58pm
    Author:  Landon Viator

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>

namespace juce
{
    /** Menu Style*/
    class Custom_Menu_Boy : public LookAndFeel_V4
    {
        void positionComboBoxText (ComboBox& box, Label& label) override;
        void drawComboBox (Graphics& g, int width, int height, bool,
                                                  int, int, int, int, ComboBox& box) override;
    };

}
