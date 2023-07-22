#include "ChaoticMaps.h"

namespace viator_dsp
{

template <typename SampleType>
ChaoticMaps<SampleType>::ChaoticMaps()
{
}

template <typename SampleType>
void ChaoticMaps<SampleType>::prepare(const juce::dsp::ProcessSpec& spec) noexcept
{
}

template <typename SampleType>
void ChaoticMaps<SampleType>::reset() noexcept
{
}

template <typename SampleType>
void ChaoticMaps<SampleType>::processMap(SampleType index) noexcept
{
    if (static_cast<int>(index) % static_cast<int>(_chaosFrequency) == 0)
    {
        const double new_x = y + 1 - a * (x * x);
        const double new_y = b * x;
        x = new_x;
        y = new_y;
    }
}

template <typename SampleType>
void ChaoticMaps<SampleType>::processBlock(juce::dsp::AudioBlock<float> &block) noexcept
{
    for (int ch = 0; ch < block.getNumChannels(); ++ch)
    {
        float* data = block.getChannelPointer(ch);
        
        for (int sample = 0; sample < block.getNumSamples(); ++sample)
        {
            data[sample] = std::sin(x) * _volume;
            
            if (sample % static_cast<int>(_chaosFrequency) == 0)
            {
                const double new_x = y + 1 - a * (x * x);
                const double new_y = b * x;
                x = new_x;
                y = new_y;
            }
        }
    }
}

template class ChaoticMaps<float>;
template class ChaoticMaps<double>;

}
