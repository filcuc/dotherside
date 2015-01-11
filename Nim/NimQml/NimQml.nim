include NimQmlTypes

## NimQml aims to provide binding to the QML for the Nim programming language

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

var qobjectRegistry = initTable[ptr QObjectObj, bool]()

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
proc dos_qvariant_create(variant: var RawQVariant) {.cdecl, dynlib:"libDOtherSide.so", importc.}
proc dos_qvariant_create_int(variant: var RawQVariant, value: cint) {.cdecl, dynlib:"libDOtherSide.so", importc.}
proc dos_qvariant_create_bool(variant: var RawQVariant, value: bool) {.cdecl, dynlib:"libDOtherSide.so", importc.}
proc dos_qvariant_create_string(variant: var RawQVariant, value: cstring) {.cdecl, dynlib:"libDOtherSide.so", importc.}
proc dos_qvariant_create_qobject(variant: var RawQVariant, value: RawQObject) {.cdecl, dynlib:"libDOtherSide.so", importc.}
proc dos_qvariant_create_qvariant(variant: var RawQVariant, value: RawQVariant) {.cdecl, dynlib:"libDOtherSide.so", importc.}
proc dos_qvariant_create_float(variant: var RawQVariant, value: cfloat) {.cdecl, dynlib:"libDOtherSide.so", importc.}
proc dos_qvariant_create_double(variant: var RawQVariant, value: cdouble) {.cdecl, dynlib:"libDOtherSide.so", importc.}
proc dos_qvariant_delete(variant: RawQVariant) {.cdecl, dynlib:"libDOtherSide.so", importc.}
proc dos_qvariant_isnull(variant: RawQVariant, isNull: var bool) {.cdecl, dynlib:"libDOtherSide.so", importc.}
proc dos_qvariant_toInt(variant: RawQVariant, value: var cint) {.cdecl, dynlib:"libDOtherSide.so", importc.}
proc dos_qvariant_toBool(variant: RawQVariant, value: var bool) {.cdecl, dynlib:"libDOtherSide.so", importc.}
proc dos_qvariant_toString(variant: RawQVariant, value: var cstring, length: var cint) {.cdecl, dynlib:"libDOtherSide.so", importc.}
proc dos_qvariant_setInt(variant: RawQVariant, value: cint) {.cdecl, dynlib:"libDOtherSide.so", importc.}
proc dos_qvariant_setBool(variant: RawQVariant, value: bool) {.cdecl, dynlib:"libDOtherSide.so", importc.}
proc dos_qvariant_setString(variant: RawQVariant, value: cstring) {.cdecl, dynlib:"libDOtherSide.so", importc.}
proc dos_qvariant_assign(leftValue: RawQVariant, rightValue: RawQVariant) {.cdecl, dynlib:"libDOtherSide.so", importc.}
proc dos_qvariant_toFloat(variant: QVariant, value: var cfloat) {.cdecl, dynlib:"libDOtherSide.so", importc.}
proc dos_qvariant_setFloat(variant: QVariant, value: float)  {.cdecl, dynlib:"libDOtherSide.so", importc.}
proc dos_qvariant_toDouble(variant: QVariant, value: var cdouble) {.cdecl, dynlib:"libDOtherSide.so", importc.}
proc dos_qvariant_setDouble(variant: QVariant, value: cdouble) {.cdecl, dynlib:"libDOtherSide.so", importc.}
proc dos_chararray_delete(rawCString: cstring) {.cdecl, dynlib:"libDOtherSide.so", importc.}

proc create*(variant: QVariant) =
  ## Create a new QVariant
  dos_qvariant_create(variant.data)
  variant.deleted = false

proc create*(variant: QVariant, value: cint) = 
  ## Create a new QVariant given a cint value
  dos_qvariant_create_int(variant.data, value)
  variant.deleted = false

proc create*(variant: QVariant, value: bool) =
  ## Create a new QVariant given a bool value  
  dos_qvariant_create_bool(variant.data, value)
  variant.deleted = false

proc create*(variant: QVariant, value: string) = 
  ## Create a new QVariant given a string value
  dos_qvariant_create_string(variant.data, value)
  variant.deleted = false

proc create*(variant: QVariant, value: QObject) =
  ## Create a new QVariant given a QObject
  dos_qvariant_create_qobject(variant.data, value.data)
  variant.deleted = false

proc create*(variant: QVariant, value: RawQVariant) =
  ## Create a new QVariant givan another QVariant
  dos_qvariant_create_qvariant(variant.data, value)
  variant.deleted = false
  
proc create*(variant: QVariant, value: cfloat) =
  ## Create a new QVariant givan another QVariant
  dos_qvariant_create_float(variant.data, value)
  variant.deleted = false

proc create*(variant: QVariant, value: QVariant) =
  create(variant, value.data)
  
proc delete*(variant: QVariant) = 
  ## Delete a QVariant
  if not variant.deleted:
    debugMsg("QVariant", "delete")
    dos_qvariant_delete(variant.data)
    variant.data = nil.RawQVariant
    variant.deleted = true

proc newQVariant*(): QVariant =
  ## Return a new QVariant  
  new(result, delete)
  result.create()

proc newQVariant*(value: cint): QVariant =
  ## Return a new QVariant given a cint
  new(result, delete)
  result.create(value)

proc newQVariant*(value: bool): QVariant  =
  ## Return a new QVariant given a bool
  new(result, delete)
  result.create(value)

proc newQVariant*(value: string): QVariant  =
  ## Return a new QVariant given a string
  new(result, delete)
  result.create(value)

proc newQVariant*(value: QObject): QVariant  =
  ## Return a new QVariant given a QObject
  new(result, delete)
  result.create(value)

proc newQVariant*(value: RawQVariant): QVariant =
  ## Return a new QVariant given a raw QVariant pointer
  new(result, delete)
  result.create(value)

proc newQVariant*(value: QVariant): QVariant =
  ## Return a new QVariant given another QVariant
  new(result, delete)
  result.create(value)

proc newQVariant*(value: float): QVariant =
  ## Return a new QVariant given a float
  new(result, delete)
  result.create(value)
  
proc isNull*(variant: QVariant): bool = 
  ## Return true if the QVariant value is null, false otherwise
  dos_qvariant_isnull(variant.data, result)

proc intVal*(variant: QVariant): int = 
  ## Return the QVariant value as int
  var rawValue: cint
  dos_qvariant_toInt(variant.data, rawValue)
  result = rawValue.cint

proc `intVal=`*(variant: QVariant, value: int) = 
  ## Sets the QVariant value int value
  var rawValue = value.cint
  dos_qvariant_setInt(variant.data, rawValue)

proc boolVal*(variant: QVariant): bool = 
  ## Return the QVariant value as bool
  dos_qvariant_toBool(variant.data, result)

proc `boolVal=`*(variant: QVariant, value: bool) =
  ## Sets the QVariant bool value
  dos_qvariant_setBool(variant.data, value)

proc floatVal*(variant: QVariant): float =
  ## Return the QVariant value as float
  var rawValue: cfloat
  dos_qvariant_toFloat(variant, rawValue)
  result = rawValue.cfloat

proc `floatVal=`*(variant: QVariant, value: float) =
  ## Sets the QVariant float value
  dos_qvariant_setFloat(variant, value.cfloat)  

proc doubleVal*(variant: QVariant): cdouble =
  ## Return the QVariant value as double
  var rawValue: cdouble
  dos_qvariant_toDouble(variant, rawValue)
  result = rawValue

proc `doubleVal=`*(variant: QVariant, value: cdouble) =
  ## Sets the QVariant double value
  dos_qvariant_setDouble(variant, value)  
  
proc stringVal*(variant: QVariant): string = 
  ## Return the QVariant value as string
  var rawCString: cstring
  var rawCStringLength: cint
  dos_qvariant_toString(variant.data, rawCString, rawCStringLength)
  result = $rawCString
  dos_chararray_delete(rawCString)

proc `stringVal=`*(variant: QVariant, value: string) = 
  ## Sets the QVariant string value
  dos_qvariant_setString(variant.data, value)

proc assign*(leftValue: QVariant, rightValue: QVariant) =
  ## Assign a QVariant with another. The inner value of the QVariant is copied
  dos_qvariant_assign(leftValue.data, rightValue.data)  

# QQmlApplicationEngine
proc dos_qqmlapplicationengine_create(engine: var RawQQmlApplicationEngine) {.cdecl, dynlib:"libDOtherSide.so", importc.}
proc dos_qqmlapplicationengine_load(engine: RawQQmlApplicationEngine, filename: cstring) {.cdecl, dynlib:"libDOtherSide.so", importc.}
proc dos_qqmlapplicationengine_context(engine: RawQQmlApplicationEngine, context: var QQmlContext) {.cdecl, dynlib:"libDOtherSide.so", importc.}
proc dos_qqmlapplicationengine_delete(engine: RawQQmlApplicationEngine) {.cdecl, dynlib:"libDOtherSide.so", importc.}

proc create*(engine: QQmlApplicationEngine) = 
  ## Create an new QQmlApplicationEngine
  dos_qqmlapplicationengine_create(engine.data)
  engine.deleted = false
  
proc load*(engine: QQmlApplicationEngine, filename: cstring) = 
  ## Load the given Qml file 
  dos_qqmlapplicationengine_load(engine.data, filename)

proc rootContext*(engine: QQmlApplicationEngine): QQmlContext =
  ## Return the engine root context
  dos_qqmlapplicationengine_context(engine.data, result)

proc delete*(engine: QQmlApplicationEngine) = 
  ## Delete the given QQmlApplicationEngine
  if not engine.deleted:
    debugMsg("QQmlApplicationEngine", "delete")
    dos_qqmlapplicationengine_delete(engine.data)
    engine.data = nil.RawQQmlApplicationEngine
    engine.deleted = true

proc newQQmlApplicationEngine*(): QQmlApplicationEngine =
  ## Return a new QQmlApplicationEngine    
  new(result, delete)
  result.create()

# QQmlContext
proc dos_qqmlcontext_setcontextproperty(context: QQmlContext, propertyName: cstring, propertyValue: RawQVariant) {.cdecl, dynlib:"libDOtherSide.so", importc.}

proc setContextProperty*(context: QQmlContext, propertyName: string, propertyValue: QVariant) = 
  ## Sets a new property with the given value
  dos_qqmlcontext_setcontextproperty(context, propertyName, propertyValue.data)

# QApplication
proc dos_qguiapplication_create() {.cdecl, dynlib: "libDOtherSide.so", importc.}
proc dos_qguiapplication_exec() {.cdecl, dynlib:"libDOtherSide.so", importc.}
proc dos_qguiapplication_quit() {.cdecl, dynlib:"libDOtherSide.so", importc.}
proc dos_qguiapplication_delete() {.cdecl, dynlib:"libDOtherSide.so", importc.}

proc create*(application: QApplication) = 
  ## Create a new QApplication
  dos_qguiapplication_create()
  application.deleted = false

proc exec*(application: QApplication) =
  ## Start the Qt event loop
  dos_qguiapplication_exec()

proc quit*(application: QApplication) =
  ## Quit the Qt event loop  
  dos_qguiapplication_quit()
  
proc delete*(application: QApplication) = 
  ## Delete the given QApplication
  if not application.deleted:
    debugMsg("QApplication", "delete")
    dos_qguiapplication_delete()
    application.deleted = true

proc newQApplication*(): QApplication =
  ## Return a new QApplication  
  new(result, delete)
  result.create()

# QObject
type RawQVariantArray {.unchecked.} = array[0..0, RawQVariant]
type RawQVariantArrayPtr = ptr RawQVariantArray
type RawQVariantSeq = seq[RawQVariant]

proc toVariantSeq(args: RawQVariantArrayPtr, numArgs: cint): seq[QVariant] =
  result = @[]
  for i in 0..numArgs-1:
    result.add(newQVariant(args[i]))

proc toRawVariantSeq(args: openarray[QVariant]): RawQVariantSeq =
  result = @[]
  for variant in args:
    result.add(variant.data)

proc delete(sequence: seq[QVariant]) =
  for variant in sequence:
    variant.delete

proc toCIntSeq(metaTypes: openarray[QMetaType]): seq[cint] =
  result = @[]
  for metaType in metaTypes:
    result.add(cint(metaType))

type QObjectCallBack = proc(nimobject: ptr QObjectObj, slotName: RawQVariant, numArguments: cint, arguments: RawQVariantArrayPtr) {.cdecl.}
    
proc dos_qobject_create(qobject: var RawQObject, nimobject: ptr QObjectObj, qobjectCallback: QObjectCallBack) {.cdecl, dynlib:"libDOtherSide.so", importc.}
proc dos_qobject_delete(qobject: RawQObject) {.cdecl, dynlib:"libDOtherSide.so", importc.}
proc dos_qobject_slot_create(qobject: RawQObject, slotName: cstring, argumentsCount: cint, argumentsMetaTypes: ptr cint, slotIndex: var cint) {.cdecl, dynlib:"libDOtherSide.so", importc.}
proc dos_qobject_signal_create(qobject: RawQObject, signalName: cstring, argumentsCount: cint, argumentsMetaTypes: ptr cint, signalIndex: var cint) {.cdecl, dynlib:"libDOtherSide.so", importc.}
proc dos_qobject_signal_emit(qobject: RawQObject, signalName: cstring, argumentsCount: cint, arguments: ptr RawQVariant) {.cdecl, dynlib:"libDOtherSide.so", importc.}
proc dos_qobject_property_create(qobject: RawQObject, propertyName: cstring, propertyType: cint, readSlot: cstring, writeSlot: cstring, notifySignal: cstring) {.cdecl, dynlib:"libDOtherSide.so", importc.}

method onSlotCalled*(nimobject: QObject, slotName: string, args: openarray[QVariant]) =
  ## Called from the NimQml bridge when a slot is called from Qml.
  ## Subclasses can override the given method for handling the slot call
  discard()

proc qobjectCallback(nimObject: ptr QObjectObj, slotName: RawQVariant, numArguments: cint, arguments: RawQVariantArrayPtr) {.cdecl, exportc.} =
  if qobjectRegistry[nimObject]:
    let qobject = cast[QObject](nimObject)
    GC_ref(qobject)
    let slotNameAsQVariant = newQVariant(slotName)
    defer: slotNameAsQVariant.delete
    let argumentsAsQVariant = arguments.toVariantSeq(numArguments)
    defer: argumentsAsQVariant.delete
    # Forward to args to the slot
    qobject.onSlotCalled(slotNameAsQVariant.stringVal, argumentsAsQVariant)
    # Update the slot return value
    dos_qvariant_assign(arguments[0], argumentsAsQVariant[0].data)
    GC_unref(qobject)

proc create*(qobject: QObject) =
  ## Create a new QObject
  debugMsg("QObject", "create")
  qobject.deleted = false
  qobject.slots = initTable[string,cint]()
  qobject.signals = initTable[string, cint]()
  qobject.properties = initTable[string, cint]()
  let qobjectPtr = addr(qobject[])
  dos_qobject_create(qobject.data, qobjectPtr, qobjectCallback)
  qobjectRegistry[qobjectPtr] = true
  
proc delete*(qobject: QObject) = 
  ## Delete the given QObject
  if not qobject.deleted:
    debugMsg("QObject", "delete")
    let qobjectPtr = addr(qobject[])
    qobjectRegistry.del qobjectPtr
    dos_qobject_delete(qobject.data)
    qobject.data = nil.RawQObject
    qobject.deleted = true
  
proc newQObject*(): QObject =
  ## Return a new QObject
  new(result, delete)
  result.create()

proc registerSlot*(qobject: QObject,
                   slotName: string, 
                   metaTypes: openarray[QMetaType]) =
  ## Register a slot in the QObject with the given name and signature
  # Copy the metatypes array
  var copy = toCIntSeq(metatypes)
  var index: cint 
  dos_qobject_slot_create(qobject.data, slotName, cint(copy.len), addr(copy[0].cint), index)
  qobject.slots[slotName] = index

proc registerSignal*(qobject: QObject,
                     signalName: string, 
                     metatypes: openarray[QMetaType]) =
  ## Register a signal in the QObject with the given name and signature
  var index: cint 
  if metatypes.len > 0:
    var copy = toCIntSeq(metatypes)
    dos_qobject_signal_create(qobject.data, signalName, copy.len.cint, addr(copy[0].cint), index)
  else:
    dos_qobject_signal_create(qobject.data, signalName, 0, nil, index)
  qobject.signals[signalName] = index

proc registerProperty*(qobject: QObject,
                       propertyName: string, 
                       propertyType: QMetaType, 
                       readSlot: string, 
                       writeSlot: string, 
                       notifySignal: string) =
  ## Register a property in the QObject with the given name and type.
  dos_qobject_property_create(qobject.data, propertyName, propertyType.cint, readSlot, writeSlot, notifySignal)

proc emit*(qobject: QObject, signalName: string, args: openarray[QVariant] = []) =
  ## Emit the signal with the given name and values
  if args.len > 0: 
    var copy = args.toRawVariantSeq
    dos_qobject_signal_emit(qobject.data, signalName, copy.len.cint, addr(copy[0]))
  else:
    dos_qobject_signal_emit(qobject.data, signalName, 0, nil)

# QQuickView
proc dos_qquickview_create(view: var RawQQuickView) {.cdecl, dynlib:"libDOtherSide.so", importc.}
proc dos_qquickview_delete(view: RawQQuickView) {.cdecl, dynlib:"libDOtherSide.so", importc.}
proc dos_qquickview_show(view: RawQQuickView) {.cdecl, dynlib:"libDOtherSide.so", importc.}
proc dos_qquickview_source(view: RawQQuickView, filename: var cstring, length: var int) {.cdecl, dynlib:"libDOtherSide.so", importc.}
proc dos_qquickview_set_source(view: RawQQuickView, filename: cstring) {.cdecl, dynlib:"libDOtherSide.so", importc.}

proc create(view: var QQuickView) =
  ## Create a new QQuickView
  dos_qquickview_create(view.data)
  view.deleted = false

proc source(view: QQuickView): cstring = 
  ## Return the source Qml file loaded by the view
  var length: int
  dos_qquickview_source(view.data, result, length)

proc `source=`(view: QQuickView, filename: cstring) =
  ## Sets the source Qml file laoded by the view
  dos_qquickview_set_source(view.data, filename)

proc show(view: QQuickView) = 
  ## Sets the view visible 
  dos_qquickview_show(view.data)

proc delete(view: QQuickView) =
  ## Delete the given QQuickView
  if not view.deleted:
    debugMsg("QQuickView", "delete")
    dos_qquickview_delete(view.data)
    view.data = nil.RawQQuickView
    view.deleted = true

proc newQQuickView*(): QQuickView =
  ## Return a new QQuickView  
  new(result, delete)
  result.create()
