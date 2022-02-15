#include "HardClipper.h"

void viator_dsp::HardClipper::prepare(const juce::dsp::ProcessSpec& spec)
{
    mCurrentSampleRate = spec.sampleRate;
    //mRawGain.reset(mCurrentSampleRate, 0.02);
    //mRawGain.setTargetValue(0.0);
    mGlobalBypass = false;
}

float viator_dsp::HardClipper::processSample(float input)
{
    input *= juce::Decibels::decibelsToGain(mRawGain);
    
    if (std::abs(input) > 1.0)
    {
        input *= 1.0 / std::abs(input);
    }
    
    return input;
}

void viator_dsp::HardClipper::setParameter(ParameterId parameter, float parameterValue)
{
    switch (parameter)
    {
        case ParameterId::kPreamp: mRawGain = parameterValue; break;
        case ParameterId::kSampleRate: mCurrentSampleRate = parameterValue; break;
        case ParameterId::kType: type = parameterValue; break;
        case ParameterId::kBypass: mGlobalBypass = static_cast<bool>(parameterValue);
    }
}
