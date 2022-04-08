#pragma once

#include <JuceHeader.h>
#include "ThreadMethods.h"

//==============================================================================
/*
    This component lives inside our window, and this is where you should put all
    your controls and content.
*/
class MainComponent  : public juce::Component
{
public:
    //==============================================================================
    MainComponent();
    ~MainComponent() override;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;
    
    juce::Label label;
private:
    //==============================================================================
    // Your private member variables go here...
    juce::TextButton triggerButton;
    std::unique_ptr<juce::ProgressBar> meter;
    MeterThread meterThread;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MainComponent)
};
