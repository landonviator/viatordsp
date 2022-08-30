/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
IRLoaderDemoAudioProcessorEditor::IRLoaderDemoAudioProcessorEditor (IRLoaderDemoAudioProcessor& p)
    : AudioProcessorEditor (&p), audioProcessor (p)
{
    addAndMakeVisible(loadBtn);
    loadBtn.setButtonText("Load IR");
    loadBtn.onClick = [this]()
    {
        fileChooser = std::make_unique<juce::FileChooser>("Choose File",
                                                          audioProcessor.root,
                                                          "*");
        
        const auto fileChooserFlags = juce::FileBrowserComponent::openMode |
        juce::FileBrowserComponent::canSelectFiles | juce::FileBrowserComponent::canSelectDirectories;
        
        fileChooser->launchAsync(fileChooserFlags, [this](const juce::FileChooser& chooser)
        {
            juce::File result (chooser.getResult());
            
            if (result.getFileExtension() == ".wav" | result.getFileExtension() == ".mp3")
            {
                audioProcessor.savedFile = result;
                audioProcessor.variableTree.setProperty("file1", audioProcessor.savedFile.getFullPathName(), nullptr);
                audioProcessor.variableTree.setProperty("root", audioProcessor.savedFile.getParentDirectory().getFullPathName(), nullptr);
                audioProcessor.root = audioProcessor.savedFile.getParentDirectory().getFullPathName();
                audioProcessor.irLoader.loadImpulseResponse(audioProcessor.savedFile, juce::dsp::Convolution::Stereo::yes, juce::dsp::Convolution::Trim::yes, 0);
                irName.setText(result.getFileName(), juce::dontSendNotification);
            }
        });
    };
    
    addAndMakeVisible(irName);
    
    setSize (600, 400);
}

IRLoaderDemoAudioProcessorEditor::~IRLoaderDemoAudioProcessorEditor()
{
}

//==============================================================================
void IRLoaderDemoAudioProcessorEditor::paint (juce::Graphics& g)
{
    g.setGradientFill(juce::ColourGradient::vertical(juce::Colour::fromRGB(40, 42, 53).darker(0.35f), getHeight(), juce::Colour::fromRGB(40, 42, 53).brighter(0.02), getHeight() * 0.4));
    g.fillRect(getLocalBounds());
}

void IRLoaderDemoAudioProcessorEditor::resized()
{
    const auto btnX = getWidth() * 0.35;
    const auto btnY = getHeight() * 0.5;
    const auto btnWidth = getWidth() * 0.15;
    const auto btnHeight = btnWidth * 0.5;
    
    loadBtn.setBounds(btnX, btnY, btnWidth, btnHeight);
    irName.setBounds(loadBtn.getX() + loadBtn.getWidth(), btnY, btnWidth * 2, btnHeight);
}
