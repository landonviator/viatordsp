#include "MainComponent.h"

//==============================================================================
MainComponent::MainComponent()
{
    meter = std::make_unique<juce::ProgressBar>(meterThread.currentPercentage);
    addAndMakeVisible(meter.get());
    
    addAndMakeVisible(triggerButton);
    triggerButton.setButtonText("Trigger");
    
    triggerButton.onClick = [this]()
    {
        meterThread.startThread();
    };
    
    addAndMakeVisible(label);
    
    setSize (600, 300);
}

MainComponent::~MainComponent()
{
    meterThread.stopThread(1000);
}

//==============================================================================
void MainComponent::paint (juce::Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    juce::Rectangle<int> background = getLocalBounds();
    g.setGradientFill(juce::ColourGradient::vertical(juce::Colour::fromFloatRGBA(0.18f, 0.20f, 0.24f, 1.0), getHeight() * 0.25, juce::Colour::fromFloatRGBA(0.18f, 0.20f, 0.24f, 1.0).darker(0.15), getHeight() * 0.75));
    g.fillRect(background);

    g.setFont (juce::Font (36.0f));
    g.setColour (juce::Colours::dimgrey);
    g.drawText ("Testing", getLocalBounds(), juce::Justification::centredTop, true);
}

void MainComponent::resized()
{
    auto buttonSize = getWidth() * 0.15;
    
    triggerButton.setBounds(getLocalBounds().withSizeKeepingCentre(buttonSize, buttonSize * 0.5));
    meter->setBounds(getLocalBounds().withTrimmedTop(200).withSizeKeepingCentre(getWidth() * 0.45, getHeight() * 0.08));
    label.setBounds(100, 100, 100, 100);
}
