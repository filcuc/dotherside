## NimQml aims to provide binding to the QML for the Nim programming language
##
## Optional finalizers
## -------------------
## To enable finalizers you must define ``nimqml_use_finalizers`` by passing
## the option, ``-d:nimqml_use_finalizers``, to the Nim compiler. The relevant
## delete method will then be called automatically by the garbage collector.
## Care should be taken when using this approach as there are no guarantees
## when a finalzier will be run, or if, indeed, it will run at all.
include private/NimQmlTypes
include private/NimQmlGlobal
include private/QMetaType
include private/QVariant
include private/QQmlApplicationEngine
include private/QQmlContext
include private/QApplication
include private/QObject
include private/QQuickView
include private/QModelIndex
include private/QHashIntByteArray
include private/QAbstractListModel

  
