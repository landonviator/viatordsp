# Viator DSP JUCE Plugin Library
 [![License: GPL v3](https://img.shields.io/badge/License-GPLv3-brightgreen.svg)](https://www.gnu.org/licenses/gpl-3.0)
[![Downloads](https://img.shields.io/github/downloads/landonviator/viatordsp/total)](https://somsubhra.github.io/github-release-stats/?username=landonviator&repository=viatordsp&page=1&per_page=30)

## Description
The viatordsp library is made up of [dsp](https://github.com/landonviator/viatordsp/tree/main/viator_modules/viator_dsp) and [gui](https://github.com/landonviator/viatordsp/tree/main/viator_modules/viator_gui) classes that help make creating plugins faster, easier, and more fun!
The dsp namespace contains dsp classes such as clippers, filters, and much more to come.
The gui namespace contains stylized versions of JUCE's built-in widgets (like sliders and comboboxes) that have their own lookandfeel overrides to make them look awesome!

## DISCLAIMER
I unfortunately cannot give you permission to use the gui objects that have images attached to them per the license of the images. You can however copy the logic and apply your own images to them!

## Installation
Clone the [repo](https://github.com/landonviator/viatordsp) viatordsp or download it as a zip. Cloning it would be better, since when there is an update, you simply pull the changes without needing to download another version of the zip file.  
<br>Just include the viator_modules folder in the Projucer's module window.

## Use
To use viatordsp, there are three namespaces: 
- viator_dsp
- viator_gui
- viator_utils

You can create an instance of a class in the folder viator_dsp, like the Distortion, with:
- viator_dsp::Distortion<float> distortion (In the PluginProcessor.h)

Update parameters, e.g.:
- distortion.setClipperType(viator_dsp::Distortion::ClipperType::kSoft);

Be sure to call the prepare method of every DSP module in the PluginProcessor.cpp's prepare method!

Or a gui component inside of viator_gui/Widgets, like a dial, with:
- viator_gui::Dial dial {" textValueSuffix", rangeStart, rangeEnd, rangeInterval, returnValue} (In the PluginEditor.h)

## Contributing
Contributions are most welcome! Check out the [issues](https://github.com/landonviator/viatordsp/issues) page for more details.

## License
viatordsp is licensed under the GNU General Public License (GPLv3) agreement.

## Support
If you like my work and would like to support me creating more audio applications, check out my [Patreon](https://www.patreon.com/ViatorDSP) where you can donate and download all of my current plugins!

## Online Presence:
- I stream JUCE development on [Twitch](https://www.twitch.tv/dr_bruisin) & [YouTube](https://www.youtube.com/channel/UCwEc_CsAk3ky7sX_yg6bSSg) Tuesdays and Thursdays!
- [Patreon](https://www.patreon.com/ViatorDSP) <br>
- [Instagram](https://www.instagram.com/viatordsp/) <br>
- [Facebook](https://www.facebook.com/Dr-Bruisin-109544051551604)<br>
- Join my [Discord](https://discord.gg/PgU3Dd8vxJ) server!
