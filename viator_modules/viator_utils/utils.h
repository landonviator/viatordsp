#ifndef utils_h
#define utils_h

namespace viator_utils
{
    struct utils
    {
        /** Cool way to go from db to gain by default, or adjust the scalar for quicker/slower log ramp!*/
        template <typename T>
        static T dbToGain(T input, T scalar = 0.05)
        {
            return std::pow(10.0, input * scalar);
        }
        
        /** Hard clip data */
        template <typename T>
        static T clipData(T input, T thresh = 1.0)
        {
            return std::copysign(thresh, input);
        }
        
        /** Hard clip an audio block */
        static void hardClipBlock(juce::dsp::AudioBlock<float> &block)
        {
            for (int ch = 0; ch < block.getNumChannels(); ++ch)
            {
                float* data = block.getChannelPointer(ch);
                
                for (int sample = 0; sample < block.getNumSamples(); ++sample)
                {
                    data[sample] = clipData(data[sample]);
                }
            }
        }
        
        /** Flip the phase of an audio block*/
        static void invertBlock(juce::dsp::AudioBlock<float> &block)
        {
            for (int ch = 0; ch < block.getNumChannels(); ++ch)
            {
                for (int sample = 0; sample < block.getNumSamples(); ++sample)
                {
                    float* data = block.getChannelPointer(ch);
                    data[sample] *= -1.0;
                }
            }
        }
        
        /** Multiply an audio block by a given value*/
        static void multiplyBlock(juce::dsp::AudioBlock<float> &block, float multiplier)
        {
            for (int ch = 0; ch < block.getNumChannels(); ++ch)
            {
                for (int sample = 0; sample < block.getNumSamples(); ++sample)
                {
                    float* data = block.getChannelPointer(ch);
                    data[sample] *= multiplier;
                }
            }
        }
    };

    struct FastMath
    {
        /** Fast std::pow*/
        static inline double fastPow(double a, double b)
        {
            union
            {
                double d;
                int x[2];
            }
            
            u = { a };
            u.x[1] = (int)(b * (u.x[1] - 1072632447) + 1072632447);
            u.x[0] = 0;
            
            return u.d;
        }
    };
}

#endif /* utils_h */

