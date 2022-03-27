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
#include "viator_dsp/Clipper.h"
#include "viator_dsp/svfilter.h"
#include "viator_dsp/WaveShaper.h"
#include "viator_dsp/Saturation.h"
#include "viator_dsp/LFOGenerator.h"

/** Viator GUI Headers*/
#include "viator_gui/Widgets/Toggle.h"
#include "viator_gui/Widgets/Dial.h"
#include "viator_gui/Widgets/Fader.h"
#include "viator_gui/Widgets/Border.h"
#include "viator_gui/Widgets/Label.h"
#include "viator_gui/Widgets/Menu.h"
#include "viator_gui/Widgets/PushButton.h"
#include "viator_gui/Widgets/NumberBox.h"
#include "viator_gui/Widgets/PushButton.h"
#include "viator_gui/Widgets/StyleSheet.h"

/** Viator Utils Headers*/
#include "viator_utils/utils.h"
