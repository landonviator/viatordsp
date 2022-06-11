#pragma once
#include <JuceHeader.h>
#include "PluginProcessor.h"
#include "./GUI/LookAndFeel/PanelLAF.h"

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
    
    Theme m_pluginTheme = Theme::kDull;
    
    void setPluginTheme(Theme newTheme);
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (LVTemplateAudioProcessorEditor)
};
