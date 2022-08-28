/*
  ==============================================================================

    SettingsPage.h
    Created: 13 Jun 2022 3:11:30pm
    Author:  Landon Viator

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "../../PluginProcessor.h"
#include "../../Parameters/Globals.h"

//==============================================================================
/*
*/
class SettingsPage  : public juce::Component
{
public:
    SettingsPage(LVTemplateAudioProcessor&);
    ~SettingsPage() override;

    void paint (juce::Graphics&) override;
    void resized() override;
    enum class Theme
    {
        kDracula,
        kPrimeDark,
        kTokyoLofi,
        kWinter,
        kFoxy,
        kPurp,
        kDull
    };
    Theme getPluginTheme();
    bool getGradientState();

private:
    
    LVTemplateAudioProcessor& audioProcessor;
    
    /** Menus */
    juce::ComboBox m_themeMenu;
    void setMenuProps(juce::ComboBox& menu);
    void setThemeMenuProps();
    
    /** Theme */
    Theme m_pluginTheme = Theme::kDracula;
    void setPluginTheme(Theme newTheme);
    
    /** =============== Buttons ===============*/
    
    // Gradient
    juce::TextButton m_gradientToggle;
    void setGradientToggleProps();
    
    // Discord link
    juce::TextButton m_discord;
    void setDiscordBtnProps();
    juce::HyperlinkButton m_discordLink;
    juce::URL m_discordUrl {"https://discord.gg/zcmjABjVn8"};
    
    // Patreon link
    juce::TextButton m_patreon;
    void setPatreonBtnProps();
    juce::HyperlinkButton m_patreonLink;
    juce::URL m_patreonUrl {"https://www.patreon.com/ViatorDSP?fan_landing=true"};
    
    // Twitch link
    juce::TextButton m_twitch;
    void setTwitchBtnProps();
    juce::HyperlinkButton m_twitchLink;
    juce::URL m_twitchUrl {"https://www.twitch.tv/dr_bruisin"};
    
    void setTextButtonProps(juce::TextButton& button);
    
    std::vector<juce::TextButton*> buttons =
    {
        &m_gradientToggle, &m_discord, &m_patreon, &m_twitch
    };
    
    /** Groups */
    juce::GroupComponent m_themeGroup;
    void setGroupProps(juce::GroupComponent& group);
    std::vector<juce::GroupComponent*> groups =
    {
        &m_themeGroup
    };
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (SettingsPage)
};
