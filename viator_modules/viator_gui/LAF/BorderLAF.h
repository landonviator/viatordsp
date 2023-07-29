#pragma once

namespace viator_gui
{
    class CustomBorder : public juce::LookAndFeel_V4
    {
        public:
        CustomBorder();
        
        void drawGroupComponentOutline (juce::Graphics& g, int width, int height,
                                        const juce::String& text, const juce::Justification& position,
                                        juce::GroupComponent& group) override;
        
        
    private:
    };
}
