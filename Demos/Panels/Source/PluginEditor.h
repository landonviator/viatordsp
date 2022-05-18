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

class Data
{
public:
    Data() {}

    juce::String getName() { return m_name; }

private:
    juce::String m_name;
};

class CustomComponent : public juce::Component
{
public:
    
    CustomComponent()
    {
        addAndMakeVisible(slider);
        slider.setSliderStyle(juce::Slider::SliderStyle::RotaryVerticalDrag);
    }
    
    ~CustomComponent()
    {
        
    }
    
    void paint(juce::Graphics& g) override
    {
        
    }
    
    void resized() override
    {
        slider.setBounds(getLocalBounds());
    }
    
private:
    juce::Slider slider;
    
};

class SourceItemListboxContents  : public ListBoxModel
{
public:
    
    // The following methods implement the necessary virtual functions from ListBoxModel,
    // telling the listbox how many rows there are, painting them, etc.
    int getNumRows() override
    {
        auto numRows = 5;
        m_data.resize(numRows);
        return numRows;
    }

    void paintListBoxItem (int rowNumber, Graphics& g,
                           int width, int height, bool rowIsSelected) override
    {
        if (rowIsSelected)
            g.fillAll (Colours::lightblue);
        
    }
    
    Component* refreshComponentForRow(int rowNumber, bool isRowSelected, Component* existingComponentToUpdate) override
    {
        CustomComponent *row = static_cast<CustomComponent*>(existingComponentToUpdate);

        if(rowNumber < m_data.size())
        {
             if(!row)
             {
                 row = new CustomComponent();
             }

            /* Update all properties of your custom component with the data for the current row  */
           //row->nameLabel.setText(m_data[rowNumber].getName());
        }
        else
        {
            //Nothing to display, free the custom component
            delete existingComponentToUpdate;
            row = nullptr;
        }

        return row;
    }
    
private:
    std::vector<Data> m_data;
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
