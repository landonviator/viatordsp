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
    
    juce::AudioProcessorValueTreeState m_treeState;
    juce::ValueTree variableTree
    { "Variables", {},
        {
        { "Group", {{ "name", "Vars" }},
            {
                { "Parameter", {{ "id", "width" }, { "value", 0.0 }}},
                { "Parameter", {{ "id", "height" }, { "value", 0.0 }}},
                { "Parameter", {{ "id", "glowslider" }, { "value", 1.0 }}},
                { "Parameter", {{ "id", "glowtoggle" }, { "value", 0.0 }}},
                { "Parameter", {{ "id", "gradienttoggle" }, { "value", 1.0 }}}
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
    viator_dsp::Distortion<float> m_DistortionModule;
    juce::dsp::Reverb m_ReverbModule;
    juce::dsp::Reverb::Parameters reverbParams;
    
    viator_dsp::SVFilter<float> m_LowShelfModule;
    viator_dsp::SVFilter<float> m_HighShelfModule;
    viator_dsp::SVFilter<float> m_MidToneModule;
    using filterParam = viator_dsp::SVFilter<float>::ParameterId;
    using filterType = viator_dsp::SVFilter<float>::FilterType;
    using qType = viator_dsp::SVFilter<float>::QType;
    void updateParameters();
    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (LVTemplateAudioProcessor)
};
