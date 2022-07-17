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
#endif
{
    
    variableTree.setProperty("glowslider", 1, nullptr);
    variableTree.setProperty("gradienttoggle", 1, nullptr);
    variableTree.setProperty("glowtoggle", 0, nullptr);
    variableTree.setProperty("gradienttoggle", 1, nullptr);
    
    _treeState.addParameterListener(colorID, this);
    _treeState.addParameterListener(driveID, this);
    _treeState.addParameterListener(driveModelID, this);
}

LVTemplateAudioProcessor::~LVTemplateAudioProcessor()
{
    _treeState.removeParameterListener(colorID, this);
    _treeState.removeParameterListener(driveID, this);
    _treeState.removeParameterListener(driveModelID, this);
}

juce::AudioProcessorValueTreeState::ParameterLayout LVTemplateAudioProcessor::createParameterLayout()
{
    std::vector <std::unique_ptr<juce::RangedAudioParameter>> params;
    
    juce::StringArray driveChoices {"Hard", "Soft", "Fuzz", "Tube", "Saturation", "Lofi"};
        
    auto pDriveModel = std::make_unique<juce::AudioParameterChoice>(driveModelID, driveModelName, driveChoices, 0);
    auto pDrive = std::make_unique<juce::AudioParameterFloat>(driveID, driveName, 0.0f, 20.0f, 0.0f);
    auto pColorMenu = std::make_unique<juce::AudioParameterInt>(colorID, colorName, 0, 9, 0);
    
    params.push_back(std::move(pDriveModel));
    params.push_back(std::move(pDrive));
    params.push_back(std::move(pColorMenu));
    
    return { params.begin(), params.end() };
}

void LVTemplateAudioProcessor::parameterChanged(const juce::String &parameterID, float newValue)
{
    updateParameters();
}

void LVTemplateAudioProcessor::updateParameters()
{
    _distortionModule.setDrive(_treeState.getRawParameterValue(driveID)->load());
    
    switch (static_cast<int>(_treeState.getRawParameterValue(driveModelID)->load()))
    {
        case 0: _distortionModule.setClipperType(viator_dsp::Distortion<float>::ClipType::kHard); break;
        case 1: _distortionModule.setClipperType(viator_dsp::Distortion<float>::ClipType::kSoft); break;
        case 2: _distortionModule.setClipperType(viator_dsp::Distortion<float>::ClipType::kFuzz); break;
        case 3: _distortionModule.setClipperType(viator_dsp::Distortion<float>::ClipType::kTube); break;
        case 4: _distortionModule.setClipperType(viator_dsp::Distortion<float>::ClipType::kSaturation); break;
        case 5: _distortionModule.setClipperType(viator_dsp::Distortion<float>::ClipType::kLofi); break;
    }
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
    spec.maximumBlockSize = samplesPerBlock;
    spec.sampleRate = sampleRate;
    spec.numChannels = getTotalNumOutputChannels();
    
    _distortionModule.prepare(spec);
    
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
    auto totalNumInputChannels  = getTotalNumInputChannels();
    auto totalNumOutputChannels = getTotalNumOutputChannels();

    _distortionModule.processBuffer(buffer);
}

//==============================================================================
bool LVTemplateAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

juce::AudioProcessorEditor* LVTemplateAudioProcessor::createEditor()
{
    //return new LVTemplateAudioProcessorEditor (*this);
    return new juce::GenericAudioProcessorEditor (*this);
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
