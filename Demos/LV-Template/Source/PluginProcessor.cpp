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
, m_treeState(*this, nullptr, "PARAMETERS", createParameterLayout())
#endif
{
    
    variableTree.setProperty("glowslider", 1, nullptr);
    variableTree.setProperty("gradienttoggle", 1, nullptr);
    variableTree.setProperty("glowtoggle", 0, nullptr);
    variableTree.setProperty("gradienttoggle", 1, nullptr);
    
    // Distortion
    m_treeState.addParameterListener(driveEnableID, this);
    m_treeState.addParameterListener(driveMenuID, this);
    m_treeState.addParameterListener(driveID, this);
    m_treeState.addParameterListener(mixID, this);
    
    // Reverb
    m_treeState.addParameterListener(reverbEnableID, this);
    m_treeState.addParameterListener(roomSizeID, this);
    m_treeState.addParameterListener(dampingID, this);
    m_treeState.addParameterListener(widthID, this);
    m_treeState.addParameterListener(reverbMixID, this);
    
    // Tilt EQ
    m_treeState.addParameterListener(tiltGainID, this);
    
    // Mid Gain
    m_treeState.addParameterListener(toneEnableID, this);
    m_treeState.addParameterListener(midGainID, this);
    m_treeState.addParameterListener(midCutoffID, this);
    m_treeState.addParameterListener(midQID, this);
    m_treeState.addParameterListener(midPreID, this);
    
    // Color Menu
    m_treeState.addParameterListener(colorID, this);
}

LVTemplateAudioProcessor::~LVTemplateAudioProcessor()
{
    // Distortion
    m_treeState.removeParameterListener(driveEnableID, this);
    m_treeState.removeParameterListener(driveMenuID, this);
    m_treeState.removeParameterListener(driveID, this);
    m_treeState.removeParameterListener(mixID, this);
    
    // Reverb
    m_treeState.removeParameterListener(reverbEnableID, this);
    m_treeState.removeParameterListener(roomSizeID, this);
    m_treeState.removeParameterListener(dampingID, this);
    m_treeState.removeParameterListener(widthID, this);
    m_treeState.removeParameterListener(reverbMixID, this);
    
    // Tilt EQ
    m_treeState.removeParameterListener(tiltGainID, this);
    
    // Mid Gain
    m_treeState.removeParameterListener(toneEnableID, this);
    m_treeState.removeParameterListener(midGainID, this);
    m_treeState.removeParameterListener(midCutoffID, this);
    m_treeState.removeParameterListener(midQID, this);
    m_treeState.removeParameterListener(midPreID, this);
    
    // Color Menu
    m_treeState.removeParameterListener(colorID, this);
}

juce::AudioProcessorValueTreeState::ParameterLayout LVTemplateAudioProcessor::createParameterLayout()
{
    std::vector <std::unique_ptr<juce::RangedAudioParameter>> params;
        
    // Distortion
    auto pDriveEnable = std::make_unique<juce::AudioParameterBool>(driveEnableID, driveEnableID, true);
    auto pDriveMenu = std::make_unique<juce::AudioParameterInt>(driveMenuID, driveMenuName, 0, 6, 0);
    auto pDrive = std::make_unique<juce::AudioParameterFloat>(driveID, driveName, 0.0f, 20.0f, 0.0f);
    auto pMix = std::make_unique<juce::AudioParameterFloat>(mixID, mixName, 0.0f, 1.0f, 1.0f);
    
    // Reverb
    auto pReverbEnable = std::make_unique<juce::AudioParameterBool>(reverbEnableID, reverbEnableName, true);
    auto pRoomSize = std::make_unique<juce::AudioParameterFloat>(roomSizeID, roomSizeName, 0.0f, 1.0f, 0.5f);
    auto pDamping = std::make_unique<juce::AudioParameterFloat>(dampingID, dampingName, 0.0f, 1.0f, 0.5f);
    auto pWidth = std::make_unique<juce::AudioParameterFloat>(widthID, widthName, 0.0f, 1.0f, 0.5f);
    auto pReverbMix = std::make_unique<juce::AudioParameterFloat>(reverbMixID, reverbMixName, 0.0f, 1.0f, 1.0f);
    
    // Tilt EQ
    auto pTiltGain = std::make_unique<juce::AudioParameterFloat>(tiltGainID, tiltGainName, -15.0f, 15.0f, 0.0f);
    
    // Mid Gain
    auto cutoffRange = juce::NormalisableRange<float>(200.0f, 5000.0f, 1.0f);
    cutoffRange.setSkewForCentre(1000.0f);
    
    auto pToneEnable = std::make_unique<juce::AudioParameterBool>(toneEnableID, toneEnableName, true);
    auto pMidGain = std::make_unique<juce::AudioParameterFloat>(midGainID, midGainName, -15.0f, 15.0f, 0.0f);
    auto pMidCutoff = std::make_unique<juce::AudioParameterFloat>(midCutoffID, midCutoffName, cutoffRange, 1000.0f);
    auto pMidQ = std::make_unique<juce::AudioParameterFloat>(midQID, midQName, 0.05f, 0.85f, 0.3f);
    auto pMidPre = std::make_unique<juce::AudioParameterBool>(midPreID, midPreName, false);
    
    // Color
    auto pColorMenu = std::make_unique<juce::AudioParameterInt>(colorID, colorName, 0, 9, 0);
    
    // Distortion
    params.push_back(std::move(pDriveEnable));
    params.push_back(std::move(pDriveMenu));
    params.push_back(std::move(pDrive));
    params.push_back(std::move(pMix));
    
    // Reverb
    params.push_back(std::move(pReverbEnable));
    params.push_back(std::move(pRoomSize));
    params.push_back(std::move(pDamping));
    params.push_back(std::move(pWidth));
    params.push_back(std::move(pReverbMix));
    
    // Tilt EQ
    params.push_back(std::move(pTiltGain));
    
    // Mid Gain
    params.push_back(std::move(pToneEnable));
    params.push_back(std::move(pMidGain));
    params.push_back(std::move(pMidCutoff));
    params.push_back(std::move(pMidQ));
    params.push_back(std::move(pMidPre));
    
    // Color
    params.push_back(std::move(pColorMenu));
    
    return { params.begin(), params.end() };
}

void LVTemplateAudioProcessor::parameterChanged(const juce::String &parameterID, float newValue)
{
    updateParameters();
}

void LVTemplateAudioProcessor::updateParameters()
{
    // Distortion
    switch (static_cast<int>(m_treeState.getRawParameterValue(driveMenuID)->load()))
    {
        case 0: m_DistortionModule.setClipperType(viator_dsp::Distortion<float>::ClipType::kLofi); break;
        case 1: m_DistortionModule.setClipperType(viator_dsp::Distortion<float>::ClipType::kHard); break;
        case 2: m_DistortionModule.setClipperType(viator_dsp::Distortion<float>::ClipType::kSoft); break;
        case 3: m_DistortionModule.setClipperType(viator_dsp::Distortion<float>::ClipType::kDiode); break;
        case 4: m_DistortionModule.setClipperType(viator_dsp::Distortion<float>::ClipType::kFuzz); break;
        case 5: m_DistortionModule.setClipperType(viator_dsp::Distortion<float>::ClipType::kTube); break;
        case 6: m_DistortionModule.setClipperType(viator_dsp::Distortion<float>::ClipType::kSaturation); break;
    }
    
    m_DistortionModule.setDrive(m_treeState.getRawParameterValue(driveID)->load());
    m_DistortionModule.setMix(m_treeState.getRawParameterValue(mixID)->load());
    
    // Reverb
    reverbParams.roomSize = m_treeState.getRawParameterValue(roomSizeID)->load();
    reverbParams.damping = m_treeState.getRawParameterValue(dampingID)->load();
    reverbParams.width = m_treeState.getRawParameterValue(widthID)->load();
    reverbParams.dryLevel = juce::jmap(m_treeState.getRawParameterValue(reverbMixID)->load(),
                                       0.0f, 1.0f, 1.0f, 0.0f);
    reverbParams.wetLevel = m_treeState.getRawParameterValue(reverbMixID)->load();
    m_ReverbModule.setParameters(reverbParams);
    
    // Tilt EQ
    m_LowShelfModule.setParameter(filterParam::kGain, m_treeState.getRawParameterValue(tiltGainID)->load() * -1.0);
    m_HighShelfModule.setParameter(filterParam::kGain, m_treeState.getRawParameterValue(tiltGainID)->load());
    
    // Mid Gain
    m_MidToneModule.setParameter(filterParam::kGain, m_treeState.getRawParameterValue(midGainID)->load());
    m_MidToneModule.setParameter(filterParam::kCutoff, m_treeState.getRawParameterValue(midCutoffID)->load());
    m_MidToneModule.setParameter(filterParam::kQ, m_treeState.getRawParameterValue(midQID)->load());
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
    
    m_DistortionModule.prepare(spec);
    m_DistortionModule.setClipperType(viator_dsp::Distortion<float>::ClipType::kLofi);
    
    m_ReverbModule.prepare(spec);
    m_ReverbModule.setParameters(reverbParams);
    
    m_LowShelfModule.prepare(spec);
    m_LowShelfModule.setParameter(filterParam::kType, filterType::kLowShelf);
    m_LowShelfModule.setParameter(filterParam::kCutoff, 1000.0);
    m_LowShelfModule.setParameter(filterParam::kQType, qType::kProportional);
    m_LowShelfModule.setParameter(filterParam::kQ, 0.3);
    m_LowShelfModule.setParameter(filterParam::kGain, 0.0);
    
    m_HighShelfModule.prepare(spec);
    m_HighShelfModule.setParameter(filterParam::kType, filterType::kHighShelf);
    m_HighShelfModule.setParameter(filterParam::kCutoff, 1000.0);
    m_HighShelfModule.setParameter(filterParam::kQType, qType::kProportional);
    m_HighShelfModule.setParameter(filterParam::kQ, 0.3);
    m_HighShelfModule.setParameter(filterParam::kGain, 0.0);
    
    m_MidToneModule.prepare(spec);
    m_MidToneModule.setParameter(filterParam::kType, filterType::kBandShelf);
    m_MidToneModule.setParameter(filterParam::kCutoff, 1000.0);
    m_MidToneModule.setParameter(filterParam::kQType, qType::kParametric);
    m_MidToneModule.setParameter(filterParam::kQ, 0.3);
    m_MidToneModule.setParameter(filterParam::kGain, 0.0);
    
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

    juce::dsp::AudioBlock<float> audioBlock {buffer};
    
    if (m_treeState.getRawParameterValue(midPreID)->load())
    {
        if (m_treeState.getRawParameterValue(toneEnableID)->load())
        {
            m_MidToneModule.process(juce::dsp::ProcessContextReplacing<float>(audioBlock));
            m_LowShelfModule.process(juce::dsp::ProcessContextReplacing<float>(audioBlock));
            m_HighShelfModule.process(juce::dsp::ProcessContextReplacing<float>(audioBlock));
        }
        
        if (m_treeState.getRawParameterValue(driveEnableID)->load())
        {
            m_DistortionModule.process(juce::dsp::ProcessContextReplacing<float>(audioBlock));
        }
    }
    
    else
    {
        if (m_treeState.getRawParameterValue(driveEnableID)->load())
        {
            m_DistortionModule.process(juce::dsp::ProcessContextReplacing<float>(audioBlock));
        }
        
        if (m_treeState.getRawParameterValue(toneEnableID)->load())
        {
            m_MidToneModule.process(juce::dsp::ProcessContextReplacing<float>(audioBlock));
            m_LowShelfModule.process(juce::dsp::ProcessContextReplacing<float>(audioBlock));
            m_HighShelfModule.process(juce::dsp::ProcessContextReplacing<float>(audioBlock));
        }
    }
    
    if (m_treeState.getRawParameterValue(reverbEnableID)->load())
    {
        m_ReverbModule.process(juce::dsp::ProcessContextReplacing<float>(audioBlock));
    }
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
    m_treeState.state.appendChild(variableTree, nullptr);
    juce::MemoryOutputStream stream(destData, false);
    m_treeState.state.writeToStream (stream);
}

void LVTemplateAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // Recall params
    auto tree = juce::ValueTree::readFromData (data, size_t(sizeInBytes));
    variableTree = tree.getChildWithName("Variables");
    
    if (tree.isValid())
    {
        m_treeState.state = tree;
        
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
