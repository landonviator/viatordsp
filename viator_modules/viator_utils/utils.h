#ifndef utils_h
#define utils_h

namespace viator_utils
{
    struct utils
    {
        static constexpr float _piDivisor = 2.0 / juce::MathConstants<float>::pi;
        
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
        static void hardClipBlock(juce::dsp::AudioBlock<float> &block, float thresh)
        {
            for (int ch = 0; ch < block.getNumChannels(); ++ch)
            {
                float* data = block.getChannelPointer(ch);
                
                for (int sample = 0; sample < block.getNumSamples(); ++sample)
                {
                    if (std::abs(data[sample]) >= juce::Decibels::decibelsToGain(thresh))
                    {
                        data[sample] = std::copysign(juce::Decibels::decibelsToGain(thresh), data[sample]);
                    }
                }
            }
        }
        
        static void softClipBlock(juce::dsp::AudioBlock<float> &block)
        {
            for (int ch = 0; ch < block.getNumChannels(); ++ch)
            {
                float* data = block.getChannelPointer(ch);
                
                for (int sample = 0; sample < block.getNumSamples(); ++sample)
                {
                    data[sample] = std::tanh(data[sample]);
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


        /**
         * @brief Bias a value, best used on values between 0 and 1.
         * 
         * @authors Noah Stiltner, and the math came from Signalsmith's Desmos formula:
         * https://www.desmos.com/calculator/97t87kp8cq
         * 
         * @param valueToBias the value going to be biased
         * @param bias the amount of bias to apply
         * @return float - biased value
         */
        static float unitBiasNormal(float valueToBias, float bias)
        {
            /*
             * Let's make sure that the bias is inclusively
             * between 0 and 1 to avoid any malfunctions. If
             * you tripped this jassert, make sure that the 
             * bias parameter is in the range [0, 1].
             */
            //juce::jassert(bias >= 0.f && bias <= 1.f);

            // Let's cover the easy options to avoid processing
            if(bias == 0.5f)
                return valueToBias;
            if(bias == 0.f)
                return 0.f;
            if(bias == 1.f)
                return 1.f;
            
            return bias * valueToBias / (1.f - bias - valueToBias + (2.f * valueToBias * bias));
        }

        /**
         * @brief Bias a value using a ranged bias, where the range is 
         * [-range, range] instead of [0, 1]. Might be useful with a centered 
         * rotary slider.
         * 
         * 
         * For a bias parameter range of [-0.5, 0.5], it could be called like
         * so:
         * unitBiasAdapted(valueToBias, bias, 0.5f)
         * 
         * or from [-1, 1]
         * unitBiasAdapted(valueToBias, bias, 1.f)
         * 
         * @authors Noah Stiltner.
         * 
         * @param valueToBias the value to bias. Preferably between 0 and 1
         * @param bias the bias to apply to the value. Should be between [-range, range]
         * @param range the maximum value of the bias parameter, and the minimum will be 
         * 
         * @return float - the biased value
         */
        static float unitBiasAdapted(float valueToBias, float bias, float range)
        {
            // Make sure the range parameter is greater than 0
            //juce::jassert(range > 0);

            // Make sure the bias parameter is between [-max, max]
            //juce::jassert(bias >= -range && bias <= range);

            // this gets the bias to be between [-1, 1]
            //T newBias = bias / max;
            // but we want it between [0, 1], so we can divide by 2, then add 0.5
            return unitBiasNormal(valueToBias, bias / range / 2.f + 0.5f);
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

namespace gui_utils
{

struct Colors
{
    static inline juce::Colour _textColor = juce::Colour::fromRGB(161, 168, 181).darker(0.3f);
};

} // gui utils

}
#endif /* utils_h */

