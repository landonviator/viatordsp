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
        
        template <typename T>
        static T clipData(T input, T thresh = 1.0)
        {
            if (std::abs(input) > thresh)
            {
                input *= 1.0 / std::abs(input);
            }
            
            return input;
        }
    };
}

#endif /* utils_h */

