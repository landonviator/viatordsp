#pragma once

namespace viator_gui
{
    class CustomDial : public juce::LookAndFeel_V4
    {
        public:
        CustomDial();
        
        void drawRotarySlider
        (
         juce::Graphics &g,
            int x,
            int y,
            int width,
            int height,
            float sliderPos,
            float rotaryStartAngle,
            float rotaryEndAngle,
         juce::Slider &slider
         ) override;
        
        void drawLabel (juce::Graphics& g, juce::Label& label) override;
        
        enum class ValueType
        {
            kInt,
            kFloat
        };
        
        ValueType getDialValueType()
        {
            return _dialValueType;
        }
        
        void setDialValueType(ValueType newValueType)
        {
            _dialValueType = newValueType;
        }
        
    private:

        float _sliderWidth;
        juce::String _sliderName = "";
        
        ValueType _dialValueType = ValueType::kFloat;
    };

class CustomDialLabel : public juce::LookAndFeel_V4
{
    public:
    CustomDialLabel();
    
    void drawLabel (juce::Graphics& g, juce::Label& label) override;
    
    enum class ValueType
    {
        kInt,
        kFloat
    };
    
    ValueType getDialValueType()
    {
        return _dialValueType;
    }
    
    void setDialValueType(ValueType newValueType)
    {
        _dialValueType = newValueType;
    }
    
private:

    float _sliderWidth;
    juce::String _sliderName = "";
    
    ValueType _dialValueType = ValueType::kFloat;
};
}
