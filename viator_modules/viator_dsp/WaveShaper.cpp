#include "WaveShaper.h"

viator_dsp::WaveShaper::WaveShaper() :
mGlobalBypass(false), mGainDB(1.0)
{
}

void viator_dsp::WaveShaper::prepare(const juce::dsp::ProcessSpec& spec)
{
    mCurrentSampleRate = spec.sampleRate;
    mRawGain.reset(mCurrentSampleRate, 0.02);
    mRawGain.setTargetValue(0.0);
}

void viator_dsp::WaveShaper::setParameter(ParameterId parameter, float parameterValue)
{
    switch (parameter)
    {
        case ParameterId::kPreamp:
        {
            mRawGain.setTargetValue(parameterValue); break;
        }
        case ParameterId::kSampleRate: mCurrentSampleRate = parameterValue; break;
        case ParameterId::kBypass: mGlobalBypass = static_cast<bool>(parameterValue);
    }
}

float viator_dsp::WaveShaper::processCubicShaper(float dataToShape, float coeff3, float coeff2, float coeff1)
{
    /** Don't do anything if the module is off*/
    if (mGlobalBypass) return dataToShape;
    
    auto gain = viator_utils::utils::dbToGain(mRawGain.getNextValue());
    return coeff3 * std::pow(dataToShape * gain, 5) - coeff2 * std::pow(dataToShape * gain, 3) + coeff1 * dataToShape * gain;
}
