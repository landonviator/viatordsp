/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"


//==============================================================================
/**
*/
struct SourceItemListboxContents  : public ListBoxModel
{
    // The following methods implement the necessary virtual functions from ListBoxModel,
    // telling the listbox how many rows there are, painting them, etc.
    int getNumRows() override
    {
        return 5;
    }

    void paintListBoxItem (int rowNumber, Graphics& g,
                           int width, int height, bool rowIsSelected) override
    {
        if (rowIsSelected)
            g.fillAll (Colours::lightblue);

        g.setColour (LookAndFeel::getDefaultLookAndFeel().findColour (Label::textColourId));
        g.setFont ((float) height * 0.7f);

        g.drawText ("Draggable Thing #" + String (rowNumber + 1),
                    5, 0, width, height,
                    Justification::centredLeft, true);
    }

    var getDragSourceDescription (const SparseSet<int>& selectedRows) override
    {
        // for our drag description, we'll just make a comma-separated list of the selected row
        // numbers - this will be picked up by the drag target and displayed in its box.
        StringArray rows;

        for (int i = 0; i < selectedRows.size(); ++i)
            rows.add (String (selectedRows[i] + 1));

        return rows.joinIntoString (", ");
    }
};

class PanelsAudioProcessorEditor  : public juce::AudioProcessorEditor
{
public:
    PanelsAudioProcessorEditor (PanelsAudioProcessor&);
    ~PanelsAudioProcessorEditor() override;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;

private:
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    PanelsAudioProcessor& audioProcessor;
    
    juce::ListBox listBox;
    SourceItemListboxContents sourceModel;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (PanelsAudioProcessorEditor)
};
