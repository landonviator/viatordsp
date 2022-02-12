#ifndef viator_utils_h
#define viator_utils_h

/** BEGIN_JUCE_MODULE_DECLARATION

    ID:            viator_utils
    vendor:         ViatorDSP
    version:        0.0.1
    name:           Landon Viator
    description:    I make plugins and noise
    website:        https://www.patreon.com/ViatorDSP
    license:        Proprietary

    dependencies:

    END_JUCE_MODULE_DECLARATION
*/

#endif /* viator_utils_h */

namespace viator_util
{
    /** Cool way to go from db to gain by default, or adjust the scalar for quicker/slower log ramp!*/
    template <typename T>
    T dbToGain(T input, T scalar = 0.05)
    {
        return std::pow(10.0, input * scalar);
    }
}
