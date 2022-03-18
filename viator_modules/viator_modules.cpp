#ifdef VIATOR_MODULES_H_INCLUDED
 /* When you add this cpp file to your project, you mustn't include it in a file where you've
    already included any other headers - just put it inside a file on its own, possibly with your config
    flags preceding it, but don't include anything else. That also includes avoiding any automatic prefix
    header files that the compiler may be using.
 */
 #error "Incorrect use of JUCE cpp file"
#endif

#include "viator_modules.h"

/** Viator DSP CPP Files*/
#include "viator_dsp/Clipper.cpp"
#include "viator_dsp/SVFilter.cpp"
#include "viator_dsp/WaveShaper.cpp"
#include "viator_dsp/Saturation.cpp"

/** Viator GUI CPP Files*/
#include "viator_gui/Widgets/Dial.cpp"
#include "viator_gui/Widgets/Fader.cpp"
#include "viator_gui/Widgets/Menu.cpp"
#include "viator_gui/Widgets/NumberBox.cpp"
#include "viator_gui/Widgets/Toggle.cpp"
#include "viator_gui/Widgets/StyleSheet.cpp"
