# Viator DSP JUCE Plugin Framework
 [![License: GPL v3](https://img.shields.io/badge/License-GPLv3-brightgreen.svg)](https://www.gnu.org/licenses/gpl-3.0)
[![Downloads](https://img.shields.io/github/downloads/landonviator/viatordsp/total)](https://somsubhra.github.io/github-release-stats/?username=landonviator&repository=viatordsp&page=1&per_page=30)

## Description
The viatordsp framework is made up of dsp and gui classes that help make creating plugins faster, easier, and more fun!
This contains dsp classes such as clippers, filters, compressors, and much more to come.
The gui contains stylized versions of JUCE's built-in widgets (like sliders and comboboxes) that have their own lookandfeel overrides to make them look awesome!

<br><br>Here is a plugin using those stylized components.
![Pic](https://github.com/landonviator/viatordsp/blob/main/Assets/btclipper.png)

## Installation
Clone the repo viatordsp or download it as a zip. Cloning it would be better, since when there is an update, you simply pull the changes without needing to doanload another version of the zip file. 
Just include the viator_modules folder in the Projucer's module window like the inamge below and you're all set! 

## Use
To use viatordsp, there are three namespace: 
- viator_dsp
- viator_gui
- viator_utils

<br><br> You can create an instance of a class in the folder viator_dsp, like the HardClipper, with:
- viator_dsp::HardClipper hardClipper; // In the PluginProcessor.h

<br><br> Or a gui component inside of viator_gui/Widgets, like a dial, with:
- viator_gui::LV_Dial dial; // In the PluginEditor.h
