# About AutoFoV
This is a plugin for the [X-Plane](https://www.x-plane.com/) flight simulator,
automatically setting the field of view based on the currently loaded aircraft.

### Compatibility
AutoFoV is compatible with X-Plane 11 (from version 11.10) and X-Plane 12.
Earlier versions of X-Plane are not supported.

* The Windows build has been compiled on Windows 11 using MinGW-w64 10.0.0 (UCRT)
* The Mac build has been compiled on macOS 10.15 "Catalina".
* The Linux build has been compiled on Ubuntu Linux 20.04 LTS

# Quick Start Guide

## Downloading AutoFoV
You can download AutoFoV from the [Release Page](https://github.com/daemotron/autofov/releases)
of its public GitHub repository. From the *Assets* section, download the file
`AutoFoV.zip` for the latest version. The files labeled *Source Code* are
***not*** what you want.

## Installing AutoFoV
AutoFoV comes in X-Plane's *fat plugin* format. Simply extract the directory
`AutoFoV` from the zip file and place it as a sub-folder into the `Resources/plugins`
folder of your X-Plane installation.

### Windows 8 or 8.1 Users Please Note
This plugin has been compiled using Microsoft's Universal C Runtime (UCRT), which by
default is available in Windows 10 and newer versions. To install UCRT on older Windows
versions, please cf. to [Update for Universal C Runtime in Windows](https://support.microsoft.com/en-us/topic/update-for-universal-c-runtime-in-windows-c0514201-7fe6-95a3-b0a5-287930f3560c).

## Using AutoFoV
AutoFoV allows to define a custom field of view for each aircraft model (i.e. for each
`.acf` file in your X-Plane's `aircraft` folder and its subfolders). To define a custom
field of view, simply create an empty file in the same folder and with the same name as
the `.acf` file, but suffixed with `.fov` instead of `.acf`, and populate it with the
numeric FoV value you want to use with this aircraft (only digits 0-9 and the decimal
dot are allowed).

### Example
The default Cessna 172's `.acf` file path is

```
Aircraft/Laminar Research/Cessna 172 SP/Cessna_172SP.acf
```

If you want to customize its FoV, simply create the file

```
Aircraft/Laminar Research/Cessna 172 SP/Cessna_172SP.fov
```

and open it with a text editor. Right at the beginning of the file, place the FoV value
you want to use with this aircraft. Make sure your text editor saves the file as plain
text without byte order mark. A valid file could contain e.g.

```
65
```

or

```
65.0
```

to configure a custom field of view of 65 degrees.

## Configuring AutoFoV
AutoFoV uses a configuration file, stored under `Output/autofov/config.txt`
(relative to X-Plane's root directory). The file looks like this:

```ini
# AutoFoV Configuration
# =====================

# Default FoV to be used when no aircraft-specific FoV is defined
fov_default = 60.00
```

When run for the first time, AutoFoV will detect a default FoV from X-Plane's
settings, and use it to initialize this file (if it doesn't exist already). You
can adjust the default FoV value to your liking, if the detected value is not
what you want.

# Building AutoFoV

## Prerequisites
* [Git](https://git-scm.com/) 2.14 or newer
* [CMake](https://cmake.org/) 3.2 or newer
* A copy of the [X-Plane SDK](https://developer.x-plane.com/sdk/plugin-sdk-downloads/), placed in the `SDK` folder (same level as `src`)

### Windows
* Mingw-w64 for Win64 (https://winlibs.com/)
* [Cmder](https://cmder.app/) console emulator (recommended, but no strict requirement)

**NB:** make sure to add the Mingw bin directory to your PATH environment variable

### macOS
* Xcode and/or Xcode command line utilities

### Linux
* gcc
* GNU make

## Get the Source Code
AutoFoV uses [XPPL](https://github.com/daemotron/xppl) as a submodule. When cloning or
updating the AutoFoV sources, you also need to check out the corresponding XPPL submodule.

### Fresh Clone
```
git clone --recurse-submodules https://github.com/daemotron/autofov.git
```

Alternatively, you can clone and checkout in two separate steps:

```
git clone https://github.com/daemotron/autofov.git
cd autofov
git submodule update --init --recursive
```

### Update Existing Clone
```
git pull --recurse-submodules
```

### Update XPPL to the Latest Version
Caution: XPPL updates must be separated from feature development, since they could
potentially break existing code.

```
git submodule update --remote xppl
```

## Compiling

### Windows
```
mkdir build
cd build
cmake -G "MinGW Makefiles" ../
mingw32-make
```

This will create a file called `AutoFoV.xpl` within your `build` directory.
To package a fat plugin, place this file withing the `win_x64` subfolder of the
plugin's main directory.

### macOS
```
mkdir build
cd build
cmake ../
make
```

This will create a file called `AutoFoV/mac_x64/AutoFoV.xpl` within your `build`
directory, ready to be packaged and shipped.

**NB:** The Mac plugin is a hybrid build for both, x86_64 and arm64, running natively
on both, Intel-based and Silicon-based Mac computers.

### Linux
```
mkdir build
cd build
cmake ../
make
```

This will create a file called `AutoFoV/mac_x64/AutoFoV.xpl` within your `build`
directory, ready to be packaged and shipped.
