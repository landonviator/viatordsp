/*
  ==============================================================================

    LV_EQ.h
    Created: 25 May 2021 5:40:30pm
    Author:  Landon Viator

  ==============================================================================
*/

#ifndef SVFilter_h
#define SVFilter_h

namespace viator_dsp
{
class SVFilter
{
public:
    
    /** Creates an uninitialised filter. Call prepare() before first use. */
    SVFilter();
    
    /** Initialises the filter. */
    void prepare(juce::dsp::ProcessSpec& spec);
    
    /** Processes the block */
    void processBlock(const juce::dsp::AudioBlock<float> &block);
    
    /** The parameters of this module. */
    enum class ParameterId
    {
        kType,
        kCutoff,
        kQ,
        kGain,
        kQType,
        kSampleRate,
        kBypass,
        kClipOutput
    };
        
    /** Different filter types*/
    enum FilterType
    {
        kLowShelf,
        kHighPass,
        kBandShelf,
        kLowPass,
        kHighShelf
    };
    
    /** Different filter Q-Factor types*/
    enum QType
    {
        kParametric,
        kProportional,
    };
    
    /** One method to change any parameter. */
    void setParameter(ParameterId parameter, float parameterValue);
    
private:
    
    /** Member variables */
    float mCurrentSampleRate, mQ, mCutoff, mGain, mRawGain, twoPi;
    bool mGlobalBypass, mClipOutput;
    
     /** Variables for the Z filter equations */
    double mGCoeff, mRCoeff, mRCoeff2, mK, mInversion;
    
     /** Filter type switch */
    FilterType mType;
    
     /** Q mode switch */
    QType mQType;
    
     /** state variables (z^-1) */
    std::vector<double> mZ1, mZ2;
    
    /** Convert the gain if needed */
    void setGain(float value);
    
    /** Get the different Q-Fators*/
    float getShelfQ(float value) const;
    float getPeakQ(float value) const;
};
}

#endif /* SVFilter_h */
