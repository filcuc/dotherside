include NimQmlTypes

## NimQml aims to provide binding to the QML for the Nim programming language
##
## Optional finalizers
## -------------------
## To enable finalizers you must define ``nimqml_use_finalizers`` by passing
## the option, ``-d:nimqml_use_finalizers``, to the Nim compiler. The relevant
## delete method will then be called automatically by the garbage collector.
## Care should be taken when using this approach as there are no guarantees
## when a finalzier will be run, or if, indeed, it will run at all.

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
  QObjectStar = cint(39),
  QVariant = cint(41), 
  Void = cint(43),

var qobjectRegistry = initTable[ptr QObjectObj, bool]()

template debugMsg(message: string) = 
  {.push warning[user]: off.} # workaround to remove warnings; this won't be needed soon
  when defined(debug):
    {.pop.}
    echo "NimQml: ", message
  else:
    {.pop.}
  
template debugMsg(typeName: string, procName: string) =
  {.push warning[user]: off.} # workaround to remove warnings; this won't be needed soon
  when defined(debug):
    {.pop.}
    var message = typeName
    message &= ": "
    message &= procName
    debugMsg(message)
  else:
    {.pop.}  

template debugMsg(typeName: string, procName: string, userMessage: string) = 
  {.push warning[user]: off.} # workaround to remove warnings; this won't be needed soon
  when defined(debug):
    {.pop.}
    var message = typeName
    message &= ": "
    message &= procName
    message &= " "
    message &= userMessage
    debugMsg(message)
  else:
    {.pop.}

template newWithCondFinalizer(variable: expr, finalizer: expr) =
  ## calls ``new`` but only setting a finalizer when ``nimqml_use_finalizers``
  ## is defined
  {.push warning[user]: off.} # workaround to remove warnings; this won't be needed soon
  when defined(nimqml_use_finalizers):
    {.pop.}
    new(variable, finalizer)
  else:
    {.pop.}
    new(variable)

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
proc dos_qvariant_toFloat(variant: RawQVariant, value: var cfloat) {.cdecl, dynlib:"libDOtherSide.so", importc.}
proc dos_qvariant_setFloat(variant: RawQVariant, value: float)  {.cdecl, dynlib:"libDOtherSide.so", importc.}
proc dos_qvariant_toDouble(variant: RawQVariant, value: var cdouble) {.cdecl, dynlib:"libDOtherSide.so", importc.}
proc dos_qvariant_setDouble(variant: RawQVariant, value: cdouble) {.cdecl, dynlib:"libDOtherSide.so", importc.}
proc dos_qvariant_setQObject(variant: RawQVariant, value: RawQObject) {.cdecl, dynlib:"libDOtherSide.so", importc.}
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
  dos_qvariant_create_qobject(variant.data, value.data.RawQObject)
  variant.deleted = false

proc create*(variant: QVariant, value: RawQVariant) =
  ## Create a new QVariant given another QVariant.
  ## The inner value of the QVariant is copied
  dos_qvariant_create_qvariant(variant.data, value)
  variant.deleted = false
  
proc create*(variant: QVariant, value: cfloat) =
  ## Create a new QVariant given a cfloat value
  dos_qvariant_create_float(variant.data, value)
  variant.deleted = false

proc create*(variant: QVariant, value: QVariant) =
  ## Create a new QVariant given another QVariant.
  ## The inner value of the QVariant is copied
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
  newWithCondFinalizer(result, delete)
  result.create()

proc newQVariant*(value: cint): QVariant =
  ## Return a new QVariant given a cint
  newWithCondFinalizer(result, delete)
  result.create(value)

proc newQVariant*(value: bool): QVariant  =
  ## Return a new QVariant given a bool
  newWithCondFinalizer(result, delete)
  result.create(value)

proc newQVariant*(value: string): QVariant  =
  ## Return a new QVariant given a string
  newWithCondFinalizer(result, delete)
  result.create(value)

proc newQVariant*(value: QObject): QVariant  =
  ## Return a new QVariant given a QObject
  newWithCondFinalizer(result, delete)
  result.create(value)

proc newQVariant*(value: RawQVariant): QVariant =
  ## Return a new QVariant given a raw QVariant pointer
  newWithCondFinalizer(result, delete)
  result.create(value)

proc newQVariant*(value: QVariant): QVariant =
  ## Return a new QVariant given another QVariant
  newWithCondFinalizer(result, delete)
  result.create(value)

proc newQVariant*(value: float): QVariant =
  ## Return a new QVariant given a float
  newWithCondFinalizer(result, delete)
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
  dos_qvariant_toFloat(variant.data, rawValue)
  result = rawValue.cfloat

proc `floatVal=`*(variant: QVariant, value: float) =
  ## Sets the QVariant float value
  dos_qvariant_setFloat(variant.data, value.cfloat)  

proc doubleVal*(variant: QVariant): cdouble =
  ## Return the QVariant value as double
  var rawValue: cdouble
  dos_qvariant_toDouble(variant.data, rawValue)
  result = rawValue

proc `doubleVal=`*(variant: QVariant, value: cdouble) =
  ## Sets the QVariant double value
  dos_qvariant_setDouble(variant.data, value)  
  
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

proc `qobjectVal=`*(variant: QVariant, value: QObject) =
  ## Sets the QVariant qobject value
  dos_qvariant_setQObject(variant.data, value.data.RawQObject)
  
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
  newWithCondFinalizer(result, delete)
  result.create()

# QQmlContext
proc dos_qqmlcontext_setcontextproperty(context: QQmlContext, propertyName: cstring, propertyValue: RawQVariant) {.cdecl, dynlib:"libDOtherSide.so", importc.}

proc setContextProperty*(context: QQmlContext, propertyName: string, propertyValue: QVariant) = 
  ## Sets a new property with the given value
  dos_qqmlcontext_setcontextproperty(context, propertyName, propertyValue.data)

# QApplication
proc dos_qapplication_create() {.cdecl, dynlib: "libDOtherSide.so", importc.}
proc dos_qapplication_exec() {.cdecl, dynlib:"libDOtherSide.so", importc.}
proc dos_qapplication_quit() {.cdecl, dynlib:"libDOtherSide.so", importc.}
proc dos_qapplication_delete() {.cdecl, dynlib:"libDOtherSide.so", importc.}

proc create*(application: QApplication) = 
  ## Create a new QApplication
  dos_qapplication_create()
  application.deleted = false

proc exec*(application: QApplication) =
  ## Start the Qt event loop
  dos_qapplication_exec()

proc quit*(application: QApplication) =
  ## Quit the Qt event loop  
  dos_qapplication_quit()
  
proc delete*(application: QApplication) = 
  ## Delete the given QApplication
  if not application.deleted:
    debugMsg("QApplication", "delete")
    dos_qapplication_delete()
    application.deleted = true

proc newQApplication*(): QApplication =
  ## Return a new QApplication  
  newWithCondFinalizer(result, delete)
  result.create()

# QGuiApplication
proc dos_qguiapplication_create() {.cdecl, dynlib: "libDOtherSide.so", importc.}
proc dos_qguiapplication_exec() {.cdecl, dynlib:"libDOtherSide.so", importc.}
proc dos_qguiapplication_quit() {.cdecl, dynlib:"libDOtherSide.so", importc.}
proc dos_qguiapplication_delete() {.cdecl, dynlib:"libDOtherSide.so", importc.}

proc create*(application: QGuiApplication) = 
  ## Create a new QApplication
  dos_qguiapplication_create()
  application.deleted = false

proc exec*(application: QGuiApplication) =
  ## Start the Qt event loop
  dos_qguiapplication_exec()

proc quit*(application: QGuiApplication) =
  ## Quit the Qt event loop  
  dos_qguiapplication_quit()
  
proc delete*(application: QGuiApplication) = 
  ## Delete the given QApplication
  if not application.deleted:
    debugMsg("QApplication", "delete")
    dos_qguiapplication_delete()
    application.deleted = true

proc newQGuiApplication*(): QGuiApplication =
  ## Return a new QApplication  
  newWithCondFinalizer(result, delete)
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
  newWithCondFinalizer(result, delete)
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
  assert propertyName != nil, "property name cannot be nil"
  # don't convert a nil string, else we get a strange memory address
  let cReadSlot: cstring = if readSlot == nil: cast[cstring](nil) else: readSlot
  let cWriteSlot: cstring = if writeSlot == nil: cast[cstring](nil) else: writeSlot
  let cNotifySignal: cstring = if notifySignal == nil: cast[cstring](nil) else: notifySignal
  dos_qobject_property_create(qobject.data, propertyName, propertyType.cint, cReadSlot, cWriteSlot, cNotifySignal)

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
  newWithCondFinalizer(result, delete)
  result.create()

# QModelIndex
proc dos_qmodelindex_create(modelIndex: var RawQModelIndex) {.cdecl, dynlib:"libDOtherSide.so", importc.}
proc dos_qmodelindex_delete(modelIndex: RawQModelIndex) {.cdecl, dynlib:"libDOtherSide.so", importc.}
proc dos_qmodelindex_row(modelIndex: RawQModelIndex, row: var cint) {.cdecl, dynlib:"libDOtherSide.so", importc.}
proc dos_qmodelindex_column(modelIndex: RawQModelIndex, column: var cint) {.cdecl, dynlib:"libDOtherSide.so", importc.}
proc dos_qmodelindex_isValid(modelIndex: RawQModelIndex, column: var bool) {.cdecl, dynlib:"libDOtherSide.so", importc.}
proc dos_qmodelindex_data(modelIndex: RawQModelIndex, role: cint, data: RawQVariant) {.cdecl, dynlib:"libDOtherSide.so", importc.}
proc dos_qmodelindex_parent(modelIndex: RawQModelIndex, parent: RawQModelIndex) {.cdecl, dynlib:"libDOtherSide.so", importc.}
proc dos_qmodelindex_child(modelIndex: RawQModelIndex, row: cint, column: cint, parent: RawQModelIndex) {.cdecl, dynlib:"libDOtherSide.so", importc.}
proc dos_qmodelindex_sibling(modelIndex: RawQModelIndex, row: cint, column: cint, sibling: RawQModelIndex) {.cdecl, dynlib:"libDOtherSide.so", importc.}

proc create*(modelIndex: var QModelIndex) =
  ## Create a new QModelIndex
  dos_qmodelindex_create(modelIndex.data)
  modelIndex.deleted = false

proc create*(modelIndex: var QModelIndex, rawQModelIndex: RawQModelIndex) =
  ## Create a new QModelIndex
  modelIndex.data = rawQModelIndex
  modelIndex.deleted = false
  
proc delete*(modelIndex: QModelIndex) =
  ## Delete the given QModelIndex
  if not modelIndex.deleted:
    debugMsg("QModelIndex", "delete")
    dos_qmodelindex_delete(modelIndex.data)
    modelIndex.data = nil.RawQModelIndex
    modelIndex.deleted = true

proc newQModelIndex*(): QModelIndex =
  ## Return a new QModelIndex
  newWithCondFinalizer(result, delete)
  result.create()

proc newQModelIndex*(rawQModelIndex: RawQModelIndex): QModelIndex =
  ## Return a new QModelIndex given a raw index
  newWithCondFinalizer(result, delete)
  result.create(rawQModelIndex)

proc row*(modelIndex: QModelIndex): cint =
  ## Return the index row
  dos_qmodelindex_row(modelIndex.data, result)

proc column*(modelIndex: QModelIndex): cint =
  ## Return the index column
  dos_qmodelindex_column(modelIndex.data, result)

proc isValid*(modelIndex: QModelIndex): bool =
  ## Return true if the index is valid, false otherwise
  dos_qmodelindex_isValid(modelIndex.data, result)

proc data*(modelIndex: QModelIndex, role: cint): QVariant =
  ## Return the model data associated to the given role  
  result = newQVariant()
  dos_qmodelindex_data(modelIndex.data, role, result.data)

proc parent*(modelIndex: QModelIndex): QModelIndex =
  ## Return the parent index
  result = newQModelIndex()
  dos_qmodelindex_parent(modelIndex.data, result.data)

proc child*(modelIndex: QModelIndex, row: cint, column: cint): QModelIndex =
  ## Return the child index associated to the given row and column
  result = newQModelIndex()
  dos_qmodelindex_child(modelIndex.data, row, column, result.data)

proc sibling*(modelIndex: QModelIndex, row: cint, column: cint): QModelIndex =
  ## Return the sibling index associated to the given row and column
  result = newQModelIndex()
  dos_qmodelindex_sibling(modelIndex.data, row, column, result.data)

# QHashIntByteArray
proc dos_qhash_int_qbytearray_create(qHash: var RawQHashIntByteArray) {.cdecl, dynlib:"libDOtherSide.so", importc.}
proc dos_qhash_int_qbytearray_delete(qHash: RawQHashIntByteArray) {.cdecl, dynlib:"libDOtherSide.so", importc.}
proc dos_qhash_int_qbytearray_insert(qHash: RawQHashIntByteArray, key: int, value: cstring) {.cdecl, dynlib:"libDOtherSide.so", importc.}
proc dos_qhash_int_qbytearray_value(qHash: RawQHashIntByteArray, key: int, value: var cstring) {.cdecl, dynlib:"libDOtherSide.so", importc.}

proc create*(qHash: var QHashIntByteArray) =
  ## Create the QHash
  debugMsg("QHashIntByteArray", "create")
  dos_qhash_int_qbytearray_create(qHash.data)
  qHash.deleted = false

proc delete*(qHash: QHashIntByteArray) =
  ## Delete the QHash
  if not qHash.deleted:
    debugMsg("QHashIntByteArray", "delete")  
    dos_qhash_int_qbytearray_delete(qHash.data)
    qHash.deleted = true

proc insert*(qHash: QHashIntByteArray, key: int, value: cstring) =
  ## Insert the value at the given key
  dos_qhash_int_qbytearray_insert(qHash.data, key, value)

proc value*(qHash: QHashIntByteArray, key: int): string =
  ## Return the value associated at the given key  
  var rawString: cstring
  dos_qhash_int_qbytearray_value(qHash.data, key, rawString)
  result = $rawString
  dos_chararray_delete(rawString)

proc newQHashIntQByteArray*(): QHashIntByteArray =
  ## Create a new QHashIntQByteArray  
  newWithCondFinalizer(result, delete)
  result.create()
  
# QAbstractListModel
type
  RowCountCallback = proc(modelObject: ptr QAbstractListModelObj, rawIndex: RawQModelIndex, result: var cint) {.cdecl.}
  ColumnCountCallback = proc(modelObject: ptr QAbstractListModelObj, rawIndex: RawQModelIndex, result: var cint) {.cdecl.}
  DataCallback = proc(modelObject: ptr QAbstractListModelObj, rawIndex: RawQModelIndex, role: cint, result: RawQVariant) {.cdecl.}
  SetDataCallback = proc(modelObject: ptr QAbstractListModelObj, rawIndex: RawQModelIndex, value: RawQVariant, role: cint, result: var bool) {.cdecl.}
  RoleNamesCallback = proc(modelObject: ptr QAbstractListModelObj, result: RawQHashIntByteArray) {.cdecl.}
  FlagsCallback = proc(modelObject: ptr QAbstractListModelObj, index: RawQModelIndex, result: var cint) {.cdecl.}
  HeaderDataCallback = proc(modelObject: ptr QAbstractListModelObj, section: cint, orientation: cint, role: cint, result: RawQVariant) {.cdecl.}

proc dos_qabstractlistmodel_create(model: var RawQAbstractListModel,
                                   modelPtr: ptr QAbstractListModelObj,
                                   qobjectCallback: QObjectCallBack,
                                   rowCountCallback: RowCountCallback,
                                   columnCountCallback: ColumnCountCallback,
                                   dataCallback: DataCallback,
                                   setDataCallback: SetDataCallBack,
                                   roleNamesCallback: RoleNamesCallback,
                                   flagsCallback: FlagsCallback,
                                   headerDataCallback: HeaderDataCallback) {.cdecl, dynlib:"libDOtherSide.so", importc.}
proc dos_qabstractlistmodel_delete(model: RawQAbstractListModel) {.cdecl, dynlib:"libDOtherSide.so", importc.}
proc dos_qabstractlistmodel_beginInsertRows(model: RawQAbstractListModel,
                                            parentIndex: RawQModelIndex,
                                            first: cint,
                                            last: cint) {.cdecl, dynlib:"libDOtherSide.so", importc.}
proc dos_qabstractlistmodel_endInsertRows(model: RawQAbstractListModel) {.cdecl, dynlib:"libDOtherSide.so", importc.}
proc dos_qabstractlistmodel_beginRemoveRows(model: RawQAbstractListModel,
                                            parentIndex: RawQModelIndex,
                                            first: cint,
                                            last: cint) {.cdecl, dynlib:"libDOtherSide.so", importc.}
proc dos_qabstractlistmodel_endRemoveRows(model: RawQAbstractListModel) {.cdecl, dynlib:"libDOtherSide.so", importc.}
proc dos_qabstractlistmodel_beginResetModel(model: RawQAbstractListModel) {.cdecl, dynlib:"libDOtherSide.so", importc.}
proc dos_qabstractlistmodel_endResetModel(model: RawQAbstractListModel) {.cdecl, dynlib:"libDOtherSide.so", importc.}
proc dos_qabstractlistmodel_dataChanged(model: RawQAbstractListModel,
                                        parentLeft: RawQModelIndex,
                                        bottomRight: RawQModelIndex,
                                        rolesArrayPtr: ptr cint,
                                        rolesArrayLength: cint) {.cdecl, dynlib:"libDOtherSide.so", importc.}

method rowCount*(model: QAbstractListModel, index: QModelIndex): cint =
  ## Return the model's row count
  return 0

proc rowCountCallback(modelObject: ptr QAbstractListModelObj, rawIndex: RawQModelIndex, result: var cint) {.cdecl, exportc.} =
  debugMsg("QAbstractListModel", "rowCountCallback")
  let model = cast[QAbstractListModel](modelObject)
  let index = newQModelIndex(rawIndex)
  result = model.rowCount(index)

method columnCount*(model: QAbstractListModel, index: QModelIndex): cint =
  ## Return the model's column count
  return 1

proc columnCountCallback(modelObject: ptr QAbstractListModelObj, rawIndex: RawQModelIndex, result: var cint) {.cdecl, exportc.} =
  debugMsg("QAbstractListModel", "columnCountCallback")
  let model = cast[QAbstractListModel](modelObject)
  let index = newQModelIndex(rawIndex)
  result = model.columnCount(index)
  
method data*(model: QAbstractListModel, index: QModelIndex, role: cint): QVariant =
  ## Return the data at the given model index and role
  return nil  
  
proc dataCallback(modelObject: ptr QAbstractListModelObj, rawIndex: RawQModelIndex, role: cint, result: RawQVariant) {.cdecl, exportc.} =
  debugMsg("QAbstractListModel", "dataCallback")
  let model = cast[QAbstractListModel](modelObject)
  let index = newQModelIndex(rawIndex)
  let variant = data(model, index, role)
  if variant != nil:
    dos_qvariant_assign(result, variant.data)
    variant.delete

method setData*(model: QAbstractListModel, index: QModelIndex, value: QVariant, role: cint): bool =
  ## Sets the data at the given index and role. Return true on success, false otherwise
  return false 

proc setDataCallback(modelObject: ptr QAbstractListModelObj, rawIndex: RawQModelIndex, rawQVariant: RawQVariant,  role: cint, result: var bool) {.cdecl, exportc.} =
  debugMsg("QAbstractListModel", "setDataCallback")
  let model = cast[QAbstractListModel](modelObject)
  let index = newQModelIndex(rawIndex)
  let variant = newQVariant(rawQVariant)
  result = model.setData(index, variant, role)
    
method roleNames*(model: QAbstractListModel): Table[cint, cstring] =
  ## Return the model role names  
  result = initTable[cint, cstring]()

proc roleNamesCallback(modelObject: ptr QAbstractListModelObj, hash: RawQHashIntByteArray) {.cdecl, exportc.} =
  debugMsg("QAbstractListModel", "roleNamesCallback")
  let model = cast[QAbstractListModel](modelObject)
  let table = model.roleNames()
  for pair in table.pairs:
    dos_qhash_int_qbytearray_insert(hash, pair.key, pair.val)

method flags*(model: QAbstractListModel, index: QModelIndex): QtItemFlag =
  ## Return the item flags and the given index
  return QtItemFlag.None

proc flagsCallback(modelObject: ptr QAbstractListModelObj, rawIndex: RawQModelIndex, result: var cint) {.cdecl, exportc.} =
  debugMsg("QAbstractListModel", "flagsCallback")
  let model = cast[QAbstractListModel](modelObject)
  let index = newQModelIndex(rawIndex)
  result = model.flags(index).cint

method headerData*(model: QAbstractListModel, section: cint, orientation: QtOrientation, role: cint): QVariant =
  ## Returns the data for the given role and section in the header with the specified orientation
  return nil

proc headerDataCallback(modelObject: ptr QAbstractListModelObj, section: cint, orientation: cint, role: cint, result: RawQVariant) {.cdecl, exportc.} =
  debugMsg("QAbstractListModel", "headerDataCallback")
  let model = cast[QAbstractListModel](modelObject)
  let variant = model.headerData(section, orientation.QtOrientation, role)
  if variant != nil:
    dos_qvariant_assign(result, variant.data)
    variant.delete
    
proc create*(model: var QAbstractListModel) =
  ## Create a new QAbstractListModel
  debugMsg("QAbstractListModel", "create")
  model.slots = initTable[string,cint]()
  model.signals = initTable[string, cint]()
  model.properties = initTable[string, cint]()
  model.deleted = false
  let modelPtr = addr(model[])
  dos_qabstractlistmodel_create(model.data.RawQAbstractListModel, modelPtr, qobjectCallback, rowCountCallback, columnCountCallback, dataCallback, setDataCallback, roleNamesCallback, flagsCallback, headerDataCallback)
  qobjectRegistry[modelPtr] = true

proc delete*(model: QAbstractListModel) =
  ## Delete the given QAbstractListModel
  if not model.deleted:
    debugMsg("QAbstractListModel", "delete")
    let modelPtr = addr(model[])
    qobjectRegistry.del modelPtr
    dos_qabstractlistmodel_delete(model.data.RawQAbstractListModel)
    model.data = nil.RawQObject
    model.deleted = true

proc newQAbstractListModel*(): QAbstractListModel =
  ## Return a new QAbstractListModel
  newWithCondFinalizer(result, delete)
  result.create()

proc beginInsertRows*(model: QAbstractListModel, parentIndex: QModelIndex, first: int, last: int) =
  ## Notify the view that the model is about to inserting the given number of rows 
  dos_qabstractlistmodel_beginInsertRows(model.data.RawQAbstractListModel, parentIndex.data, first.cint, last.cint)

proc endInsertRows*(model: QAbstractListModel) =
  ## Notify the view that the rows have been inserted
  dos_qabstractlistmodel_endInsertRows(model.data.RawQAbstractListModel)

proc beginRemoveRows*(model: QAbstractListModel, parentIndex: QModelIndex, first: int, last: int) =
  ## Notify the view that the model is about to remove the given number of rows 
  dos_qabstractlistmodel_beginRemoveRows(model.data.RawQAbstractListModel, parentIndex.data, first.cint, last.cint)

proc endRemoveRows*(model: QAbstractListModel) =
  ## Notify the view that the rows have been removed
  dos_qabstractlistmodel_endRemoveRows(model.data.RawQAbstractListModel)

proc beginResetModel*(model: QAbstractListModel) =
  ## Notify the view that the model is about to resetting
  dos_qabstractlistmodel_beginResetModel(model.data.RawQAbstractListModel)

proc endResetModel*(model: QAbstractListModel) =
  ## Notify the view that model has finished resetting
  dos_qabstractlistmodel_endResetModel(model.data.RawQAbstractListModel)

proc dataChanged*(model: QAbstractListModel,
                 topLeft: QModelIndex,
                 bottomRight: QModelIndex,
                 roles: seq[cint]) =
  ## Notify the view that the model data changed
  var copy = roles
  dos_qabstractlistmodel_dataChanged(model.data.RawQAbstractListModel, topLeft.data, bottomRight.data, copy[0].addr, copy.len.cint)  
  
