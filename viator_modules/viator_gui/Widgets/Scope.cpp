#include "Scope.h"

namespace viator_gui
{

Scope::Scope(int numChannels)
{
    scopeModule = std::make_unique<juce::AudioVisualiserComponent>(numChannels);
    
    scopeModule->setColours(juce::Colours::black, juce::Colours::purple);
    scopeModule->setRepaintRate(10);
    addAndMakeVisible(*scopeModule);
    
    setSliderProps(sampleDial);
    setSliderProps(bufferDial);
    setSliderProps(repaintDial);
    
    sampleDial.onValueChange = [this]()
    {
        scopeModule->setSamplesPerBlock(sampleDial.getValue());
    };
    
    bufferDial.onValueChange = [this]()
    {
        scopeModule->setBufferSize(bufferDial.getValue());
    };
    
    repaintDial.onValueChange = [this]()
    {
        scopeModule->setRepaintRate(repaintDial.getValue());
    };
    
    sampleDial.setValue(32.0);
    bufferDial.setValue(128.0);
    repaintDial.setValue(2.0);
}

Scope::~Scope()
{
}

void Scope::paint (juce::Graphics& g)
{
}

void Scope::resized()
{
    scopeModule->setBounds(0, 0, getWidth() * 0.75, getHeight());
    
    auto dialX = scopeModule->getRight() - getWidth() * 0.04;
    auto dialY = scopeModule->getY();
    auto dialSize = getHeight() * 0.33;
    
    sampleDial.setBounds(dialX, dialY, dialSize, dialSize);
    dialY += dialSize;
    bufferDial.setBounds(dialX, dialY, dialSize, dialSize);
    dialY += dialSize;
    repaintDial.setBounds(dialX, dialY, dialSize, dialSize);
}

void Scope::setSliderProps(juce::Slider &dial)
{
    dial.setSliderStyle(juce::Slider::SliderStyle::RotaryVerticalDrag);
    dial.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 64, 32);
    dial.setRange(1.0, 1024.0, 1.0);
    addAndMakeVisible(dial);
}

void Scope::fillBuffer(juce::AudioBuffer<float> &buffer)
{
    scopeModule->pushBuffer(buffer);
}

void Scope::setSamplesPerBlock(float samplesPerBlock)
{
    scopeModule->setSamplesPerBlock(samplesPerBlock);
}

void Scope::setBufferSize(float samplesPerBlock)
{
    scopeModule->setBufferSize(samplesPerBlock);
}


} // viator_gui
