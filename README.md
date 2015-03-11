# DOtherSide
Qml bindings for both D and Nim programming languages

## Change log
The project change log can be read [here](./CHANGELOG.md).

## Documentation
The documentation for the Nim programming language can be
read [here](http://filcuc.github.io/DOtherSide/ "").

For the D programming language is an on going project
and pull request are accepted.

## Supported Platforms and Requirements
Currently we support the following platforms/compilers:
- Linux both 32/64bit with gcc
- Windows 32/64bit with Visual Studio 2013 Community Edition 

You need the following software:
* Qt 5.3
* dmd 2.065
* gcc 4.8 or later with c++11 support (Linux)
* Visual Studio 2013 Community Edition (Windows)
* nim 0.10.2

## Build Instructions
1. Open a shell terminal inside the cloned repo
2. mkdir build && cd build
3. cmake ..
4. make

## Install Instructions
For the C++ bridge:

1. Copy the libDOtherSide.so from the build dir to your system lib i.e /usr/lib

For NimQml use the Nimble package manager:

1. Open a shell and navigate to the NimQml subdirectory
2. Type: nimble install
3. Now you can use it in your .nim files

## Supported features:
* Creation of custom QObject and inject in a qml QtQuick view (both Nim and D)
* Slot and Signal creation for the following types int, bool, string (both Nim and D)
* Creation of properties for databinding (both Nim and D)




