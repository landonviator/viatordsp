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
    class CustomAbleDialLAF : public LookAndFeel_V4
    {
        
    public:
        
        CustomAbleDialLAF(bool isStereoDial);
        
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
        float sliderWidth;
        
    private:
        
        float stereoDialScalar = 1.0;
    };

    /** Alpha Dial Style*/
    class AlphaDialLAF : public juce::LookAndFeel_V4
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
        float sliderWidth;
    };

    /** Hard Dial Style*/
    class HardDialLAF : public juce::LookAndFeel_V4
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
        float sliderWidth;
    };

/** Full Dial Style*/
class FullDialLAF : public juce::LookAndFeel_V4
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
    float sliderWidth;
    
private:
    juce::DropShadow shadowProperties;
    juce::DropShadowEffect dialShadow;

};

/** Full Dial Mirrow Style*/
class FullDialMirrowLAF : public juce::LookAndFeel_V4
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
    float sliderWidth;

};

    /** Number Box Style*/
    class CustomNumberBox : public juce::LookAndFeel_V4
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
        float sliderWidth;
    };

    /** Push Button Style*/
    class CustomPushButton : public juce::LookAndFeel_V4
    {
        
    public:
        
        void drawButtonText (Graphics& g, TextButton& button,
                             bool /*shouldDrawButtonAsHighlighted*/, bool /*shouldDrawButtonAsDown*/) override;
    };

    /** Fader Style*/
    class FaderLAF : public LookAndFeel_V4
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
        float sliderHeight;
        float sliderWidth;
        
    private:
        
        juce::String sliderFont {"Helvetica"};
        
    };

    /** Phase Button Style*/
    class PhaseToggleLAF : public LookAndFeel_V4
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
    class PowerToggleLAF : public LookAndFeel_V4
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
    class CustomBorder : public LookAndFeel_V2
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
    class Custom_Menu : public LookAndFeel_V4
    {
        void positionComboBoxText (ComboBox& box, Label& label) override;
    };

    /** Fader Style*/
    class WindowSliderLAF : public LookAndFeel_V4
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
        
    };
}
