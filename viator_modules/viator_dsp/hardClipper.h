#ifndef HardClipper_h
#define HardClipper_h

//#include "viator_dsp.h"
#include "../Common/Common.h"

namespace viator_dsp
{
class HardClipper
{
public:
    
    void prepare(const juce::dsp::ProcessSpec& spec);
    
    float processSample(float input);
    
    enum class ParameterId
    {
        kPreamp,
        kSampleRate,
        kType,
        kBypass
    };
        
    void setParameter(ParameterId parameter, float parameterValue);
    
private:
    
    // Member variables
    float mCurrentSampleRate;
    float mRawGain;
    bool mGlobalBypass;
    bool type = false;
};
}

#endif /* svfilter_h */
