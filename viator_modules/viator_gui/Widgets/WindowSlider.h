#pragma once

namespace viator_gui
{
    class WindowSlider  : public juce::Slider
    {
    public:
        WindowSlider();
        
        void resized() override;
        void setPopupPosition();
        
    private:
        
        void mouseMove (const juce::MouseEvent &) override;
        void mouseEnter (const juce::MouseEvent &) override;
        void mouseExit (const juce::MouseEvent &) override;
        
        juce::Label _minPopup;
        juce::Label _maxPopup;
    };
}
