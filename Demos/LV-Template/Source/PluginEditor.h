#pragma once
#include <JuceHeader.h>
#include "PluginProcessor.h"
#include "./GUI/LookAndFeel/PanelLAF.h"
#include "./GUI/LookAndFeel/FullDial.h"

//==============================================================================

class LVTemplateAudioProcessorEditor  :
public juce::AudioProcessorEditor
{
public:
    LVTemplateAudioProcessorEditor (LVTemplateAudioProcessor&);
    ~LVTemplateAudioProcessorEditor() override;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;
    
private:

    LVTemplateAudioProcessor& audioProcessor;
    
    /** Boiler plate UI stuff */
    void uiConstructor();
    void initWindow();
    void uiPaint(juce::Graphics &g);
    void uiResized();
    void saveWindowSize();
    bool constructorFinished = false;
    
    juce::GroupComponent panel;
    CustomPanel customPanelLAF;
    juce::GlowEffect glow;
    
    void setTextButtonProps(juce::TextButton& button);
    
    /** Header */
    juce::Rectangle<float> m_headerRectangle;
    juce::TextButton m_settingsButton;
    void setSettingsButtonProps();
    juce::Rectangle<float> m_settingsPage;
    juce::ComboBox m_themeMenu;
    void setMenuProps(juce::ComboBox& menu);
    void setThemeMenuProps();
    
    /** Theme */
    juce::Colour m_bgColor;
    juce::Colour m_bgLighterColor;
    juce::Colour m_textAccentColor;
    juce::Colour m_bgTransparent;
    juce::Colour m_mainCompColor;
    juce::Colour m_mainCompFillColor;
    
    enum class Theme
    {
        kDracula,
        kPrimeDark,
        kPrimeLight,
        kTokyoLofi,
        kTokyoLight,
        kWinter,
        kFoxy,
        kMaterialLight,
        kPurp,
        kDull
    };
    
    Theme m_pluginTheme = Theme::kDracula;
    
    void setPluginTheme(Theme newTheme);
    juce::TextButton m_glowToggle;
    void setGlowButtonProps();
    juce::GroupComponent m_themeGroup;
    void setGroupProps(juce::GroupComponent& group);
    void setThemePageResized();
    juce::TextButton m_gradientToggle;
    void setGradientToggleProps();
    
    //Discord link
    juce::TextButton m_discord;
    void setDiscordBtnProps();
    juce::HyperlinkButton m_discordLink;
    juce::URL m_discordUrl {"https://discord.gg/zcmjABjVn8"};
    
    //Patreon link
    juce::TextButton m_patreon;
    void setPatreonBtnProps();
    juce::HyperlinkButton m_patreonLink;
    juce::URL m_patreonUrl {"https://www.patreon.com/ViatorDSP?fan_landing=true"};
    
    //Twitch link
    juce::TextButton m_twitch;
    void setTwitchBtnProps();
    juce::HyperlinkButton m_twitchLink;
    juce::URL m_twitchUrl {"https://www.twitch.tv/dr_bruisin"};
    
    std::vector<juce::TextButton*> buttons =
    {
        &m_settingsButton, &m_glowToggle, &m_gradientToggle, &m_discord, &m_patreon, &m_twitch
    };
    
    /** Test Widgets */
    juce::Slider testDial;
    void setSliderProps(juce::Slider& slider);
    FullDialLAF customDialLAF;
    
    /** Shadow */
    juce::DropShadow shadowProperties;
    juce::DropShadowEffect dialShadow;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (LVTemplateAudioProcessorEditor)
};
