#pragma once
#include <JuceHeader.h>
#include "PluginProcessor.h"
#include "./GUI/LookAndFeel/PanelLAF.h"
#include "./GUI/LookAndFeel/FullDial.h"
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
    juce::ComboBox m_themeMenu;
    
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
    
    /** Settings Page */
    SettingsPage m_settingsPage;
    
    std::vector<juce::TextButton*> buttons =
    {
        &m_settingsButton
    };
    
    /** Test Widgets */
    juce::Slider testDial1;
    juce::Slider testDial2;
    juce::Slider testDial3;
    juce::Slider testDial4;
    void setSliderProps(juce::Slider& slider);
    FullDialLAF customDialLAF;
    
    std::vector<juce::Slider*> sliders =
    {
        &testDial1, &testDial2, &testDial3, &testDial4
    };
    
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> driveAttach;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> threshAttach;
    
    /** Shadow */
    juce::DropShadow shadowProperties;
    juce::DropShadowEffect dialShadow;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (LVTemplateAudioProcessorEditor)
};
