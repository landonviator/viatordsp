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
    };
}

#endif /* utils_h */

