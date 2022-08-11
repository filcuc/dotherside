# DOtherSide
[![License](https://img.shields.io/badge/license-LGPL-green.svg)](https://github.com/filcuc/DOtherSide/blob/master/LICENSE)
[![CI](https://github.com/filcuc/dotherside/workflows/CI/badge.svg)](https://github.com/filcuc/dotherside/actions?query=workflow%3ACI+branch%3Amaster)
[![codecov](https://codecov.io/gh/filcuc/dotherside/branch/master/graph/badge.svg)](https://codecov.io/gh/filcuc/dotherside)
[![Documentation Status](https://img.shields.io/badge/read-documentation-blue.svg)](https://filcuc.github.io/dotherside/)

C language library for creating bindings for the Qt QML language.

Documentation: https://filcuc.github.io/dotherside/

Currently the DOtherSide library is used by the following bindings:
* [nimqml](https://github.com/filcuc/nimqml), QML bindings for the Nim programming language
* [qml_zig](https://github.com/kassane/qml_zig), QML bindings for the Zig programming language

It was historically used by: 
* [dqml](https://github.com/filcuc/dqml), QML bindings for the D programming language
* [qml-rust](https://github.com/White-Oak/qml-rust), QML bindings for the Rust programming language

## Supported features
The following features are implementable from a binding language
* Creation of custom QObject
* Creation of custom QAbstractItemModels (Lists, Tables and Trees)
* Creation of custom properties, signals and slots
* Creation of QObjects from QML
* Registration of singletons in QML
* Creation of custom image providers

## Prebuilt binaries
Currently we provide the prebuilt binaries for Windows through the
GitHub [releases](https://github.com/filcuc/DOtherSide/releases) page
or directly as artifacts from Github actions

## Change log
The project change log can be read [here](./CHANGELOG.md).

## Supported platforms
Currently we support the following platforms/compilers:
- Linux both 32/64bit with gcc
- Windows 32/64bit with Visual Studio 2013|2015 Community Edition

## Build requirements
You need the following software:
* Qt 5.12 or higher or Qt 6.2 or higher
* Linux: gcc 4.8 or later with c++11 support or higher
* Windows: Visual Studio 2013|2015 Community Edition (Windows) or higher

## Qt5 and Qt6 Notes
We support both Qt5 and Qt6 builds but we don't support coesisteance of the DOtherSide library 
compiled in both ways. In other words the DOtherSide so name is the same compiled with Qt5 or Qt6.
This is a current limitation but we could change this in future.

## Build instructions:
```
cd /path/to/cloned/repo
mkdir build
cd build
cmake ..
cmake --build .
```

## Install Instructions
Once you built the package just type
```
make install
```
by default cmake will install to the default CMAKE prefix.
If you want to customize this location type the following command
during the build steps when invoking cmake
```
cmake -DCMAKE_INSTALL_PREFIX:PATH=/path/to/install/prefix path/to/CMakeLists.txt
```
