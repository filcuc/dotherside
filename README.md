# DOtherSide

[![Build Status](https://travis-ci.org/filcuc/DOtherSide.svg?branch=develop)](https://travis-ci.org/filcuc/DOtherSide)

## Description

Qml bindings for both D and Nim programming languages

## Supported features:
* Creation of custom QObject and inject in a qml QtQuick view (both Nim and D)
* Slot and Signal creation for the following types int, bool, string (both Nim and D)
* Creation of properties for databinding (both Nim and D)
* Subclassing of QAbstractListModels [both Nim and D)

## Supported Platforms
Currently we support the following platforms/compilers:
- Linux both 32/64bit with gcc
- Windows 32/64bit with Visual Studio 2013 Community Edition

## Change log
The project change log can be read [here](./CHANGELOG.md).

## Documentation
The documentation for the Nim programming language can be
read [here](http://filcuc.github.io/DOtherSide/ "").

For the D programming language is an on going project
and pull request are accepted.

## Build Instructions and requirements
You need the following software:
* Qt 5.3 or higher
* dmd 2.065 or higher
* Linux: gcc 4.8 or later with c++11 support or higher
* Windows: Visual Studio 2013 Community Edition (Windows) or higher
* Windows: MingGW 4.9.2 or higher
* nim 0.10.3 or higher

Build instructions:
1. Open a shell terminal inside the cloned repo
2. mkdir build && cd build
3. cmake ..
4. make

## Install Instructions
For the DOtherSide C++ bridge:

1. Copy the libDOtherSide.so from the build dir to your system lib i.e /usr/lib

For NimQml use the Nimble package manager:

1. Open a shell and navigate to the NimQml subdirectory
2. Type: nimble install
3. Now you can use it in your .nim files
