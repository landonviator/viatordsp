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
#include "viator_dsp/SVFilter.h"

/** Viator GUI Headers*/
#include "viator_gui/Widgets/LV_Toggle.h"
#include "viator_gui/Widgets/LV_Dial.h"
#include "viator_gui/Widgets/LV_Fader.h"
#include "viator_gui/Widgets/LV_GroupComponent.h"
#include "viator_gui/Widgets/LV_Label.h"
#include "viator_gui/Widgets/LV_Menu.h"
#include "viator_gui/Widgets/LV_PushButton.h"
#include "viator_gui/Widgets/LV_NumberBox.h"
#include "viator_gui/Widgets/LV_PushButton.h"
#include "viator_gui/Widgets/StyleSheet.h"

/** Viator Utils Headers*/
#include "viator_utils/utils.h"
