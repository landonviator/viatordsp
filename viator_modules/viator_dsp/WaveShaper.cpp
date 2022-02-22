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
            mGainDB = viator_utils::utils::dbToGain(mRawGain.getNextValue());
        }
        case ParameterId::kSampleRate: mCurrentSampleRate = parameterValue; break;
        case ParameterId::kBypass: mGlobalBypass = static_cast<bool>(parameterValue);
    }
}

float viator_dsp::WaveShaper::processCubicShaper(float dataToShape, int coeff3, int coeff2, int coeff1)
{
    /** Don't do anything if the module is off*/
    if (mGlobalBypass) return dataToShape;
    
    auto shape = coeff3 * pow(dataToShape, 3) + coeff2 * pow(dataToShape, 2) + coeff1 * dataToShape;
    
    return viator_utils::utils::clipData(shape);
}
