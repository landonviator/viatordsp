#ifndef HardClipper_h
#define HardClipper_h

#include "../Common/Common.h"

namespace viator_dsp
{
class HardClipper
{
public:
    
    HardClipper();
    
    void prepare(const juce::dsp::ProcessSpec& spec);
    
    float processSample(float input);
    
    enum class ParameterId
    {
        kPreamp,
        kSampleRate,
        kBypass
    };
        
    void setParameter(ParameterId parameter, float parameterValue);
    
private:
    
    // Member variables
    float mCurrentSampleRate;
    juce::SmoothedValue<float> mRawGain;
    bool mGlobalBypass;
};
}

#endif /* HardClipper_h */
