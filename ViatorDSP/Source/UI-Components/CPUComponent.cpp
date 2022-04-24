#include "CPUComponent.h"

CPUComponent::CPUComponent(ViatorDSPAudioProcessor& p) : audioProcessor(p)
{
    
    addAndMakeVisible(cpuLabel);
    addAndMakeVisible(cpuHeader);
    addAndMakeVisible(cpuButton);
    cpuButtonAttach = std::make_unique<juce::AudioProcessorValueTreeState::ButtonAttachment>(audioProcessor.treeState, "cpu", cpuButton);
}

CPUComponent::~CPUComponent()
{
    cpuButtonAttach = nullptr;
}

void CPUComponent::paint(juce::Graphics &g)
{
    
}

void CPUComponent::resized()
{
    topHeaderMargin = getHeight() * 0.015;
    auto labelSize = getWidth() * 0.05;
    
    cpuButton.setBounds(getWidth() * 0.84, getHeight() * 0.87, labelSize, labelSize);
    cpuLabel.setBounds(cpuButton.getX() + cpuButton.getWidth(), cpuButton.getY(), labelSize, labelSize);
    cpuHeader.setBounds(cpuLabel.getX() + cpuLabel.getWidth(), cpuLabel.getY(), labelSize, labelSize);
}

void CPUComponent::updateLabel(juce::String newText)
{
    cpuLabel.setText(newText, juce::dontSendNotification);
}
