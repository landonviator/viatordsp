/** BEGIN_JUCE_MODULE_DECLARATION

    ID:            viator_modules
    vendor:         ViatorDSP
    version:        0.0.1
    name:           Landon Viator
    description:    I make plugins and noise
    website:        https://www.patreon.com/ViatorDSP
    license:        Proprietary

    dependencies:

    END_JUCE_MODULE_DECLARATION
*/

#pragma once
#define VIATOR_MODULES_H_INCLUDED

#include <juce_core/juce_core.h>
#include <juce_events/juce_events.h>

/** Viator DSP Headers*/
#include "viator_dsp/Distortion.h"
#include "viator_dsp/SVFilter.h"
#include "viator_dsp/LFOGenerator.h"
#include "viator_dsp/MultiBandProcessor.h"
#include "viator_dsp/BitCrusher.h"
#include "viator_dsp/BrickWallLPF.h"

/** Viator GUI Headers*/
#include "viator_gui/Widgets/Toggle.h"
#include "viator_gui/Widgets/ToggleButton.h"
#include "viator_gui/Widgets/Dial.h"
#include "viator_gui/Widgets/Fader.h"
#include "viator_gui/Widgets/Border.h"
#include "viator_gui/Widgets/Label.h"
#include "viator_gui/Widgets/LEDButton.h"
#include "viator_gui/Widgets/Menu.h"
#include "viator_gui/Widgets/PushButton.h"
#include "viator_gui/Widgets/NumberBox.h"
#include "viator_gui/Widgets/PushButton.h"
#include "viator_gui/Widgets/StyleSheet.h"
#include "viator_gui/Widgets/Menu_Styles.h"
#include "viator_gui/Widgets/FilmStripKnob.h"
#include "viator_gui/Widgets/FilmStripFader.h"

/** Viator Utils Headers*/
#include "viator_utils/utils.h"
