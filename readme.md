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
* [Qt Library](http://www.qt.io/).
* [MPlayer](http://www.mplayerhq.hu/).

# Install

Translucent MPlayer is available for Windows 7 onwards. You can download the latest installer from the [releases page](https://github.com/FelixdelasPozas/TranslucentMPlayer/releases). Neither the application or the installer are digitally signed so the system will ask for approval before running it the first time.

# Screenshots

> **_NOTE:_**  Some screenshots are from older versions. Latest version might be slightly different. 

MPlayer executable configuration and detection.

![configuration](https://github.com/user-attachments/assets/8f31b8cc-44df-44f6-b9e4-8fa73b2c8a8a)

Video display settings. 

![videoconf](https://github.com/user-attachments/assets/f756273e-89a5-4cd7-99c7-07cfeb79cf4d)

The video is completely transparent to events so the only way to control it is from the tray menu. The menu has widgets to play & pause the current video, volume modification & mute, the current play list and full-screen mode toggle. 

![trayicon](https://github.com/user-attachments/assets/b1b0927f-32c4-4aa7-b6e4-fc3c5a806f0a)

Watching a movie while coding...

![example](https://github.com/user-attachments/assets/552cf476-56a2-47c4-b8a9-c11c886d6da2)

# Repository information

**Version**: 1.4.0

**Status**: finished

**License**: GNU General Public License 3

**cloc statistics**

| Language                     |files          |blank        |comment           |code  |
|:-----------------------------|--------------:|------------:|-----------------:|-----:|
| C++                          |   10          | 394         |   286            | 1622 |
| C/C++ Header                 |   9           | 200         |   578            |  353 |
| CMake                        |   1           |  16         |     7            |   62 |
| **Total**                    | **20**        | **610**     | **871**          | **2037** |
