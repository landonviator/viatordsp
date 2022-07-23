#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
LVTemplateAudioProcessor::LVTemplateAudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
     : AudioProcessor (BusesProperties()
                     #if ! JucePlugin_IsMidiEffect
                      #if ! JucePlugin_IsSynth
                       .withInput  ("Input",  juce::AudioChannelSet::stereo(), true)
                      #endif
                       .withOutput ("Output", juce::AudioChannelSet::stereo(), true)
                     #endif
                       )
, _treeState(*this, nullptr, "PARAMETERS", createParameterLayout())
, _oversamplingModule(2, 2, juce::dsp::Oversampling<float>::FilterType::filterHalfBandPolyphaseIIR)
#endif
{
    
    variableTree.setProperty("glowslider", 1, nullptr);
    variableTree.setProperty("gradienttoggle", 1, nullptr);
    variableTree.setProperty("glowtoggle", 0, nullptr);
    variableTree.setProperty("gradienttoggle", 1, nullptr);
    
    _treeState.addParameterListener(inputID, this);
    _treeState.addParameterListener(outputID, this);
    _treeState.addParameterListener(phaseID, this);
    _treeState.addParameterListener(hqID, this);
    _treeState.addParameterListener(presetID, this);
}

LVTemplateAudioProcessor::~LVTemplateAudioProcessor()
{
    _treeState.removeParameterListener(inputID, this);
    _treeState.removeParameterListener(outputID, this);
    _treeState.removeParameterListener(phaseID, this);
    _treeState.removeParameterListener(hqID, this);
    _treeState.removeParameterListener(presetID, this);
}

juce::AudioProcessorValueTreeState::ParameterLayout LVTemplateAudioProcessor::createParameterLayout()
{
    std::vector <std::unique_ptr<juce::RangedAudioParameter>> params;
    
    params.push_back (std::make_unique<juce::AudioParameterInt>(juce::ParameterID { presetID, 1 }, presetName, 0, 9, 0));
    
    params.push_back (std::make_unique<juce::AudioParameterFloat>(juce::ParameterID { inputID, 1 }, inputName,
                                                                  juce::NormalisableRange<float> (-24.0f, 24.0f, 0.1f), 0.0f));
    
    params.push_back (std::make_unique<juce::AudioParameterFloat>(juce::ParameterID { outputID, 1 }, outputName,
                                                                  juce::NormalisableRange<float> (-24.0f, 24.0f, 0.1f), 0.0f));
    
    params.push_back (std::make_unique<juce::AudioParameterBool>(juce::ParameterID { phaseID, 1 }, phaseName, false));
    
    params.push_back (std::make_unique<juce::AudioParameterBool>(juce::ParameterID { hqID, 1 }, hqName, false));
    
    params.push_back (std::make_unique<juce::AudioParameterInt>(juce::ParameterID { colorID, 1 }, colorName, 0, 9, 0));
    
    return { params.begin(), params.end() };
}

void LVTemplateAudioProcessor::parameterChanged(const juce::String &parameterID, float newValue)
{
    if (parameterID == hqID)
    {
        hqToggle = static_cast<bool>(_treeState.getRawParameterValue(hqID)->load());
            
        // Adjust samplerate of filters when oversampling
        if (hqToggle)
        {
            spec.sampleRate = getSampleRate() * _oversamplingModule.getOversamplingFactor();
            _inputGainModule.prepare(spec);
            _outputGainModule.prepare(spec);
        }

        else
        {
            spec.sampleRate = getSampleRate();
            _inputGainModule.prepare(spec);
            _outputGainModule.prepare(spec);
        }
    }
            
    updateParameters();
}

void LVTemplateAudioProcessor::updateParameters()
{
    _inputGainModule.setGainDecibels(_treeState.getRawParameterValue(inputID)->load());
    _outputGainModule.setGainDecibels(_treeState.getRawParameterValue(outputID)->load());
}

//==============================================================================
const juce::String LVTemplateAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool LVTemplateAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool LVTemplateAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool LVTemplateAudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double LVTemplateAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int LVTemplateAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int LVTemplateAudioProcessor::getCurrentProgram()
{
    return 0;
}

void LVTemplateAudioProcessor::setCurrentProgram (int index)
{
}

const juce::String LVTemplateAudioProcessor::getProgramName (int index)
{
    return {};
}

void LVTemplateAudioProcessor::changeProgramName (int index, const juce::String& newName)
{
}

//==============================================================================
void LVTemplateAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    // Initialize spec for dsp modules
    hqToggle = static_cast<bool>(_treeState.getRawParameterValue(hqID)->load());
        
    // Oversampling
    _oversamplingModule.initProcessing(samplesPerBlock);
    
    if (hqToggle)
    {
        spec.sampleRate = sampleRate * _oversamplingModule.getOversamplingFactor();
    }
        
    else
    {
        spec.sampleRate = sampleRate;
    }
    
    spec.maximumBlockSize = samplesPerBlock;
    spec.numChannels = getTotalNumInputChannels();
    
    // DSP
    _inputGainModule.prepare(spec);
    _outputGainModule.prepare(spec);
    
    // Init params
    updateParameters();
}

void LVTemplateAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool LVTemplateAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
  #if JucePlugin_IsMidiEffect
    juce::ignoreUnused (layouts);
    return true;
  #else
    // This is the place where you check if the layout is supported.
    // In this template code we only support mono or stereo.
    // Some plugin hosts, such as certain GarageBand versions, will only
    // load plugins that support stereo bus layouts.
    if (layouts.getMainOutputChannelSet() != juce::AudioChannelSet::mono()
     && layouts.getMainOutputChannelSet() != juce::AudioChannelSet::stereo())
        return false;

    // This checks if the input layout matches the output layout
   #if ! JucePlugin_IsSynth
    if (layouts.getMainOutputChannelSet() != layouts.getMainInputChannelSet())
        return false;
   #endif

    return true;
  #endif
}
#endif

void LVTemplateAudioProcessor::processBlock (juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiMessages)
{
    juce::ScopedNoDenormals noDenormals;

    if (hqToggle)
    {
        hqProcessBlock(buffer);
    }
    
    else
    {
        normalProcessBlock(buffer);
    }

}

void LVTemplateAudioProcessor::hqProcessBlock(juce::AudioBuffer<float> &buffer)
{
    // Blocks
    juce::dsp::AudioBlock<float> block {buffer};
    juce::dsp::AudioBlock<float> upSampledBlock (buffer);

    // Up sample
    upSampledBlock = _oversamplingModule.processSamplesUp(upSampledBlock);
    
    // Input
    _inputGainModule.process(juce::dsp::ProcessContextReplacing<float>(upSampledBlock));
    
    // Output
    _outputGainModule.process(juce::dsp::ProcessContextReplacing<float>(upSampledBlock));
    
    // Apply phase invert
    if (_treeState.getRawParameterValue(phaseID)->load())
    {
        viator_utils::utils::invertBlock(upSampledBlock);
    }
    
    _oversamplingModule.processSamplesDown(block);
    
    // Clip output
    viator_utils::utils::hardClipBlock(block);
}

void LVTemplateAudioProcessor::normalProcessBlock(juce::AudioBuffer<float> &buffer)
{
    // Block
    juce::dsp::AudioBlock<float> block {buffer};

    // Input
    _inputGainModule.process(juce::dsp::ProcessContextReplacing<float>(block));
    
    // Output
    _outputGainModule.process(juce::dsp::ProcessContextReplacing<float>(block));
    
    // Apply phase invert
    if (_treeState.getRawParameterValue(phaseID)->load())
    {
        viator_utils::utils::invertBlock(block);
    }
    
    // Clip output
    viator_utils::utils::hardClipBlock(block);
}

//==============================================================================
bool LVTemplateAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

juce::AudioProcessorEditor* LVTemplateAudioProcessor::createEditor()
{
    return new LVTemplateAudioProcessorEditor (*this);
    //return new juce::GenericAudioProcessorEditor (*this);
}

//==============================================================================
void LVTemplateAudioProcessor::getStateInformation (juce::MemoryBlock& destData)
{
    // Save params
    _treeState.state.appendChild(variableTree, nullptr);
    juce::MemoryOutputStream stream(destData, false);
    _treeState.state.writeToStream (stream);
}

void LVTemplateAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // Recall params
    auto tree = juce::ValueTree::readFromData (data, size_t(sizeInBytes));
    variableTree = tree.getChildWithName("Variables");
    
    if (tree.isValid())
    {
        _treeState.state = tree;
        
        // Window Size
        windowWidth = variableTree.getProperty("width");
        windowHeight = variableTree.getProperty("height");
    }
}

//==============================================================================
// This creates new instances of the plugin..
juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new LVTemplateAudioProcessor();
}
