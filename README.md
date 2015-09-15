# DOtherSide
[![Build Status](https://travis-ci.org/filcuc/DOtherSide.svg?branch=develop)](https://travis-ci.org/filcuc/DOtherSide)

C language library for creating bindings for the Qt QML language.

Currently the DOtherSide library is used by the following bindings:
* [nimqml](https://github.com/filcuc/nimqml), QML bindings for the Nim programming language
* [dqml](https://github.com/filcuc/dqml), QML bindings for the D programming language

## Supported platforms
Currently we support the following platforms/compilers:
- Linux both 32/64bit with gcc
- Windows 32/64bit with Visual Studio 2013 Community Edition

## Change log
The project change log can be read [here](./CHANGELOG.md).

## Build requirements
You need the following software:
* Qt 5.3 or higher
* Linux: gcc 4.8 or later with c++11 support or higher
* Windows: Visual Studio 2013 Community Edition (Windows) or higher
* Windows: MingGW 4.9.2 or higher

## Build instructions:
1. Open a shell terminal inside the cloned repo
2. mkdir build && cd build
3. cmake ..
4. make

## Install Instructions
Copy the libDOtherSide.so from the build dir to your system lib i.e /usr/lib
