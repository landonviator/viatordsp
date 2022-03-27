#pragma once
#ifndef LFOGenerator_h
#define LFOGenerator_h

#include <JuceHeader.h>

namespace viator_dsp
{
    class LFOGenerator
    {
    public:
        
        void prepare(const juce::dsp::ProcessSpec& spec);
            
        /** Must be called in the sample loop*/
        void process();
            
        enum class ParameterId
        {
            kFrequency,
            kBypass
        };

        void setParameter(ParameterId parameter, float parameterValue);
        float getCurrentLFOValue();
        
    private:
        
        float m_frequency;
        float m_time;
        float m_deltaTime;
        float m_LFOValue;
        bool m_GlobalBypass {false};
        
    }; // class
} // namepace

#endif /* LFOGenerator_h */
