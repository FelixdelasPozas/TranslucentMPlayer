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
* Fullscreen mode support (full size on the specified screen).

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

> **_NOTE:_**  Some screenshots are from older versions. Latest version might be slightly different. 

MPlayer executable configuration and detection.

![configuration](https://cloud.githubusercontent.com/assets/12167134/11912577/19d07d4a-a643-11e5-998c-95366e4cc673.jpg)

Video display settings. 

![videoconf](https://cloud.githubusercontent.com/assets/12167134/11912580/1a3d6626-a643-11e5-940e-6dc2b907a18c.jpg)

The video is completely transparent to events so the only way to control it is from the tray menu. The menu has widgets to play & pause the current video, volume modification & mute, the current play list and full-screen mode toggle. 

![trayicon](https://user-images.githubusercontent.com/12167134/168468708-55e3f730-7d7e-454c-bef4-6a4feb4a05be.png)

Watching a movie while coding...

![example](https://cloud.githubusercontent.com/assets/12167134/11912578/19d569fe-a643-11e5-9a27-7e2f6e7ae9c2.jpg)

# Repository information

**Version**: 1.3.2

**Status**: finished

**License**: GNU General Public License 3

**cloc statistics**

| Language                     |files          |blank        |comment           |code  |
|:-----------------------------|--------------:|------------:|-----------------:|-----:|
| C++                          |   10          | 388         |   285            | 1590 |
| C/C++ Header                 |   9           | 199         |   574            |  351 |
| CMake                        |   1           |  17         |    13            |   62 |
| **Total**                    | **20**        | **604**     | **872**          | **2003** |
