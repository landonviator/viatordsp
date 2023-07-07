#include "Fader.h"

namespace viator_gui
{

Meter::Meter()
{
    addAndMakeVisible(meter);
    meter.setSliderStyle(juce::Slider::SliderStyle::LinearVertical);
    meter.setTextBoxStyle(juce::Slider::NoTextBox, true, 0, 0);
    meter.setRange(-60.0, 0.0, 0.1);
    meter.setColour(juce::Slider::ColourIds::trackColourId, juce::Colours::white.withAlpha(0.5f));
    meter.setColour(juce::Slider::ColourIds::backgroundColourId, juce::Colours::black.withAlpha(0.5f));
    meter.setColour(juce::Slider::ColourIds::thumbColourId, juce::Colours::black.withAlpha(0.8f));
    meter.setLookAndFeel(&meterLAF);
    
    setInterceptsMouseClicks(false, false);
}

Meter::~Meter()
{
}

void Meter::paint (juce::Graphics& g)
{
    paintSliderLabelTrack(g);
}

void Meter::resized()
{
    meter.setBounds(0, 0, getWidth() * 0.5, getHeight());
}

void Meter::paintSliderLabelTrack(juce::Graphics &g)
{
    auto tickDividor = 3.0;
    auto numTicks = (meter.getMaximum() - meter.getMinimum()) / 3.0 + 1;
    auto currentMeterTick = 0.0;
    auto currentMeterTickY = 0.0;
    
    auto lineX = getWidth() * 0.5;
    auto textX = getWidth() * 0.6;
    
    g.setColour(viator_utils::gui_utils::Colors::_textColor);
    g.setFont(getWidth() * 0.25);
    auto textSize = getWidth() * 0.4;
    
    for (size_t tick = 0; tick < static_cast<int>(numTicks); tick++)
    {
        if (tick > 0)
        {
            currentMeterTick -= tickDividor;
        }
        
        currentMeterTickY = meter.getPositionOfValue(currentMeterTick);
        
        g.drawLine(lineX, currentMeterTickY, getWidth() * 0.6, currentMeterTickY, 1.0f);
        
        auto currentTickText = std::to_string(static_cast<int>(std::abs(currentMeterTick)));
        g.drawText(currentTickText, textX, currentMeterTickY - 6, textSize, 12, juce::Justification::centred);
    }
}

} // viator_gui
