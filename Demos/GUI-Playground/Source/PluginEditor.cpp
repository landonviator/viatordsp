/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
GUIPlaygroundAudioProcessorEditor::GUIPlaygroundAudioProcessorEditor (GUIPlaygroundAudioProcessor& p)
    : AudioProcessorEditor (&p), audioProcessor (p)
{
    alertWindow = std::make_unique<juce::AlertWindow>("Alert",
                                                      "Choose an option",
                                                      juce::MessageBoxIconType::InfoIcon,
                                                      nullptr);
    alertWindow->addProgressBarComponent(progress);
    
    addAndMakeVisible(alertBtn);
    alertBtn.setButtonText("Alert");
    alertBtn.setColour(juce::TextButton::ColourIds::textColourOnId, juce::Colours::whitesmoke.withAlpha(0.75f));
    alertBtn.setColour(juce::TextButton::ColourIds::textColourOffId, juce::Colours::whitesmoke.withAlpha(0.75f));
    alertBtn.setColour(juce::TextButton::ColourIds::buttonColourId, juce::Colours::transparentBlack);
    alertBtn.setColour(juce::TextButton::ColourIds::buttonOnColourId, juce::Colours::transparentBlack);
    alertBtn.setColour(juce::ComboBox::ColourIds::outlineColourId, juce::Colours::whitesmoke.withAlpha(0.75f));
    alertBtn.onClick = [this]()
    {
        startTimerHz(10);
        
        
        alertWindow->showYesNoCancelBox(juce::MessageBoxIconType::InfoIcon, "Alert", "Would you like to quit the app and locate the missing file?", "Yes", "No", "Cancel", nullptr, juce::ModalCallbackFunction::create([this](int result)
        {
            stopTimer();
        }));
    };
    
    addAndMakeVisible(slider);
    
    setSize (900, 600);
}

GUIPlaygroundAudioProcessorEditor::~GUIPlaygroundAudioProcessorEditor()
{
}

//==============================================================================
void GUIPlaygroundAudioProcessorEditor::paint (juce::Graphics& g)
{
    g.setGradientFill(juce::ColourGradient::vertical(juce::Colour::fromRGB(252, 66, 123), getHeight(), juce::Colour::fromRGB(214, 162, 232), getHeight() * 0.3));
    g.fillRect(getLocalBounds());
    
    g.setColour(juce::Colours::whitesmoke.withAlpha(0.25f));
    g.fillRect(getLocalBounds().withSizeKeepingCentre(getWidth() * 0.9, getHeight() * 0.9));
}

void GUIPlaygroundAudioProcessorEditor::resized()
{
    const auto size = getWidth() * 0.1;
    alertBtn.setBounds(getLocalBounds().withSizeKeepingCentre(size, size * 0.5));
    slider.setBounds(100, 100, 300, 100);
}
