#include "Tube.h"

namespace viator_dsp
{

template <typename SampleType>
void Compressor<SampleType>::reset()
{
}

//==============================================================================
template class Compressor<float>;
template class Compressor<double>;

} // namespace viator_dsp
