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
    
    /** Panels */
    juce::GroupComponent m_mainBorder;
    juce::GroupComponent m_distortionBorder;
    juce::GroupComponent m_crusherBorder;
    juce::GroupComponent m_toneBorder;
    juce::GroupComponent m_reverbBorder;
    juce::GroupComponent m_distortionTitle;
    juce::GroupComponent m_crusherTitle;
    juce::GroupComponent m_toneTitle;
    juce::GroupComponent m_reverbTitle;
    std::vector<juce::GroupComponent*> groups =
    {
        &m_mainBorder, &m_distortionBorder, &m_crusherBorder,
        &m_toneBorder, &m_reverbBorder, &m_distortionTitle, &m_crusherTitle,
        &m_toneTitle, &m_reverbTitle,
    };
    void setGroupProps(juce::GroupComponent& group);
    void setPanelLayout();
    void setDistortionGroupLayout();
    void setToneGroupLayout();
    
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
    juce::Colour m_textColor = juce::Colours::whitesmoke;
    
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
    
    /** ============================== Module Widgets ============================== */
    juce::Slider m_driveDial;
    juce::Slider m_mixDial;
    juce::Slider m_toneDial;
    juce::Slider m_cutoffDial;
    juce::Slider m_tiltSlider;
    viator_gui::Label m_driveLabel;
    viator_gui::Label m_driveMixLabel;
    
    void setSliderProps(juce::Slider& slider);
    void setDisSliderProps();
    
    FullDialLAF customDialLAF;
    ButtonStyle customButtonLAF;
    
    std::vector<viator_gui::Label*> disLabels =
    {
        &m_driveLabel, &m_driveMixLabel
    };
    
    void setDisLabelProps(viator_gui::Label& label);
    
    std::vector<juce::Slider*> disSliders =
    {
        &m_driveDial, &m_mixDial
    };
    
    std::vector<juce::Slider*> toneSliders =
    {
        &m_toneDial, &m_cutoffDial, &m_tiltSlider
    };
    
    void setToneSliderProps();
    
    std::unique_ptr<juce::AudioProcessorValueTreeState::ButtonAttachment> driveToggleAttach;
    std::unique_ptr<juce::AudioProcessorValueTreeState::ButtonAttachment> prepostToggleAttach;
    std::unique_ptr<juce::AudioProcessorValueTreeState::ButtonAttachment> toneToggleAttach;
    std::unique_ptr<juce::AudioProcessorValueTreeState::ComboBoxAttachment> driveMenuAttach;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> driveAttach;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> driveMixAttach;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> toneAttach;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> tiltAttach;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> cutoffAttach;
    
    /** ============================== Module Toggles ==============================*/
    viator_gui::Toggle m_distortionToggle;
    viator_gui::Toggle m_crusherToggle;
    viator_gui::Toggle m_toneToggle;
    viator_gui::Toggle m_reverbToggle;
    viator_gui::PushButton m_prepostButton;
    void setPrePostProps();
    
    std::vector<viator_gui::Toggle*> toggles =
    {
        &m_distortionToggle, &m_crusherToggle, &m_toneToggle, &m_reverbToggle
    };
    
    void setModuleToggleProps(viator_gui::Toggle& toggle);
    
    /** ============================== Module Labels ==============================*/
    viator_gui::Label m_distortionLabel;
    viator_gui::Label m_crusherLabel;
    viator_gui::Label m_toneLabel;
    viator_gui::Label m_reverbLabel;
    
    std::vector<viator_gui::Label*> moduleLabels =
    {
        &m_distortionLabel, &m_crusherLabel, &m_toneLabel, &m_reverbLabel
    };
    
    void setModuleLabelProps(juce::Label& label);
    
    /** ============================== Module Menus ==============================*/
    viator_gui::Menu m_distortionMenu;
    
    std::vector<viator_gui::Menu*> menus =
    {
        &m_distortionMenu
    };
    
    void setMenuProps(viator_gui::Menu& menu);
    void setDistortionMenuProps();
    
    /** ============================== Shadow ============================== */
    juce::DropShadow shadowProperties;
    juce::DropShadowEffect dialShadow;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (LVTemplateAudioProcessorEditor)
};
