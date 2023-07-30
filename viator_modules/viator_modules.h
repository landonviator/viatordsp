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

#include <juce_audio_basics/juce_audio_basics.h>
#include <juce_audio_devices/juce_audio_devices.h>
#include <juce_audio_formats/juce_audio_formats.h>
#include <juce_audio_processors/juce_audio_processors.h>
#include <juce_audio_utils/juce_audio_utils.h>
#include <juce_core/juce_core.h>
#include <juce_data_structures/juce_data_structures.h>
#include <juce_dsp/juce_dsp.h>
#include <juce_events/juce_events.h>
#include <juce_graphics/juce_graphics.h>
#include <juce_gui_basics/juce_gui_basics.h>
#include <juce_gui_extra/juce_gui_extra.h>
#include "viator_utils/utils.h"

/** Viator DSP Headers*/
#include "viator_dsp/Distortion/Distortion.h"
#include "viator_dsp/Filter/SVFilter.h"
#include "viator_dsp/Filter/MultiBandProcessor.h"
#include "viator_dsp/Distortion/BitCrusher.h"
#include "viator_dsp/Filter/BrickWallLPF.h"
#include "viator_dsp/Dynamics/Expander.h"
#include "viator_dsp/Distortion/Tube.h"
#include "viator_dsp/Dynamics/Denoiser.h"
#include "viator_dsp/ModuleBase.h"
#include "viator_dsp/Dynamics/Compressor.h"
#include "viator_dsp/Filter/FastFilter.h"

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
