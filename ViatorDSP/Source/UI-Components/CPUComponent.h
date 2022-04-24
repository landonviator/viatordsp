#pragma once
#include <JuceHeader.h>

#include "../PluginProcessor.h"

class CPUComponent : public juce::Component
{
    public:
        
         CPUComponent(ViatorDSPAudioProcessor& p);
        ~CPUComponent() override;
        
        void paint(juce::Graphics& g) override;
        
        void resized() override;
            
        void updateLabel(juce::String newText);
        
    private:
        
        ViatorDSPAudioProcessor& audioProcessor;
        
        viator_gui::Label cpuLabel {false, "CPU"};
        viator_gui::Label cpuHeader {true, "CPU"};
        viator_gui::LEDButton cpuButton;
        
        float topHeaderMargin;
        
        std::unique_ptr <juce::AudioProcessorValueTreeState::ButtonAttachment> cpuButtonAttach;
        
};
