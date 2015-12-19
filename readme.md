Translucent MPlayer
===================

# Summary
- [Description](#description)
- [Compilation](#compilation-requirements)
- [Install](#install)
- [Screenshots](#screenshots)
- [Repository information](#repository-information)

# Description
Translucent MPlayer is a mplayer frontend for displaying a always-on-top, translucent, borderless and transparent to events (click-throught) video on the desktop.

## Options
It's not a full featured frontent supporting only a minimal set of options:
* Brightness, contrast, hue, saturation and gamma configuration for video display.
* Video opacity configuration. 
* Playlist support. 
* Subtitles support. 
* Video geometry can be configured in size and can be positioned in several preset positions depending on desktop configuration (multiple monitors supported).
* Controlled and configured from a tray icon menu. 

# Compilation requirements
## To build the tool:
* cross-platform build system: [CMake](http://www.cmake.org/cmake/resources/software.html).
* compiler: [Mingw64](http://sourceforge.net/projects/mingw-w64/) on Windows.

## External dependencies
The following libraries are required:
* [Qt 5 opensource framework](http://www.qt.io/).
* [MPlayer](http://www.mplayerhq.hu/).

# Install
The only current option is build from source as binaries are not provided. 

# Screenshots
MPlayer executable configuration and detection.

![configuration]()

Video display settings. 

![settings]()

The video is completely transparent to events so the only way to control it is from the tray menu. The menu has widgets to play & pause the current video, volume modification & mute, and the current play list. 

![trayicon]()

Watching a movie while coding...

![example]()

# Repository information

**Version**: 1.1.0

**Status**: finished

**cloc statistics**

| Language                     |files          |blank        |comment           |code  |
|:-----------------------------|--------------:|------------:|-----------------:|-----:|
| C++                          |   9           | 341         |   260            | 1398 |
| C/C++ Header                 |   8           | 179         |   518            |  306 |
| CMake                        |   1           |  17         |    13            |   60 |
| **Total**                    | **18**        | **537**     | **791**          | **1764** |
