import NimQmlTypes
import tables

## NimQml aims to provide binding to the QML for the Nim programming language

export QObject
export QApplication
export QVariant
export QQmlApplicationEngine
export QQmlContext

type QMetaType* {.pure.} = enum ## \
  ## Qt metatypes values used for specifing the 
  ## signals and slots argument and return types.
  ##
  ## This enum mimic the QMetaType::Type C++ enum
  UnknownType = cint(0), 
  Bool = cint(1),
  Int = cint(2), 
  QString = cint(10), 
  VoidStar = cint(31),
  QVariant = cint(41), 
  Void = cint(43)

proc debugMsg(message: string) = 
  echo "NimQml: ", message

proc debugMsg(typeName: string, procName: string) = 
  var message = typeName
  message &= ": "
  message &= procName
  debugMsg(message)

proc debugMsg(typeName: string, procName: string, userMessage: string) = 
  var message = typeName
  message &= ": "
  message &= procName
  message &= " "
  message &= userMessage
  debugMsg(message)

# QVariant
proc dos_qvariant_create(variant: var QVariant) {.cdecl, dynlib:"libDOtherSide.so", importc.}
proc dos_qvariant_create_int(variant: var QVariant, value: cint) {.cdecl, dynlib:"libDOtherSide.so", importc.}
proc dos_qvariant_create_bool(variant: var QVariant, value: bool) {.cdecl, dynlib:"libDOtherSide.so", importc.}
proc dos_qvariant_create_string(variant: var QVariant, value: cstring) {.cdecl, dynlib:"libDOtherSide.so", importc.}
proc dos_qvariant_create_qobject(variant: var QVariant, value: DynamicQObject) {.cdecl, dynlib:"libDOtherSide.so", importc.}
proc dos_qvariant_delete(variant: QVariant) {.cdecl, dynlib:"libDOtherSide.so", importc.}
proc dos_qvariant_isnull(variant: QVariant, isNull: var bool) {.cdecl, dynlib:"libDOtherSide.so", importc.}
proc dos_qvariant_toInt(variant: QVariant, value: var cint) {.cdecl, dynlib:"libDOtherSide.so", importc.}
proc dos_qvariant_toBool(variant: QVariant, value: var bool) {.cdecl, dynlib:"libDOtherSide.so", importc.}
proc dos_qvariant_toString(variant: QVariant, value: var cstring, length: var cint) {.cdecl, dynlib:"libDOtherSide.so", importc.}
proc dos_qvariant_setInt(variant: QVariant, value: cint) {.cdecl, dynlib:"libDOtherSide.so", importc.}
proc dos_qvariant_setBool(variant: QVariant, value: bool) {.cdecl, dynlib:"libDOtherSide.so", importc.}
proc dos_qvariant_setString(variant: QVariant, value: cstring) {.cdecl, dynlib:"libDOtherSide.so", importc.}
proc dos_chararray_delete(rawCString: cstring) {.cdecl, dynlib:"libDOtherSide.so", importc.}

proc create*(variant: var QVariant) =
  ## Create a new QVariant
  dos_qvariant_create(variant)

proc create*(variant: var QVariant, value: cint) = 
  ## Create a new QVariant given a cint value
  dos_qvariant_create_int(variant, value)

proc create*(variant: var QVariant, value: bool) =
  ## Create a new QVariant given a bool value  
  dos_qvariant_create_bool(variant, value)

proc create*(variant: var QVariant, value: string) = 
  ## Create a new QVariant given a string value
  dos_qvariant_create_string(variant, value)

proc create*(variant: var QVariant, value: QObject) =
  ## Create a new QVariant given a QObject
  dos_qvariant_create_qobject(variant, value.data)

proc delete*(variant: QVariant) = 
  ## Delete a QVariant
  debugMsg("QVariant", "delete")
  dos_qvariant_delete(variant)

proc isNull*(variant: QVariant): bool = 
  ## Return true if the QVariant value is null, false otherwise
  dos_qvariant_isnull(variant, result)

proc intVal*(variant: QVariant): int = 
  ## Return the QVariant value as int
  var rawValue: cint
  dos_qvariant_toInt(variant, rawValue)
  result = cast[int](rawValue)

proc `intVal=`*(variant: QVariant, value: int) = 
  ## Sets the QVariant value int value
  var rawValue = cast[cint](value)
  dos_qvariant_setInt(variant, rawValue)

proc boolVal*(variant: QVariant): bool = 
  ## Return the QVariant value as bool
  dos_qvariant_toBool(variant, result)

proc `boolVal=`*(variant: QVariant, value: bool) =
  ## Sets the QVariant bool value
  dos_qvariant_setBool(variant, value)

proc stringVal*(variant: QVariant): string = 
  ## Return the QVariant value as string
  var rawCString: cstring
  var rawCStringLength: cint
  dos_qvariant_toString(variant, rawCString, rawCStringLength)
  result = $rawCString
  dos_chararray_delete(rawCString)

proc `stringVal=`*(variant: QVariant, value: string) = 
  ## Sets the QVariant string value
  dos_qvariant_setString(variant, value)


# QQmlApplicationEngine
proc dos_qqmlapplicationengine_create(engine: var QQmlApplicationEngine) {.cdecl, dynlib:"libDOtherSide.so", importc.}
proc dos_qqmlapplicationengine_load(engine: QQmlApplicationEngine, filename: cstring) {.cdecl, dynlib:"libDOtherSide.so", importc.}
proc dos_qqmlapplicationengine_context(engine: QQmlApplicationEngine, context: var QQmlContext) {.cdecl, dynlib:"libDOtherSide.so", importc.}
proc dos_qqmlapplicationengine_delete(engine: QQmlApplicationEngine) {.cdecl, dynlib:"libDOtherSide.so", importc.}

proc create*(engine: var QQmlApplicationEngine) = 
  ## Create an new QQmlApplicationEngine
  dos_qqmlapplicationengine_create(engine)

proc load*(engine: QQmlApplicationEngine, filename: cstring) = 
  ## Load the given Qml file 
  dos_qqmlapplicationengine_load(engine, filename)

proc rootContext*(engine: QQmlApplicationEngine): QQmlContext =
  ## Return the engine root context
  dos_qqmlapplicationengine_context(engine, result)

proc delete*(engine: QQmlApplicationEngine) = 
  ## Delete the given QQmlApplicationEngine
  debugMsg("QQmlApplicationEngine", "delete")
  dos_qqmlapplicationengine_delete(engine)

# QQmlContext
proc dos_qqmlcontext_setcontextproperty(context: QQmlContext, propertyName: cstring, propertyValue: QVariant) {.cdecl, dynlib:"libDOtherSide.so", importc.}

proc setContextProperty*(context: QQmlContext, propertyName: string, propertyValue: QVariant) = 
  ## Sets a new property with the given value
  dos_qqmlcontext_setcontextproperty(context, propertyName, propertyValue)

# QApplication
proc dos_qguiapplication_create() {.cdecl, dynlib: "libDOtherSide.so", importc.}
proc dos_qguiapplication_exec() {.cdecl, dynlib:"libDOtherSide.so", importc.}
proc dos_qguiapplication_delete() {.cdecl, dynlib:"libDOtherSide.so", importc.}

proc create*(application: QApplication) = 
  ## Create a new QApplication
  dos_qguiapplication_create()

proc exec*(application: QApplication) =
  ## Start the Qt event loop
  dos_qguiapplication_exec()

proc delete*(application: QApplication) = 
  ## Delete the given QApplication
  dos_qguiapplication_delete()

# QObject
type QVariantArray {.unchecked.} = array[0..0, QVariant]
type QVariantArrayPtr = ptr QVariantArray

proc toVariantSeq(args: QVariantArrayPtr, numArgs: cint): seq[QVariant] =
  result = @[]
  for i in 0..numArgs-1:
    result.add(args[i])

proc toCIntSeq(metaTypes: openarray[QMetaType]): seq[cint] =
  result = @[]
  for metaType in metaTypes:
    result.add(cint(metaType))

type QObjectCallBack = proc(nimobject: ptr QObject, slotName: QVariant, numArguments: cint, arguments: QVariantArrayPtr) {.cdecl.}
    
proc dos_qobject_create(qobject: var DynamicQObject, nimobject: ptr QObject, qobjectCallback: QObjectCallBack) {.cdecl, dynlib:"libDOtherSide.so", importc.}
proc dos_qobject_delete(qobject: DynamicQObject) {.cdecl, dynlib:"libDOtherSide.so", importc.}
proc dos_qobject_slot_create(qobject: DynamicQObject, slotName: cstring, argumentsCount: cint, argumentsMetaTypes: ptr cint, slotIndex: var cint) {.cdecl, dynlib:"libDOtherSide.so", importc.}
proc dos_qobject_signal_create(qobject: DynamicQObject, signalName: cstring, argumentsCount: cint, argumentsMetaTypes: ptr cint, signalIndex: var cint) {.cdecl, dynlib:"libDOtherSide.so", importc.}
proc dos_qobject_signal_emit(qobject: DynamicQObject, signalName: cstring, argumentsCount: cint, arguments: ptr QVariant) {.cdecl, dynlib:"libDOtherSide.so", importc.}
proc dos_qobject_property_create(qobject: DynamicQObject, propertyName: cstring, propertyType: cint, readSlot: cstring, writeSlot: cstring, notifySignal: cstring) {.cdecl, dynlib:"libDOtherSide.so", importc.}

method onSlotCalled*(nimobject: QObject, slotName: string, args: openarray[QVariant]) =
  ## Called from the NimQml bridge when a slot is called from Qml.
  ## Subclasses can override the given method for handling the slot call
  discard()

proc qobjectCallback(nimobject: ptr QObject, slotName: QVariant, numArguments: cint, arguments: QVariantArrayPtr) {.cdecl, exportc.} =
  # forward to the QObject subtype instance
  nimobject[].onSlotCalled(slotName.stringVal, arguments.toVariantSeq(numArguments))

proc create*(qobject: var QObject) =
  ## Create a new QObject
  qobject.name = "QObject"
  qobject.slots = initTable[string,cint]()
  qobject.signals = initTable[string, cint]()
  dos_qobject_create(qobject.data, addr(qobject), qobjectCallback)

proc delete*(qobject: QObject) = 
  ## Delete the given QObject
  dos_qobject_delete(qobject.data)

proc registerSlot*(qobject: var QObject, 
                   slotName: string, 
                   metaTypes: openarray[QMetaType]) =
  ## Register a slot in the QObject with the given name and signature
  # Copy the metatypes array
  var copy = toCIntSeq(metatypes)
  var index: cint 
  dos_qobject_slot_create(qobject.data, slotName, cint(copy.len), cast[ptr cint](addr(copy[0])), index)
  qobject.slots[slotName] = index

proc registerSignal*(qobject: var QObject, 
                     signalName: string, 
                     metatypes: openarray[QMetaType]) =
  ## Register a signal in the QObject with the given name and signature
  var index: cint 
  if metatypes.len > 0:
    var copy = toCIntSeq(metatypes)
    dos_qobject_signal_create(qobject.data, signalName, cast[cint](copy.len), cast[ptr cint](addr(copy[0])), index)
  else:
    dos_qobject_signal_create(qobject.data, signalName, 0, cast[ptr cint](0), index)
  qobject.signals[signalName] = index

proc registerProperty*(qobject: var QObject, 
                       propertyName: string, 
                       propertyType: QMetaType, 
                       readSlot: string, 
                       writeSlot: string, 
                       notifySignal: string) =
  ## Register a property in the QObject with the given name and type.
  dos_qobject_property_create(qobject.data, propertyName, cast[cint](propertyType), readSlot, writeSlot, notifySignal)

proc emit*(qobject: QObject, signalName: string, args: openarray[QVariant] = []) =
  ## Emit the signal with the given name and values
  if args.len > 0: 
    var copy: seq[QVariant]
    for i in 0..args.len-1:
      copy.add(args[i])
    dos_qobject_signal_emit(qobject.data, signalName, args.len.cint, addr(copy[0]))
  else:
    dos_qobject_signal_emit(qobject.data, signalName, 0, nil)

# QQuickView
proc dos_qquickview_create(view: var QQuickView) {.cdecl, dynlib:"libDOtherSide.so", importc.}
proc dos_qquickview_delete(view: QQuickView) {.cdecl, dynlib:"libDOtherSide.so", importc.}
proc dos_qquickview_show(view: QQuickView) {.cdecl, dynlib:"libDOtherSide.so", importc.}
proc dos_qquickview_source(view: QQuickView, filename: var cstring, length: var int) {.cdecl, dynlib:"libDOtherSide.so", importc.}
proc dos_qquickview_set_source(view: QQuickView, filename: cstring) {.cdecl, dynlib:"libDOtherSide.so", importc.}

proc create(view: var QQuickView) =
  ## Create a new QQuickView
  dos_qquickview_create(view)

proc source(view: QQuickView): cstring = 
  ## Return the source Qml file loaded by the view
  var length: int
  dos_qquickview_source(view, result, length)

proc `source=`(view: QQuickView, filename: cstring) =
  ## Sets the source Qml file laoded by the view
  dos_qquickview_set_source(view, filename)

proc show(view: QQuickView) = 
  ## Sets the view visible 
  dos_qquickview_show(view)

proc delete(view: QQuickView) =
  ## Delete the given QQuickView
  dos_qquickview_delete(view)



