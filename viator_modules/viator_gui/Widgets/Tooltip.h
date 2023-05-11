#pragma once

namespace viator_gui
{

class TooltipWindow : public juce::TooltipWindow
{
public:
    TooltipWindow();

    juce::String getTipFor(juce::Component& c) override;
    void enableTooltips(const bool shouldShow);
    
private:
    int _millisecondsBeforeTipAppears = 700;
    bool _shouldShowTooltips = true;
};
} // namespace
