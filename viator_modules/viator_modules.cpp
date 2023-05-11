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
#include "viator_dsp/Distortion.cpp"
#include "viator_dsp/SVFilter.cpp"
#include "viator_dsp/LFOGenerator.cpp"
#include "viator_dsp/MultiBandProcessor.cpp"
#include "viator_dsp/BitCrusher.cpp"
#include "viator_dsp/BrickWallLPF.cpp"

/** Viator GUI CPP Files*/
#include "viator_gui/Widgets/Dial.cpp"
#include "viator_gui/Widgets/Fader.cpp"
#include "viator_gui/Widgets/Label.cpp"
#include "viator_gui/Widgets/NumberBox.cpp"
#include "viator_gui/Widgets/StyleSheet.cpp"
#include "viator_gui/Widgets/FilmStripKnob.cpp"
#include "viator_gui/Widgets/Menu.cpp"
#include "viator_gui/Widgets/TextButton.cpp"
#include "viator_gui/Widgets/Tooltip.cpp"

/** Viator LAF Headers*/
#include "viator_gui/LAF/MenuLAF.cpp"
#include "viator_gui/LAF/FaderLAF.cpp"
#include "viator_gui/LAF/DialLAF.cpp"
#include "viator_gui/LAF/TextButtonLAF.cpp"
#include "viator_gui/LAF/SettingsLAF.cpp"

