/*
  ==============================================================================

    StyleSheet.h
    Created: 20 Jul 2021 6:38:58pm
    Author:  landon viator

  ==============================================================================
*/

#pragma once

namespace juce
{

    /** Custom Ableton-style dial*/
    class LV_CustomAbleDialLAF : public LookAndFeel_V4
    {
        
    public:
        
        LV_CustomAbleDialLAF(bool isStereoDial);
        
        void drawRotarySlider
        (
            Graphics &g,
            int x, int y,
            int width, int height, float sliderPos,
            float sliderPosProportional,
            float rotaryStartAngle,
            float rotaryEndAngle, Slider &slider
         );
        
        void setDialIsStereoDial(bool isStereoDial);
        
    private:
        
        float stereoDialScalar = 1.0;
    };

    /** Alpha Dial Style*/
    class LV_AlphaDialLAF : public juce::LookAndFeel_V4
    {
        
    public:
        
        void drawRotarySlider
        (
            Graphics &g,
            int x,
            int y,
            int width,
            int height,
            float sliderPos,
            float rotaryStartAngle,
            float rotaryEndAngle,
            Slider &slider
        ) override;
        
        void drawLabel (Graphics& g, Label& label) override;
    };

    /** Hard Dial Style*/
    class LV_HardDialLAF : public juce::LookAndFeel_V4
    {
        
    public:
        
        void drawRotarySlider
        (
            Graphics &g,
            int x,
            int y,
            int width,
            int height,
            float sliderPos,
            float rotaryStartAngle,
            float rotaryEndAngle,
            Slider &slider
        ) override;

        void drawLabel (Graphics& g, Label& label) override;
    };

    /** Number Box Style*/
    class LV_CustomNumberBox : public juce::LookAndFeel_V4
    {
        
    public:
        
        void drawLinearSlider
        (
            Graphics& g,
            int x,
            int y,
            int width,
            int height,
            float sliderPos,
            float minSliderPos,
            float maxSliderPos,
            const Slider::SliderStyle style, Slider& slider
         ) override;

        void drawLabel (Graphics& g, Label& label) override;
    };

    /** Push Button Style*/
    class LV_CustomPushButton : public juce::LookAndFeel_V4
    {
        
    public:
        
        void drawButtonText (Graphics& g, TextButton& button,
                             bool /*shouldDrawButtonAsHighlighted*/, bool /*shouldDrawButtonAsDown*/) override;
    };

    /** Fader Style*/
    class LV_FaderLAF : public LookAndFeel_V4
    {
    public:
        
        void drawLinearSlider
        (
            Graphics& g,
            int x,
            int y,
            int width,
            int height,
            float sliderPos,
            float minSliderPos,
            float maxSliderPos,
            const Slider::SliderStyle style,
            Slider& slider
         ) override;
        
        void drawLabel(Graphics &g, Label &label) override;
        
    private:
        
        juce::String sliderFont {"Helvetica"};
        
    };

    /** Phase Button Style*/
    class LV_PhaseToggleLAF : public LookAndFeel_V4
    {
        
    public:
        
        
        void drawToggleButton
        (
            juce::Graphics &g,
            juce::ToggleButton &toggleButton,
            bool shouldDrawButtonAsHighlighted,
            bool shouldDrawButtonAsDown
         ) override;
    };

    /** Power Button Style*/
    class LV_PowerToggleLAF : public LookAndFeel_V4
    {
        
    public:
        
        
        void drawToggleButton
        (
            juce::Graphics &g,
            juce::ToggleButton &toggleButton,
            bool shouldDrawButtonAsHighlighted,
            bool shouldDrawButtonAsDown
         ) override;
    };

    /** Border Style*/
    class LV_CustomBorder : public LookAndFeel_V2
    {
        public:
        
        void drawGroupComponentOutline
        (
            Graphics& g, int width, int height,
            const String& text, const Justification& position,
            GroupComponent& group
         ) override;
    };

    /** Menu Style*/
    class LV_Custom_Menu : public LookAndFeel_V4
    {
        void positionComboBoxText (ComboBox& box, Label& label) override;
    };
}
