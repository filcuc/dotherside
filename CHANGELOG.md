# Version 0.4.5
* Removed the D bindings
* Removed the Nim bindings

# Version 0.4.2
* [DOtherSide] Code cleanup and little refactoring
* [NimQml] Made nim compiles with the "cpp" option by default. This should fix C/C++ interop problems

# Version 0.4.1
* [DQml] Added support for code generation of slots, signals and properties by using custom UDAs
* [DQml] Updated the examples with the new attributes for code generation
* [NimQml] Little fix for adding fixing compilation with Nim 0.11.0

# Version 0.4.0
* [DQml] Inheritance of slots and signals is now supported
* [DQml] Added support for QAbstractListModel subclasses
* [DQml] Put on par the examples for matching those in NimQml
* [NimQml] Fixed AbstractItemModel example
* [NimQml] Initial support for windows builds with Visual Studio community edition
* [DOtherSide] Initial support for windows build
* [DOtherSide] Removed most warnings and code cleanup

# Version 0.3.0
* [NimQml] Added support for QAbstractListModel subclasses
* [NimQml] Fixed QtObject macro wrong reorder of the methods and proc declaration (thanks to Will)
* [NimQml] Added new ContactApp example
* [NimQml] Added optional support for finalizers
* [DOtherSide] Added support for injecting the DynamicQObject as behaviour to QObject subclasses
* [DotherSide] Added support for QAbstractListModel subclasses

# Version 0.2.0
* [DQml] Initial support for properties creation
* [NimQml] Added new macro syntax for creating QObject derived object (thanks to Will)

# Version 0.1.0
* [DOtherSide] Initial version with support for QObject Slot, Signal and Properties creation
* [DQml] Initial support for Slot and Signal creation
* [NimQml] Initial support for Slot, Signal and Properties creation
