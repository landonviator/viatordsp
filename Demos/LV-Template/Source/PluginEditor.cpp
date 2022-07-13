#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
LVTemplateAudioProcessorEditor::LVTemplateAudioProcessorEditor (LVTemplateAudioProcessor& p)
    : AudioProcessorEditor (&p), audioProcessor (p), m_settingsPage(audioProcessor)
, m_distortionLabel("Distortion")
, m_crusherLabel("Distortion")
, m_toneLabel("Tone")
, m_reverbLabel("Reverb")
{
    uiConstructor();
}

LVTemplateAudioProcessorEditor::~LVTemplateAudioProcessorEditor()
{
    /** Sliders */
    for (auto& slider : disSliders)
    {
        slider->setLookAndFeel(nullptr);
    }
    
    for (auto& slider : toneSliders)
    {
        slider->setLookAndFeel(nullptr);
    }
    
    for (auto& slider : verbSliders)
    {
        slider->setLookAndFeel(nullptr);
    }
    
    disSliders.clear();
    disSliders.shrink_to_fit();
    
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


