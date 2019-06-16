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
It requires an MPlayer executable. Some popular players (like SMPlayer) comes with a suitable MPlayer that can be used with Translucent MPlayer. If you don't have one
you can download one from the [official MPlayer website](http://www.mplayerhq.hu). 

## Options
Translucent MPlayer it's not a full featured frontent, it only supports a minimal set of options:
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
Download and execute the latest installer from the [releases](https://github.com/FelixdelasPozas/TranslucentMPlayer/releases) page. 

# Screenshots
MPlayer executable configuration and detection.

![configuration](https://cloud.githubusercontent.com/assets/12167134/11912577/19d07d4a-a643-11e5-998c-95366e4cc673.jpg)

Video display settings. 

![videoconf](https://cloud.githubusercontent.com/assets/12167134/11912580/1a3d6626-a643-11e5-940e-6dc2b907a18c.jpg)

The video is completely transparent to events so the only way to control it is from the tray menu. The menu has widgets to play & pause the current video, volume modification & mute, and the current play list. 

![trayicon](https://cloud.githubusercontent.com/assets/12167134/11912579/19db2376-a643-11e5-9eea-7f5b928991f9.jpg)

Watching a movie while coding...

![example](https://cloud.githubusercontent.com/assets/12167134/11912578/19d569fe-a643-11e5-9a27-7e2f6e7ae9c2.jpg)

# Repository information

**Version**: 1.1.3

**Status**: finished

**License**: GNU General Public License 3

**cloc statistics**

| Language                     |files          |blank        |comment           |code  |
|:-----------------------------|--------------:|------------:|-----------------:|-----:|
| C++                          |   9           | 349         |   261            | 1411 |
| C/C++ Header                 |   8           | 179         |   518            |  306 |
| CMake                        |   1           |  17         |    13            |   61 |
| **Total**                    | **18**        | **545**     | **792**          | **1778** |
