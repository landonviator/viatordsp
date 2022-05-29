#pragma once
#include <JuceHeader.h>
#include "../LookAndFeel/MenuSliderLAF.h"
#include "../LookAndFeel/ToggleButtonLAF.h"
#include "../LookAndFeel/LabelLAF.h"
#include "../LookAndFeel/ColorButtonLAF.h"
#include "../Globals.h"
#include "SettingsComps/ToolTipSettingsComp.h"
#include "SettingsComps/MasterColorComp.h"

//==============================================================================

class SettingsPage  : public juce::Component
{
public:
    SettingsPage();
    ~SettingsPage() override;

    void paint (juce::Graphics&) override;
    void resized() override;
    bool getShouldUseToolTips();
private:
    
    juce::Slider menuSlider1;
    MenuSliderLAF customMenuSlider;
    
    ToolTipSettingsComp tooltipSettingsComp;
    MasterColorComp masterColorComp;
    
    LabelLAF customLabelLAF;
    
    float rowheight;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (SettingsPage)
};
