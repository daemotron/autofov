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

## Important Note
Please note that AutoFoV will detect a default FoV from X-Plane's settings, and
will restore this FoV value during shutdown, ensuring X-Plane writes this default
value back into its configuration files, and not any value temporarily set for
a specific aircraft. **This behaviour however prevents you from setting a new default
FoV value in X-Plane's settings dialogue while AutoFoV is loaded** - AutoFoV will
override this newly set value during shutdown and revert X-Plane's settings back
to their original value.

To work around this limitation, open the plugin manager and disable AutoFoV before
configuring a new default field of view in X-Plane's setting dialogue. Shut down
X-Plane without re-enabling AutoFoV, and your new FoV default value should be
saved in X-Plane's configuration files. Once loading X-Plane again, AutoFoV will
initialize this new FoV value as its default.

# Building AutoFoV

## Prerequisites
* [CMake](https://cmake.org/) 3.2 or newer
* A copy of the [X-Plane SDK](https://developer.x-plane.com/sdk/plugin-sdk-downloads/), placed in the `SDK` folder (same level as `src`)

### Windows
* Mingw-w64 for Win64 (https://winlibs.com/)
* [Cmder](https://cmder.app/) console emulator (recommended, but no strict requirement)

NB: make sure to add the Mingw bin directory to your PATH environment variable

### Linux
* gcc
* GNU make

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
