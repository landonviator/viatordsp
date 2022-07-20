/*
  ==============================================================================

    SettingsPage.cpp
    Created: 13 Jun 2022 3:11:30pm
    Author:  Landon Viator

  ==============================================================================
*/

#include <JuceHeader.h>
#include "SettingsPage.h"

//==============================================================================
SettingsPage::SettingsPage(LVTemplateAudioProcessor& p) : audioProcessor(p)
{
    setMenuProps(m_themeMenu);
    setThemeMenuProps();
    setGlowSliderProps();
    
    m_themeGroup.setText("Plugin Color Themes");
    _uiTypeGroup.setText("GUI Style");
    
    /** Buttons */
    for (auto& button : buttons)
    {
        setTextButtonProps(*button);
    }
    
    _skueomorphic.setToggleState(true, juce::dontSendNotification);
    _skueomorphic.onStateChange = [this]()
    {
        getParentComponent()->resized();
    };
    
//    _flat.onStateChange = [this]()
//    {
//        getParentComponent()->resized();
//    };
    
    /** Groups */
    for (auto& group : groups)
    {
        setGroupProps(*group);
    }
    
    _skueomorphic.setButtonText("Real");
    _skueomorphic.setRadioGroupId(1);
    
    _flat.setButtonText("Flat");
    _flat.setRadioGroupId(1);
}

SettingsPage::~SettingsPage()
{
}

void SettingsPage::paint (juce::Graphics& g)
{
    g.fillAll(juce::Colours::black.withAlpha(0.5f));
    
    /** Buttons */
    for (auto& button : buttons)
    {
        setTextButtonProps(*button);
    }
}

void SettingsPage::resized()
{
    /** Glow Toggle */
    const auto contentX = getWidth() * 0.1;
    const auto contentY = getHeight() * 0.06;
    m_glowToggle.setBounds(contentX * 1.47, contentY * 1.6, getWidth() * 0.2, getHeight() * 0.05);
    m_glowSlider.setBounds(m_glowToggle.getX() + m_glowToggle.getWidth() * 1.34, m_glowToggle.getY(), m_glowToggle.getWidth() * 2.3, m_glowToggle.getHeight());
    
    /** Theme Menu and Gradient Toggle */
    const auto buttonX = m_glowToggle.getX();
    const auto buttonY = m_glowToggle.getY();
    const auto buttonWidth = m_glowToggle.getWidth();
    const auto buttonHeight = m_glowToggle.getHeight();
    m_gradientToggle.setBounds(buttonX, buttonY + buttonHeight * 1.5, buttonWidth, buttonHeight);
    m_themeMenu.setBounds(m_glowToggle.getX() + m_glowToggle.getWidth() * 1.55, m_gradientToggle.getY(), m_glowToggle.getWidth() * 2.0, m_glowToggle.getHeight());
    m_themeGroup.setBounds(m_glowToggle.getX() * 0.57, m_glowToggle.getY() * 0.65, m_themeMenu.getX() + m_themeMenu.getWidth(), m_gradientToggle.getY() + m_gradientToggle.getHeight() * 0.38);
    
    /** UI Type */
    _uiTypeGroup.setBounds(m_themeGroup.getX(),
                           m_themeGroup.getY() + m_themeGroup.getHeight() + buttonHeight,
                           m_themeGroup.getWidth() * 0.68,
                           m_themeGroup.getHeight() * 0.75);
    
    _skueomorphic.setBounds(m_glowToggle.getX(), _uiTypeGroup.getY() + _uiTypeGroup.getHeight() * 0.36, buttonWidth, buttonHeight);
    _flat.setBounds(_skueomorphic.getX() + _skueomorphic.getWidth() * 1.28, _skueomorphic.getY(), buttonWidth, buttonHeight);
    
    /** Social Toggles */
    m_discord.setBounds(buttonX, buttonY * 9.0, buttonWidth, buttonHeight);
    m_patreon.setBounds(m_discord.getX() + m_discord.getWidth() * 1.5, m_discord.getY(), buttonWidth, buttonHeight);
    m_twitch.setBounds(m_patreon.getX() + m_patreon.getWidth() * 1.5, m_discord.getY(), buttonWidth, buttonHeight);
}

SettingsPage::Theme SettingsPage::getPluginTheme()
{
    return m_pluginTheme;
}

void SettingsPage::setPluginTheme(Theme newTheme)
{
    m_pluginTheme = newTheme;
}

bool SettingsPage::getGlowState()
{
    return m_glowToggle.getToggleState();
}

bool SettingsPage::getGradientState()
{
    return m_gradientToggle.getToggleState();
}

bool SettingsPage::getUIType()
{
    return _skueomorphic.getToggleState();
}

float SettingsPage::getCurrentGlowValue()
{
    return _currentGlowValue;
}

void SettingsPage::setTextButtonProps(juce::TextButton &button)
{
    addAndMakeVisible(button);
    button.setClickingTogglesState(true);
    button.setColour(juce::ComboBox::outlineColourId, juce::Colours::transparentBlack);
    button.setColour(juce::TextButton::ColourIds::textColourOnId, juce::Colours::whitesmoke);
    button.setColour(juce::TextButton::ColourIds::textColourOffId, juce::Colours::whitesmoke.withAlpha(0.5f));
    button.setColour(juce::TextButton::ColourIds::buttonColourId, juce::Colour::fromRGB(53, 55, 70));
    button.setColour(juce::TextButton::ColourIds::buttonOnColourId, m_mainCompColor.withAlpha(0.5f));
    
    /** Individual Button Props */
    setGlowButtonProps();
    setGradientToggleProps();
    setDiscordBtnProps();
    setPatreonBtnProps();
    setTwitchBtnProps();
}

void SettingsPage::setDiscordBtnProps()
{
    m_discord.setButtonText("Discord");
    m_discord.setClickingTogglesState(false);
    
    // Discord link
    m_discordLink.setURL(m_discordUrl);
    addAndMakeVisible(m_discordLink);
    
    m_discord.onClick = [this]()
    {
        m_discordLink.triggerClick();
    };
}

void SettingsPage::setPatreonBtnProps()
{
    m_patreon.setButtonText("Patreon");
    m_patreon.setClickingTogglesState(false);
    
    // Patreon link
    m_patreonLink.setURL(m_patreonUrl);
    addAndMakeVisible(m_patreonLink);
    
    m_patreon.onClick = [this]()
    {
        m_patreonLink.triggerClick();
    };
}

void SettingsPage::setTwitchBtnProps()
{
    m_twitch.setButtonText("Twitch");
    m_twitch.setClickingTogglesState(false);
    
    // Twitch link
    m_twitchLink.setURL(m_twitchUrl);
    addAndMakeVisible(m_twitchLink);
    
    m_twitch.onClick = [this]()
    {
        m_twitchLink.triggerClick();
    };
}

void SettingsPage::setGlowButtonProps()
{
    m_glowToggle.setButtonText("Glow");
    m_glowToggle.setToggleState(audioProcessor.variableTree.getProperty("glowtoggle"), juce::dontSendNotification);
    m_glowToggle.onClick = [this]()
    {
        audioProcessor.variableTree.setProperty("glowtoggle",
                                                m_glowToggle.getToggleState(), nullptr);
        getParentComponent()->repaint();
    };
}

void SettingsPage::setGlowSliderProps()
{
    addAndMakeVisible(m_glowSlider);
    m_glowSlider.setSliderStyle(juce::Slider::SliderStyle::LinearHorizontal);
    m_glowSlider.setTextBoxStyle(juce::Slider::TextBoxLeft, false, 64, 32);
    m_glowSlider.setColour(juce::Slider::ColourIds::trackColourId, juce::Colour::fromRGB(53, 55, 70));
    m_glowSlider.setColour(juce::Slider::ColourIds::textBoxOutlineColourId, juce::Colours::transparentBlack);
    m_glowSlider.setColour(juce::Slider::ColourIds::textBoxTextColourId, juce::Colours::whitesmoke);
    m_glowSlider.setColour(juce::Slider::ColourIds::thumbColourId, juce::Colour::fromRGB(53, 55, 70));
    m_glowSlider.setColour(juce::Slider::ColourIds::backgroundColourId, juce::Colours::black);
    m_glowSlider.setDoubleClickReturnValue(true, 1.0);
    m_glowSlider.setRange(0.0, 1.0, 0.01);
    m_glowSlider.setValue(audioProcessor.variableTree.getProperty("glowslider"));
    
    m_glowSlider.onValueChange = [this]()
    {
        _currentGlowValue = m_glowSlider.getValue();
        audioProcessor.variableTree.setProperty("glowslider", m_glowSlider.getValue(), nullptr);
        getParentComponent()->repaint();
    };
}

void SettingsPage::setGradientToggleProps()
{
    m_gradientToggle.setButtonText("Gradient");
    m_gradientToggle.setToggleState(audioProcessor.variableTree.getProperty("gradienttoggle"), juce::dontSendNotification);
    m_gradientToggle.onClick = [this]()
    {
        audioProcessor.variableTree.setProperty("gradienttoggle",
                                                m_gradientToggle.getToggleState(), nullptr);
        getParentComponent()->repaint();
    };
}

void SettingsPage::setGroupProps(juce::GroupComponent &group)
{
    addAndMakeVisible(group);
    group.setColour(juce::GroupComponent::ColourIds::outlineColourId, juce::Colours::whitesmoke.withAlpha(0.2f));
    group.setColour(juce::GroupComponent::ColourIds::textColourId, juce::Colours::whitesmoke.withAlpha(0.2f));
}

void SettingsPage::setMenuProps(juce::ComboBox &menu)
{
    addAndMakeVisible(menu);
    menu.setColour(juce::ComboBox::ColourIds::backgroundColourId, juce::Colour::fromRGB(53, 55, 70));
    menu.setColour(juce::ComboBox::ColourIds::outlineColourId, juce::Colours::whitesmoke.withAlpha(0.0f));
    menu.setColour(juce::ComboBox::ColourIds::focusedOutlineColourId, juce::Colours::black.withAlpha(0.5f));
    menu.setColour(juce::ComboBox::ColourIds::textColourId, juce::Colours::whitesmoke.withAlpha(0.5f));
    menu.setColour(juce::ComboBox::ColourIds::arrowColourId, juce::Colours::whitesmoke.withAlpha(0.5f));

    menu.getLookAndFeel().setColour(juce::PopupMenu::backgroundColourId, juce::Colour::fromRGB(53, 55, 70));
    menu.getLookAndFeel().setColour(juce::PopupMenu::highlightedBackgroundColourId, juce::Colours::skyblue.withAlpha(0.1f));
    menu.getLookAndFeel().setColour(juce::PopupMenu::textColourId, juce::Colours::whitesmoke.withAlpha(0.5f));
    menu.getLookAndFeel().setColour(juce::PopupMenu::highlightedTextColourId, juce::Colours::whitesmoke.withAlpha(0.5f));

    menu.setJustificationType(juce::Justification::centred);
}

void SettingsPage::setThemeMenuProps()
{
    m_themeMenu.setText("Themes");
    m_themeMenu.setTextWhenNothingSelected("Themes");
    m_themeMenu.addSectionHeading("Dark");
    m_themeMenu.addItem("Dracula", 1);
    m_themeMenu.addItem("Prime Dark", 2);
    m_themeMenu.addItem("Tokyo Lofi", 3);
    m_themeMenu.addItem("Winter", 4);
    m_themeMenu.addItem("Foxy", 5);
    m_themeMenu.addItem("Purp", 6);
    m_themeMenu.addItem("Dull", 7);
    m_themeMenu.onChange = [this]()
    {
        switch (m_themeMenu.getSelectedItemIndex())
        {
            case 0:
            {
                setPluginTheme(Theme::kDracula);
                getParentComponent()->repaint();
                audioProcessor.variableTree.setProperty("colortheme", 0, nullptr);
                break;
            }
                
            case 1:
            {
                setPluginTheme(Theme::kPrimeDark);
                getParentComponent()->repaint();
                audioProcessor.variableTree.setProperty("colortheme", 1, nullptr);
                break;
            }
                
            case 2:
            {
                setPluginTheme(Theme::kTokyoLofi);
                getParentComponent()->repaint();
                audioProcessor.variableTree.setProperty("colortheme", 2, nullptr);
                break;
            }
                
            case 3:
            {
                setPluginTheme(Theme::kWinter);
                getParentComponent()->repaint();
                audioProcessor.variableTree.setProperty("colortheme", 3, nullptr);
                break;
            }
                
            case 4:
            {
                setPluginTheme(Theme::kFoxy);
                getParentComponent()->repaint();
                audioProcessor.variableTree.setProperty("colortheme", 4, nullptr);
                break;
            }
                
            case 5:
            {
                setPluginTheme(Theme::kPurp);
                getParentComponent()->repaint();
                audioProcessor.variableTree.setProperty("colortheme", 5, nullptr);
                break;
            }
                
            case 6:
            {
                setPluginTheme(Theme::kDull);
                getParentComponent()->repaint();
                audioProcessor.variableTree.setProperty("colortheme", 6, nullptr);
                break;
            }
        }
    };
    
    m_themeMenu.setSelectedItemIndex(static_cast<int>(audioProcessor.variableTree.getProperty("colortheme")));
}
