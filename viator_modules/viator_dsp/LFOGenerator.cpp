#include "LFOGenerator.h"

void viator_dsp::LFOGenerator::prepare(const juce::dsp::ProcessSpec &spec)
{
    m_frequency = 1;
    m_time = 0.0;
    m_deltaTime = 1 / spec.sampleRate;
}

/** Must be called in the sample loop*/
void viator_dsp::LFOGenerator::process()
{
    if (m_GlobalBypass)
    {
        m_LFOValue.setTargetValue(0.0);
        return;
    }
    
    if (m_time >= std::numeric_limits<float>::max())
    {
        m_time = 0.0;
    }
    
    m_LFOValue = sin(2 * juce::double_Pi * m_frequency * m_time);
    m_time += m_deltaTime;
}

float viator_dsp::LFOGenerator::getCurrentLFOValue()
{
    return m_LFOValue;
}

void viator_dsp::LFOGenerator::setParameter(ParameterId parameter, float parameterValue)
{
    switch (parameter)
    {
        case viator_dsp::LFOGenerator::ParameterId::kFrequency: m_frequency = static_cast<int>(parameterValue); break;
        case viator_dsp::LFOGenerator::ParameterId::kBypass: m_GlobalBypass = static_cast<bool>(parameterValue); break;
    }
}
