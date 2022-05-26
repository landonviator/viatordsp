#include <JuceHeader.h>
#include "ToolTipSettingsComp.h"

//==============================================================================

ToolTipSettingsComp::ToolTipSettingsComp()
{
    /** Tooltip Toggle */
    addAndMakeVisible(toolTipToggle);
    toolTipToggle.setColour(juce::TextButton::ColourIds::buttonColourId, juce::Colours::transparentBlack);
    toolTipToggle.setColour(juce::TextButton::ColourIds::buttonOnColourId, juce::Colours::black.brighter(0.15));
    toolTipToggle.setColour(juce::ComboBox::ColourIds::outlineColourId, juce::Colours::whitesmoke.withAlpha(0.3f));
    toolTipToggle.setLookAndFeel(&customToggleButton);
    toolTipToggle.onClick = [this]()
    {
        shouldUseToolTips = toolTipToggle.getToggleState();
    };
    
    /** Tooltip Label */
    addAndMakeVisible(tooltipLabel);
    tooltipLabel.setText("Show Tool Tips?", juce::dontSendNotification);
    tooltipLabel.setColour(juce::Label::ColourIds::textColourId, juce::Colours::whitesmoke.withAlpha(0.5f));
}

ToolTipSettingsComp::~ToolTipSettingsComp()
{
    toolTipToggle.setLookAndFeel(nullptr);
}

void ToolTipSettingsComp::paint (juce::Graphics& g)
{
    g.setColour(juce::Colours::whitesmoke.withAlpha(0.15f));
    g.fillRoundedRectangle(getWidth() * 0.05, getHeight() * 0.05, getWidth() * 0.9, getHeight() * 0.9, 2.0f);
    
    g.setColour(juce::Colours::black.withAlpha(0.3f));
    g.drawRoundedRectangle(getWidth() * 0.05, getHeight() * 0.05, getWidth() * 0.9, getHeight() * 0.9, 2.0f, 2.0f);
}

void ToolTipSettingsComp::resized()

{
    auto leftMargin = getWidth() * 0.1;
    auto topMargin = getHeight() * 0.2f;
    auto compWidth = getWidth() * 0.1;
    auto compHeight = getHeight() * 0.6;
    
    toolTipToggle.setBounds(leftMargin, topMargin, compWidth, compHeight);
    tooltipLabel.setBounds(toolTipToggle.getX() + toolTipToggle.getWidth() * 1.3f, topMargin * 1.2f, compWidth * 4.0, compHeight);
    tooltipLabel.setFont(juce::Font ("Helvetica", getWidth() * 0.04f, juce::Font::FontStyleFlags::bold));
}

bool ToolTipSettingsComp::getShouldUseToolTips()
{
    return shouldUseToolTips;
}
