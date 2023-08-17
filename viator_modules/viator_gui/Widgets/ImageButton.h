#pragma once

namespace viator_gui
{
    class ImageButton  : public juce::Component
    {
    public:
        ImageButton(const juce::Image& offImage,
                    const juce::Image& onImage,
                    const juce::String& offText,
                    const juce::String& onText);
        ~ImageButton() override;

        void paint (juce::Graphics&) override;
        void resized() override;
        
        juce::ImageButton& getButton(){return button;};
        juce::Label& getLabel(){return btnLabel;};
        
        enum class ViatorButtonType
        {
            kLED,
            kDarkFlat,
            kLightFlat
        };
        
        void setButtonType(ViatorButtonType newBtnType){_btnType = newBtnType;};
        
    private:
        juce::ImageButton button;
        juce::String btnOffText = "";
        juce::String btnOnText = "";
        juce::String btnText = "";
        juce::Label btnLabel;
        
        ViatorButtonType _btnType = ViatorButtonType::kLED;
        
        juce::Colour _textOff = juce::Colours::whitesmoke.withAlpha(0.5f);
        juce::Colour _textOn = juce::Colours::black.withAlpha(0.5f);
        JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (ImageButton)
    };
}
