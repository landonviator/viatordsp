/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
ParaEQDemoAudioProcessorEditor::ParaEQDemoAudioProcessorEditor (ParaEQDemoAudioProcessor& p)
    : AudioProcessorEditor (&p), audioProcessor (p)
{
    initWindowSize();
    
    startTimerHz(30);
    
    // Dial props
    for (auto& dial : dials)
    {
        setSliderProps(*dial);
    }
    
    // Label props
    for (auto& label : labels)
    {
        setLabelProps(*label);
    }
    
    // Graph Label props
    for (auto& label : graphLabels)
    {
        setLabelProps(*label);
    }
    
    // Attach labels
    for (int i = 0; i < labels.size(); ++i)
    {
        labels[i]->attachToComponent(dials[i], false);
    }
    
    // Slider attachments
    band1GainDialAttach = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.treeState, "band1Gain", band1GainDial);
    band1CutoffDialAttach = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.treeState, "band1Cutoff", band1CutoffDial);
    band1QDialAttach = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.treeState, "band1Q", band1QDial);
    
    band2GainDialAttach = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.treeState, "band2Gain", band2GainDial);
    band2CutoffDialAttach = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.treeState, "band2Cutoff", band2CutoffDial);
    band2QDialAttach = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.treeState, "band2Q", band2QDial);
    
    band3GainDialAttach = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.treeState, "band3Gain", band3GainDial);
    band3CutoffDialAttach = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.treeState, "band3Cutoff", band3CutoffDial);
    band3QDialAttach = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.treeState, "band3Q", band3QDial);
    
    band4GainDialAttach = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.treeState, "band4Gain", band4GainDial);
    band4CutoffDialAttach = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.treeState, "band4Cutoff", band4CutoffDial);
    band4QDialAttach = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.treeState, "band4Q", band4QDial);
    
    band5GainDialAttach = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.treeState, "band5Gain", band5GainDial);
    band5CutoffDialAttach = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.treeState, "band5Cutoff", band5CutoffDial);
    band5QDialAttach = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.treeState, "band5Q", band5QDial);
    
    band6GainDialAttach = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.treeState, "band6Gain", band6GainDial);
    band6CutoffDialAttach = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.treeState, "band6Cutoff", band6CutoffDial);
    band6QDialAttach = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.treeState, "band6Q", band6QDial);
    
    band7GainDialAttach = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.treeState, "band7Gain", band7GainDial);
    band7CutoffDialAttach = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.treeState, "band7Cutoff", band7CutoffDial);
    band7QDialAttach = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.treeState, "band7Q", band7QDial);
}

ParaEQDemoAudioProcessorEditor::~ParaEQDemoAudioProcessorEditor()
{
    band1GainDialAttach.reset();
    band1CutoffDialAttach.reset();
    band1QDialAttach.reset();
    
    band2GainDialAttach.reset();
    band2CutoffDialAttach.reset();
    band2QDialAttach.reset();
    
    band3GainDialAttach.reset();
    band3CutoffDialAttach.reset();
    band3QDialAttach.reset();
    
    band4GainDialAttach.reset();
    band4CutoffDialAttach.reset();
    band4QDialAttach.reset();
    
    band5GainDialAttach.reset();
    band5CutoffDialAttach.reset();
    band5QDialAttach.reset();
    
    band6GainDialAttach.reset();
    band6CutoffDialAttach.reset();
    band6QDialAttach.reset();
    
    band7GainDialAttach.reset();
    band7CutoffDialAttach.reset();
    band7QDialAttach.reset();
    
    stopTimer();
}

//==============================================================================
void ParaEQDemoAudioProcessorEditor::paint (juce::Graphics& g)
{
    g.fillAll(juce::Colour::fromRGB(40, 42, 54));
    
    g.setColour(juce::Colours::black);
    g.fillRect(m_analyzerBounds);
    m_analyzerBounds.setBounds(0, 0, getWidth(), getHeight() * 0.5);
    
    drawFrame(g);
}

void ParaEQDemoAudioProcessorEditor::resized()
{
    const auto leftMargin = getWidth() * 0.1;
    const auto topMargin = getHeight() * 0.58;
    const auto dialSize = getWidth() * 0.06;
    const auto spaceBetween = 1.4;
    auto groupSpace = 2.25;
    auto groupSpaceOffset = 1.25;
    
    m_analyzerBounds.setBounds(0, 0, getWidth(), getHeight() * 0.5);
    
    band1GainDial.setBounds(leftMargin, topMargin, dialSize, dialSize);
    band1CutoffDial.setBounds(leftMargin - band1GainDial.getWidth() * 0.5, band1GainDial.getY() + band1GainDial.getHeight() * spaceBetween, dialSize, dialSize);
    band1QDial.setBounds(band1CutoffDial.getX() + band1CutoffDial.getWidth(), band1CutoffDial.getY(), dialSize, dialSize);
    
    band2GainDial.setBounds(leftMargin * groupSpace, topMargin, dialSize, dialSize);
    band2CutoffDial.setBounds(band2GainDial.getX() - band1GainDial.getWidth() * 0.5, band1GainDial.getY() + band1GainDial.getHeight() * spaceBetween, dialSize, dialSize);
    band2QDial.setBounds(band2CutoffDial.getX() + band2CutoffDial.getWidth(), band2CutoffDial.getY(), dialSize, dialSize);
    groupSpace += groupSpaceOffset;
    
    band3GainDial.setBounds(leftMargin * groupSpace, topMargin, dialSize, dialSize);
    band3CutoffDial.setBounds(band3GainDial.getX() - band1GainDial.getWidth() * 0.5, band1GainDial.getY() + band1GainDial.getHeight() * spaceBetween, dialSize, dialSize);
    band3QDial.setBounds(band3CutoffDial.getX() + band3CutoffDial.getWidth(), band3CutoffDial.getY(), dialSize, dialSize);
    groupSpace += groupSpaceOffset;
    
    band4GainDial.setBounds(leftMargin * groupSpace, topMargin, dialSize, dialSize);
    band4CutoffDial.setBounds(band4GainDial.getX() - band1GainDial.getWidth() * 0.5, band1GainDial.getY() + band1GainDial.getHeight() * spaceBetween, dialSize, dialSize);
    band4QDial.setBounds(band4CutoffDial.getX() + band4CutoffDial.getWidth(), band4CutoffDial.getY(), dialSize, dialSize);
    groupSpace += groupSpaceOffset;
    
    band5GainDial.setBounds(leftMargin * groupSpace, topMargin, dialSize, dialSize);
    band5CutoffDial.setBounds(band5GainDial.getX() - band1GainDial.getWidth() * 0.5, band1GainDial.getY() + band1GainDial.getHeight() * spaceBetween, dialSize, dialSize);
    band5QDial.setBounds(band5CutoffDial.getX() + band5CutoffDial.getWidth(), band5CutoffDial.getY(), dialSize, dialSize);
    groupSpace += groupSpaceOffset;
    
    band6GainDial.setBounds(leftMargin * groupSpace, topMargin, dialSize, dialSize);
    band6CutoffDial.setBounds(band6GainDial.getX() - band1GainDial.getWidth() * 0.5, band1GainDial.getY() + band1GainDial.getHeight() * spaceBetween, dialSize, dialSize);
    band6QDial.setBounds(band6CutoffDial.getX() + band6CutoffDial.getWidth(), band6CutoffDial.getY(), dialSize, dialSize);
    groupSpace += groupSpaceOffset;
    
    band7GainDial.setBounds(leftMargin * groupSpace, topMargin, dialSize, dialSize);
    band7CutoffDial.setBounds(band7GainDial.getX() - band1GainDial.getWidth() * 0.5, band1GainDial.getY() + band1GainDial.getHeight() * spaceBetween, dialSize, dialSize);
    band7QDial.setBounds(band7CutoffDial.getX() + band7CutoffDial.getWidth(), band7CutoffDial.getY(), dialSize, dialSize);
    
    const auto labelX = getWidth() * 0.018;
    const auto labelY = getHeight() * 0.43;
    const auto labelW = getWidth() * 0.1;
    const auto labelH = labelW * 0.5;
    
    graphLabel100.setBounds(labelX, labelY, labelW, labelH);
    auto space1 = graphLabel100.getX() * 2.68;
    
    graphLabel250.setBounds(space1, labelY, labelW, labelH);
    auto space2 = graphLabel100.getX() * 5.28;
    
    graphLabel500.setBounds(space2, labelY, labelW, labelH);
    auto space3 = graphLabel100.getX() * 10.27;
    
    graphLabel1000.setBounds(space3, labelY, labelW, labelH);
    auto space4 = graphLabel1000.getX() * 1.84;
    
    graphLabel2000.setBounds(space4, labelY, labelW, labelH);
    auto space5 = graphLabel2000.getX() * 1.7;
    
    graphLabel4000.setBounds(space5, labelY, labelW, labelH);
    auto space6 = graphLabel4000.getX() * 1.453;
    
    graphLabel8000.setBounds(space6, labelY, labelW, labelH);
    auto space7 = graphLabel8000.getX() * 1.123;
    
    graphLabel14000.setBounds(space7, labelY, labelW, labelH);
}

void ParaEQDemoAudioProcessorEditor::drawFrame (juce::Graphics& g)
{
    for (int i = 1; i < audioProcessor.scopeSize; ++i)
    {
        auto width  = m_analyzerBounds.toNearestInt().getWidth();
        auto height = m_analyzerBounds.toNearestInt().getHeight();

        g.setColour(juce::Colours::green);
        g.drawLine ({ (float) juce::jmap (i - 1, 0, audioProcessor.scopeSize - 1, 0, width),
                              juce::jmap (audioProcessor.scopeData[i - 1], 0.0f, 1.0f, (float) height, 0.0f),
                      (float) juce::jmap (i,     0, audioProcessor.scopeSize - 1, 0, width),
                              juce::jmap (audioProcessor.scopeData[i],     0.0f, 1.0f, (float) height, 0.0f) });
        DBG(audioProcessor.scopeData[i]);
    }
}
