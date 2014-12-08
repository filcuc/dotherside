import NimQmlTypes
import tables

export QObject
export QApplication
export QVariant
export QQmlApplicationEngine
export QQmlContext

type QMetaType* {.pure.} = enum
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

# QVariant
proc dos_qvariant_create(variant: var pointer) {.cdecl, dynlib:"libDOtherSide.so", importc.}
proc dos_qvariant_create_int(variant: var pointer, value: cint) {.cdecl, dynlib:"libDOtherSide.so", importc.}
proc dos_qvariant_create_bool(variant: var pointer, value: bool) {.cdecl, dynlib:"libDOtherSide.so", importc.}
proc dos_qvariant_create_string(variant: var pointer, value: cstring) {.cdecl, dynlib:"libDOtherSide.so", importc.}
proc dos_qvariant_create_qobject(variant: var pointer, value: pointer) {.cdecl, dynlib:"libDOtherSide.so", importc.}
proc dos_qvariant_delete(variant: pointer) {.cdecl, dynlib:"libDOtherSide.so", importc.}
proc dos_qvariant_isnull(variant: pointer, isNull: var bool) {.cdecl, dynlib:"libDOtherSide.so", importc.}
proc dos_qvariant_toInt(variant: pointer, value: var cint) {.cdecl, dynlib:"libDOtherSide.so", importc.}
proc dos_qvariant_toBool(variant: pointer, value: var bool) {.cdecl, dynlib:"libDOtherSide.so", importc.}
proc dos_qvariant_toString(variant: pointer, value: var cstring, length: var cint) {.cdecl, dynlib:"libDOtherSide.so", importc.}
proc dos_chararray_delete(rawCString: cstring) {.cdecl, dynlib:"libDOtherSide.so", importc.}

proc create*(variant: var QVariant) =
  var data: pointer
  dos_qvariant_create(data)
  variant = QVariant(data)

proc create*(variant: var QVariant, value: cint) = 
  var data: pointer
  dos_qvariant_create_int(data, value)
  variant = QVariant(data)

proc create*(variant: var QVariant, value: bool) =
  var data: pointer
  dos_qvariant_create_bool(data, value)
  variant = QVariant(data)

proc create*(variant: var QVariant, value: string) = 
  var data: pointer
  dos_qvariant_create_string(data, value)
  variant = QVariant(data)

proc create*(variant: var QVariant, value: QObject) =
  var data: pointer
  dos_qvariant_create_qobject(data, value.data)
  variant = QVariant(data)

proc delete*(variant: QVariant) = 
  debugMsg("QVariant", "delete")
  dos_qvariant_delete(pointer(variant))

proc isNull*(variant: QVariant): bool = 
  dos_qvariant_isnull(pointer(variant), result)

proc toInt*(variant: QVariant): cint = 
  dos_qvariant_toInt(pointer(variant), result)

proc toBool*(variant: QVariant): bool = 
  dos_qvariant_toBool(pointer(variant), result)

proc toString*(variant: QVariant): string = 
  var rawCString: cstring
  var rawCStringLength: cint
  dos_qvariant_toString(pointer(variant), rawCString, rawCStringLength)
  result = $rawCString
  dos_chararray_delete(rawCString)

# QQmlApplicationEngine
proc dos_qqmlapplicationengine_create(engine: var pointer) {.cdecl, dynlib:"libDOtherSide.so", importc.}
proc dos_qqmlapplicationengine_load(engine: pointer, filename: cstring) {.cdecl, dynlib:"libDOtherSide.so", importc.}
proc dos_qqmlapplicationengine_context(engine: pointer, context: var pointer) {.cdecl, dynlib:"libDOtherSide.so", importc.}
proc dos_qqmlapplicationengine_delete(engine: pointer) {.cdecl, dynlib:"libDOtherSide.so", importc.}

proc create*(engine: var QQmlApplicationEngine) = 
  var temp: pointer
  dos_qqmlapplicationengine_create(temp)
  engine = QQmlApplicationEngine(temp)

proc load*(engine: QQmlApplicationEngine, filename: cstring) = 
  dos_qqmlapplicationengine_load(pointer(engine), filename)

proc rootContext*(engine: QQmlApplicationEngine): QQmlContext =
  var context: pointer
  dos_qqmlapplicationengine_context(pointer(engine), context)
  result = cast[QQmlContext](context)

proc delete*(engine: QQmlApplicationEngine) = 
  debugMsg("QQmlApplicationEngine", "delete")
  dos_qqmlapplicationengine_delete(pointer(engine))

# QQmlContext
proc dos_qqmlcontext_setcontextproperty(context: pointer, propertyName: cstring, propertyValue: pointer) {.cdecl, dynlib:"libDOtherSide.so", importc.}

proc setContextProperty*(context: QQmlContext, propertyName: string, propertyValue: QVariant) = 
  dos_qqmlcontext_setcontextproperty(pointer(context), propertyName, pointer(propertyValue))

# QApplication
proc dos_qguiapplication_create() {.cdecl, dynlib: "libDOtherSide.so", importc.}
proc dos_qguiapplication_exec() {.cdecl, dynlib:"libDOtherSide.so", importc.}
proc dos_qguiapplication_delete() {.cdecl, dynlib:"libDOtherSide.so", importc.}

proc create*(application: QApplication) = 
  debugMsg("QApplication", "create")
  dos_qguiapplication_create()

proc exec*(application: QApplication) =
  debugMsg("QApplication", "exec")
  dos_qguiapplication_exec()

proc delete*(application: QApplication) = 
  debugMsg("QApplication", "delete")
  dos_qguiapplication_delete()

# QObject
type QVariantArray {.unchecked.} = array[0..0, QVariant]
type QVariantArrayPtr = ptr QVariantArray

proc dos_qobject_create(qobject: var pointer, nimobject: pointer, qobjectCallback: pointer) {.cdecl, dynlib:"libDOtherSide.so", importc.}
proc dos_qobject_delete(qobject: pointer) {.cdecl, dynlib:"libDOtherSide.so", importc.}
proc dos_qobject_slot_create(qobject: pointer, slotName: cstring, argumentsCount: cint, argumentsMetaTypes: ptr cint, slotIndex: var cint) {.cdecl, dynlib:"libDOtherSide.so", importc.}

proc qobjectCallback(nimobject: pointer, slotName: QVariant, numArguments: cint, arguments: QVariantArrayPtr) {.exportc.} = 
  debugMsg("QObject", "qobjectCallback")

proc toCIntSeq(metaTypes: openarray[QMetaType]): seq[cint] =
  result = @[]
  for metaType in metaTypes:
    result.add(cint(metaType))

proc create*(qobject: var QObject) =
  qobject.slots = initTable[string,cint]()
  dos_qobject_create(qobject.data, addr(qobject), qobjectCallback)

proc delete*(qobject: QObject) = 
  debugMsg("QObject", "delete")
  dos_qobject_delete(qobject.data)

proc registerSlot*(qobject: var QObject, slotName: string, metaTypes: openarray[QMetaType]) =
  # Copy the metatypes array
  var copy = toCIntSeq(metatypes)
  var index: cint 
  dos_qobject_slot_create(qobject.data, slotName, cint(copy.len), cast[ptr cint](addr(copy[0])), index)
  qobject.slots[slotName] = index

# QQuickView
proc dos_qquickview_create(view: var pointer) {.cdecl, dynlib:"libDOtherSide.so", importc.}
proc dos_qquickview_delete(view: pointer) {.cdecl, dynlib:"libDOtherSide.so", importc.}
proc dos_qquickview_show(view: pointer) {.cdecl, dynlib:"libDOtherSide.so", importc.}
proc dos_qquickview_source(view: pointer, filename: var cstring, length: var int) {.cdecl, dynlib:"libDOtherSide.so", importc.}
proc dos_qquickview_set_source(view: pointer, filename: cstring) {.cdecl, dynlib:"libDOtherSide.so", importc.}

proc create(view: var QQuickView) = 
  var temp: pointer
  dos_qquickview_create(temp)
  view = QQuickView(temp)

proc source(view: QQuickView): cstring = 
  var length: int
  dos_qquickview_source(pointer(view), result, length)  

proc `source=`(view: QQuickView, filename: cstring) =
  dos_qquickview_set_source(pointer(view), filename)

proc show(view: QQuickView) = 
  dos_qquickview_show(pointer(view))

proc delete(view: QQuickView) = 
  debugMsg("QQuickView", "delete")
  dos_qquickview_delete(pointer(view))