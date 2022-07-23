/*
  ==============================================================================

    Header.cpp
    Created: 17 Jul 2022 2:46:42pm
    Author:  Landon Viator

  ==============================================================================
*/

#include <JuceHeader.h>
#include "Header.h"

//==============================================================================
Header::Header(LVTemplateAudioProcessor& p) : audioProcessor(p)
{
    // Init settings button
    setSettingsButtonProps();
    
    // Init preset Browser
    setPresetBrowserItems();
}

Header::~Header()
{
    _settingsButton.setLookAndFeel(nullptr);
    _presetBrowser.setLookAndFeel(nullptr);
}

void Header::paint (juce::Graphics& g)
{
    // Init Header
    g.setColour(juce::Colours::black.withAlpha(0.2f));
    g.fillRect(0, 0, getWidth(), getHeight());
    g.setColour(juce::Colours::black.withAlpha(0.1f));
    g.drawLine(0, getHeight(), getWidth(), getHeight(), 1.0);
    g.setColour(juce::Colours::black);
    
    // Init logo
    auto headerLogo = juce::ImageCache::getFromMemory(BinaryData::landon5504_png, BinaryData::landon5504_pngSize);
    g.drawImageWithin(headerLogo,
                      getWidth() * 0.02,
                      0,
                      getWidth() * 0.17,
                      getHeight(),
                      juce::RectanglePlacement::centred);
    
    // Init buttons with colors for color change update
    for (auto& button : buttons)
    {
        setTextButtonProps(*button);
    }
    
    // Menu color update
    setPresetBrowserProps();
}

void Header::resized()
{
    // Position settings button
    float rightMargin = getWidth() * 0.95f;
    float headerTopMargin = getHeight() * 0.125f;
    float buttonWidth = getWidth() * 0.04;
    float buttonHeight = getHeight() * 0.75f;
    
    _settingsButton.setBounds(rightMargin, headerTopMargin, buttonWidth, buttonHeight);
    
    auto presetWidth = getWidth() * 0.15;
    auto presetHeight = getWidth() * 0.03;
    _presetBrowser.setBounds(getLocalBounds().withSizeKeepingCentre(presetWidth, presetHeight));

    // Position settings page
    setSettingsButtonProps();
}

void Header::setSettingsButtonProps()
{
    _settingsButton.setComponentID("settings");
    _settingsButton.onClick = [this]()
    {
        getParentComponent()->resized();
        getParentComponent()->repaint();
    };
}

bool Header::showSettings()
{
    return _settingsButton.getToggleState();
}

void  Header::setTextButtonProps(juce::TextButton &button)
{
    addAndMakeVisible(button);
    button.setClickingTogglesState(true);
    
    button.setColour(juce::ComboBox::outlineColourId, m_textAccentColor);
    button.setColour(juce::TextButton::ColourIds::textColourOnId, m_textAccentColor);
    button.setColour(juce::TextButton::ColourIds::textColourOffId, m_textAccentColor);
    button.setColour(juce::TextButton::ColourIds::buttonColourId, m_mainCompColor);
    button.setColour(juce::TextButton::ColourIds::buttonOnColourId, m_mainCompColor);
    button.setLookAndFeel(&customButtonLAF);
}

void Header::setPresetBrowserProps()
{
    addAndMakeVisible(_presetBrowser);
    _presetBrowser.setColour(juce::ComboBox::ColourIds::backgroundColourId, juce::Colours::transparentBlack);
    _presetBrowser.setColour(juce::ComboBox::ColourIds::outlineColourId, m_mainCompColor.withAlpha(0.4f));
    _presetBrowser.setColour(juce::ComboBox::ColourIds::focusedOutlineColourId, juce::Colours::transparentBlack);
    _presetBrowser.setColour(juce::ComboBox::ColourIds::textColourId, m_textColor);
    _presetBrowser.setColour(juce::ComboBox::ColourIds::arrowColourId, m_textColor);

    _presetBrowser.getLookAndFeel().setColour(juce::PopupMenu::backgroundColourId, m_mainCompColor.withAlpha(0.8f));
    _presetBrowser.getLookAndFeel().setColour(juce::PopupMenu::highlightedBackgroundColourId, m_mainCompColor);
    _presetBrowser.getLookAndFeel().setColour(juce::PopupMenu::textColourId, m_textColor);
    _presetBrowser.getLookAndFeel().setColour(juce::PopupMenu::highlightedTextColourId, m_bgLighterColor);
    
    _presetBrowser.setLookAndFeel(&_customMenu);
}

void Header::setPresetBrowserItems()
{
    _presetBrowser.setTextWhenNothingSelected("Presets");
    _presetBrowser.addItem("Lofi Room", 1);
    //presetMenuAttach = std::make_unique<juce::AudioProcessorValueTreeState::ComboBoxAttachment>(audioProcessor.m_treeState, presetID, m_presetBrowser);

    _presetBrowser.onChange = [this]()
    {
        switch (_presetBrowser.getSelectedItemIndex())
        {
            case 0:
            {
                setPreset(-12.0f, 12.0f); break;
            }
        }
    };
}

void Header::setPreset(float input, float output)
{
    audioProcessor._treeState.getParameterAsValue(inputID) = input;
    audioProcessor._treeState.getParameterAsValue(outputID) = output;
}
