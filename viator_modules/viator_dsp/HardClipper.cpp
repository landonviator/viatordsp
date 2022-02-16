#include "HardClipper.h"

viator_dsp::HardClipper::HardClipper() :
mGlobalBypass(false)
{
    
}

void viator_dsp::HardClipper::prepare(const juce::dsp::ProcessSpec& spec)
{
    mCurrentSampleRate = spec.sampleRate;
    mRawGain.reset(mCurrentSampleRate, 0.02);
    mRawGain.setTargetValue(0.0);
}

float viator_dsp::HardClipper::processSample(float input)
{
    if (mGlobalBypass) return input;
    
    input *= viator_utils::utils::dbToGain(mRawGain.getNextValue());
    
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
        case ParameterId::kPreamp: mRawGain.setTargetValue(parameterValue); break;
        case ParameterId::kSampleRate: mCurrentSampleRate = parameterValue; break;
        case ParameterId::kBypass: mGlobalBypass = static_cast<bool>(parameterValue);
    }
}
