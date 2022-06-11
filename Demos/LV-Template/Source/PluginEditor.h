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
    
    juce::Colour m_bgColor = juce::Colour::fromRGB(40, 42, 53);
    juce::Colour m_bgLighterColor = juce::Colour::fromRGB(53, 55, 70);
    juce::Colour m_textAccentColor = juce::Colour::fromRGB(96, 110, 157);
    juce::Colour m_bgTransparent = juce::Colours::black.withAlpha(0.5f);
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (LVTemplateAudioProcessorEditor)
};
