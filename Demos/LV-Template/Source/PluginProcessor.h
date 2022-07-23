#pragma once
#include <JuceHeader.h>
#include "Parameters/Globals.h"

//==============================================================================
/**
*/
class LVTemplateAudioProcessor  : public juce::AudioProcessor, public juce::AudioProcessorValueTreeState::Listener
{
public:
    //==============================================================================
    LVTemplateAudioProcessor();
    ~LVTemplateAudioProcessor() override;

    //==============================================================================
    void prepareToPlay (double sampleRate, int samplesPerBlock) override;
    void releaseResources() override;

   #ifndef JucePlugin_PreferredChannelConfigurations
    bool isBusesLayoutSupported (const BusesLayout& layouts) const override;
   #endif

    void processBlock (juce::AudioBuffer<float>&, juce::MidiBuffer&) override;

    //==============================================================================
    juce::AudioProcessorEditor* createEditor() override;
    bool hasEditor() const override;

    //==============================================================================
    const juce::String getName() const override;

    bool acceptsMidi() const override;
    bool producesMidi() const override;
    bool isMidiEffect() const override;
    double getTailLengthSeconds() const override;

    //==============================================================================
    int getNumPrograms() override;
    int getCurrentProgram() override;
    void setCurrentProgram (int index) override;
    const juce::String getProgramName (int index) override;
    void changeProgramName (int index, const juce::String& newName) override;

    //==============================================================================
    void getStateInformation (juce::MemoryBlock& destData) override;
    void setStateInformation (const void* data, int sizeInBytes) override;
    
    juce::AudioProcessorValueTreeState _treeState;
    juce::ValueTree variableTree
    { "Variables", {},
        {
        { "Group", {{ "name", "Vars" }},
            {
                { "Parameter", {{ "id", "width" }, { "value", 0.0 }}},
                { "Parameter", {{ "id", "height" }, { "value", 0.0 }}},
                { "Parameter", {{ "id", "glowslider" }, { "value", 1 }}},
                { "Parameter", {{ "id", "glowtoggle" }, { "value", 1 }}},
                { "Parameter", {{ "id", "gradienttoggle" }, { "value", 1 }}},
                { "Parameter", {{ "id", "colortheme" }, { "value", 0 }}}
            }
        }
        }
    };
    
    /** Window Vars =====================================================*/
    float windowWidth {0.0f};
    float windowHeight {0.0f};
    
private:
    /** JUCE Boilerplate */
    juce::dsp::ProcessSpec spec;
    juce::AudioProcessorValueTreeState::ParameterLayout createParameterLayout();
    void parameterChanged (const juce::String& parameterID, float newValue) override;
    
    /** DSP */
    juce::dsp::Gain<float> _inputGainModule;
    juce::dsp::Gain<float> _outputGainModule;
    juce::dsp::Oversampling<float> _oversamplingModule;
    void hqProcessBlock(juce::AudioBuffer<float>& buffer);
    void normalProcessBlock(juce::AudioBuffer<float>& buffer);
    bool hqToggle;
    void updateParameters();
    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (LVTemplateAudioProcessor)
};
