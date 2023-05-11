#include <JuceHeader.h>

namespace viator_gui
{

TooltipWindow::TooltipWindow()
{
    setMillisecondsBeforeTipAppears(_millisecondsBeforeTipAppears);
}

juce::String TooltipWindow::getTipFor(juce::Component& c)
{
    if (!juce::ModifierKeys::currentModifiers.isAnyMouseButtonDown())
    {
        if (auto* ttc = dynamic_cast<juce::TooltipClient*> (&c))
        {
            if (! c.isCurrentlyBlockedByAnotherModalComponent())
            {
                if (_shouldShowTooltips)
                {
                    return ttc->getTooltip();
                }
                
                else
                {
                    return "";
                }
            }
        }
    }

    return {};
}

void TooltipWindow::enableTooltips(const bool shouldShow)
{
    _shouldShowTooltips = shouldShow;
}
} // namespace
