# Viator DSP JUCE Plugin Library
 [![License: GPL v3](https://img.shields.io/badge/License-GPLv3-brightgreen.svg)](https://www.gnu.org/licenses/gpl-3.0)
[![Downloads](https://img.shields.io/github/downloads/landonviator/viatordsp/total)](https://somsubhra.github.io/github-release-stats/?username=landonviator&repository=viatordsp&page=1&per_page=30)

## Description
The viatordsp framework is made up of [dsp](https://github.com/landonviator/viatordsp/tree/main/viator_modules/viator_dsp) and [gui](https://github.com/landonviator/viatordsp/tree/main/viator_modules/viator_gui) classes that help make creating plugins faster, easier, and more fun!
This contains dsp classes such as clippers, filters, compressors, and much more to come.
The gui contains stylized versions of JUCE's built-in widgets (like sliders and comboboxes) that have their own lookandfeel overrides to make them look awesome!

<br>Here is a plugin using those stylized components.<br><br>
![Pic](https://github.com/landonviator/viatordsp/blob/main/Assets/btclipper.png)

## Installation
Clone the [repo](https://github.com/landonviator/viatordsp) viatordsp or download it as a zip. Cloning it would be better, since when there is an update, you simply pull the changes without needing to download another version of the zip file.  
<br>Just include the viator_modules folder in the Projucer's module window like the inamge below and you're all set! <br><br>
![Pic](https://github.com/landonviator/viatordsp/blob/main/Assets/projucer.png)

## Use
To use viatordsp, there are three namespace: 
- viator_dsp
- viator_gui
- viator_utils

You can create an instance of a class in the folder viator_dsp, like the HardClipper, with:
- viator_dsp::HardClipper hardClipper (In the PluginProcessor.h)

Or a gui component inside of viator_gui/Widgets, like a dial, with:
- viator_gui::LV_Dial dial (In the PluginEditor.h)

## Contributing
Contributions are most welcome! Check out the [issues](https://github.com/landonviator/viatordsp/issues) page for more details.

## License
viatordsp is licensed under the GNU General Public License (GPLv3) agreement.
