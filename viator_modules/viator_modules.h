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
#include "viator_dsp/Expander.h"
#include "viator_dsp/Tube.h"
#include "viator_dsp/Denoiser.h"
#include "viator_dsp/ModuleBase.h"
#include "viator_dsp/Compressor.h"

/** Viator GUI Headers*/
#include "viator_gui/Widgets/Dial.h"
#include "viator_gui/Widgets/Fader.h"
#include "viator_gui/Widgets/Label.h"
#include "viator_gui/Widgets/NumberBox.h"
#include "viator_gui/Widgets/StyleSheet.h"
#include "viator_gui/Widgets/FilmStripKnob.h"
#include "viator_gui/Widgets/Menu.h"
#include "viator_gui/Widgets/TextButton.h"
#include "viator_gui/Widgets/Tooltip.h"
#include "viator_gui/Widgets/Meter.h"
#include "viator_gui/Widgets/Scope.h"
#include "viator_gui/Widgets/VUMeter.h"
#include "viator_gui/Widgets/LedMeter.h"
#include "viator_gui/Widgets/ImageFader.h"
#include "viator_gui/Widgets/ImageButton.h"

/** Viator LAF Headers*/
#include "viator_gui/LAF/MenuLAF.h"
#include "viator_gui/LAF/FaderLAF.h"
#include "viator_gui/LAF/DialLAF.h"
#include "viator_gui/LAF/TextButtonLAF.h"
#include "viator_gui/LAF/SettingsLAF.h"
#include "viator_gui/LAF/MeterLAF.h"
#include "viator_gui/LAF/BorderLAF.h"

/** Viator Utils Headers*/
#include "viator_utils/utils.h"
#include "viator_utils/Colors/Gradient.h"
#include "viator_utils/Window/Window.h"
#include "viator_utils/DSP/dsp.h"
