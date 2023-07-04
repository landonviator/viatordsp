#ifndef Compressor_h
#define Compressor_h

#include <JuceHeader.h>

namespace viator_dsp
{

template <typename SampleType>
class Compressor : public ModuleBase<SampleType>
{
public:
    Compressor(){};
    ~Compressor(){};

    void reset();
    
    SampleType processSample(SampleType input) override
    {
        return 2.0 / 3.14 * std::atan(input);
    }
    
private:
};

} // namespace viator_dsp

#endif /* Compressor_h */
