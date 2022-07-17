#pragma once
#include <JuceHeader.h>
#include "PluginProcessor.h"
#include "./GUI/LookAndFeel/PanelLAF.h"
#include "./GUI/LookAndFeel/FullDial.h"
#include "./GUI/LookAndFeel/Buttons.h"
#include "./GUI/Components/SettingsPage/SettingsPage.h"

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
    void getBGColor();
    
private:

    LVTemplateAudioProcessor& audioProcessor;
    
    /** Boiler plate UI stuff */
    void uiConstructor();
    void initWindow();
    void uiPaint(juce::Graphics &g);
    void uiResized();
    void saveWindowSize();
    bool constructorFinished = false;
    
    juce::GlowEffect glow;
    
    void setTextButtonProps(juce::TextButton& button);
    ButtonStyle customButtonLAF;
    
    /** Header */
    juce::Rectangle<float> m_headerRectangle;
    juce::TextButton m_settingsButton;
    void setSettingsButtonProps();
    juce::ComboBox m_themeMenu;
    
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
    
    Theme m_pluginTheme = Theme::kDracula;
    
    void setPluginTheme(Theme newTheme);
    
    /** Settings Page */
    SettingsPage m_settingsPage;
    
    std::vector<juce::TextButton*> buttons =
    {
        &m_settingsButton
    };
    
    /** ============================== Shadow ============================== */
    juce::DropShadow shadowProperties;
    juce::DropShadowEffect dialShadow;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (LVTemplateAudioProcessorEditor)
};
