#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
LVTemplateAudioProcessorEditor::LVTemplateAudioProcessorEditor (LVTemplateAudioProcessor& p)
    : AudioProcessorEditor (&p), audioProcessor (p)
{
    uiConstructor();
}

LVTemplateAudioProcessorEditor::~LVTemplateAudioProcessorEditor()
{
    panel.setLookAndFeel(nullptr);
    testDial.setLookAndFeel(nullptr);
    
    buttons.clear();
    buttons.shrink_to_fit();
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


