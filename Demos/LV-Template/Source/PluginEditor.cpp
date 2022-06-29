#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
LVTemplateAudioProcessorEditor::LVTemplateAudioProcessorEditor (LVTemplateAudioProcessor& p)
    : AudioProcessorEditor (&p), audioProcessor (p), m_settingsPage(audioProcessor)
{
    uiConstructor();
}

LVTemplateAudioProcessorEditor::~LVTemplateAudioProcessorEditor()
{
    /** Sliders */
    for (auto& slider : sliders)
    {
        slider->setLookAndFeel(nullptr);
    }
    
    sliders.clear();
    sliders.shrink_to_fit();
    
    buttons.clear();
    buttons.shrink_to_fit();
    
    groups.clear();
    groups.shrink_to_fit();
    
    m_settingsButton.setLookAndFeel(nullptr);
}

//==============================================================================
void LVTemplateAudioProcessorEditor::paint (juce::Graphics& g)
{
    uiPaint(g);
}

void LVTemplateAudioProcessorEditor::resized()
{
    uiResized();
}


