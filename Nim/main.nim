# QApplication
proc dos_qguiapplication_create() {.cdecl, dynlib: "libDOtherSide.so", importc.}
proc dos_qguiapplication_exec() {.cdecl, dynlib:"libDOtherSide.so", importc.}
proc dos_qguiapplication_delete() {.cdecl, dynlib:"libDOtherSide.so", importc.}

type QApplication = distinct pointer

proc create(application: QApplication) = 
  echo "QApplication: create"
  dos_qguiapplication_create()

proc exec(application: QApplication) =
  echo "QApplication: exec"
  dos_qguiapplication_exec()

proc delete(application: QApplication) = 
  echo "QApplication: delete"
  dos_qguiapplication_delete()

# QQmlApplicationEngine
proc dos_qqmlapplicationengine_create(engine: var pointer) {.cdecl, dynlib:"libDOtherSide.so", importc.}
proc dos_qqmlapplicationengine_load(engine: pointer, filename: cstring) {.cdecl, dynlib:"libDOtherSide.so", importc.}
proc dos_qqmlapplicationengine_delete(engine: pointer) {.cdecl, dynlib:"libDOtherSide.so", importc.}

type QQmlApplicationEngine = distinct pointer

proc create(engine: var QQmlApplicationEngine) = 
  var temp: pointer
  dos_qqmlapplicationengine_create(temp)
  engine = QQmlApplicationEngine(temp)

proc load(engine: QQmlApplicationEngine, filename: cstring) = 
  dos_qqmlapplicationengine_load(pointer(engine), filename)

proc delete(engine: QQmlApplicationEngine) = 
  dos_qqmlapplicationengine_delete(pointer(engine))

# QQuickView
proc dos_qquickview_create(view: var pointer) {.cdecl, dynlib:"libDOtherSide.so", importc.}
proc dos_qquickview_delete(view: pointer) {.cdecl, dynlib:"libDOtherSide.so", importc.}
proc dos_qquickview_show(view: pointer) {.cdecl, dynlib:"libDOtherSide.so", importc.}
proc dos_qquickview_source(view: pointer, filename: var cstring, length: var int) {.cdecl, dynlib:"libDOtherSide.so", importc.}
proc dos_qquickview_set_source(view: pointer, filename: cstring) {.cdecl, dynlib:"libDOtherSide.so", importc.}

type QQuickView = distinct pointer

proc create(view: var QQuickView) = 
  echo "QQuickView: create"
  var temp: pointer
  dos_qquickview_create(temp)
  view = QQuickView(temp)

proc source(view: QQuickView): cstring = 
    var length: int
    dos_qquickview_source(pointer(view), result, length)
    return 

proc `source=`(view: QQuickView, filename: cstring) =
  echo "QQuickView: source="
  dos_qquickview_set_source(pointer(view), filename)

proc show(view: QQuickView) = 
  echo "QQuickView: show"
  dos_qquickview_show(pointer(view))

proc delete(view: QQuickView) = 
  echo "QQuickView: delete"
  dos_qquickview_delete(pointer(view))

# QVariant
proc dos_qvariant_create(variant: var pointer) {.cdecl, dynlib:"libDOtherSide.so", importc.}
proc dos_qvariant_create_int(variant: var pointer, value: int) {.cdecl, dynlib:"libDOtherSide.so", importc.}
proc dos_qvariant_create_bool(variant: var pointer, value: bool) {.cdecl, dynlib:"libDOtherSide.so", importc.}
proc dos_qvariant_create_string(variant: var pointer, value: cstring) {.cdecl, dynlib:"libDOtherSide.so", importc.}
proc dos_qvariant_delete(variant: pointer) {.cdecl, dynlib:"libDOtherSide.so", importc.}
proc dos_qvariant_isnull(variant: pointer, isNull: var bool) {.cdecl, dynlib:"libDOtherSide.so", importc.}
proc dos_qvariant_toInt(variant: pointer, value: var int) {.cdecl, dynlib:"libDOtherSide.so", importc.}
proc dos_qvariant_toBool(variant: pointer, value: var bool) {.cdecl, dynlib:"libDOtherSide.so", importc.}
proc dos_qvariant_toString(variant: pointer, value: var cstring) {.cdecl, dynlib:"libDOtherSide.so", importc.}

type QVariant = distinct pointer

proc create(variant: var QVariant) =
  var data: pointer
  dos_qvariant_create(data)
  variant = QVariant(data)

proc create(variant: var QVariant, value: int) = 
  var data: pointer
  dos_qvariant_create_int(data, value)
  variant = QVariant(data)

proc create(variant: var QVariant, value: bool) =
  var data: pointer
  dos_qvariant_create_bool(data, value)
  variant = QVariant(data)

proc create(variant: var QVariant, value: cstring) = 
  var data: pointer
  dos_qvariant_create_string(data, value)
  variant = QVariant(data)

proc delete(variant: QVariant) = 
  dos_qvariant_delete(pointer(variant))

proc isNull(variant: QVariant): bool = 
  dos_qvariant_isnull(pointer(variant), result)

proc toInt(variant: QVariant): int = 
  dos_qvariant_toInt(pointer(variant), result)

proc toBool(variant: QVariant): bool = 
  dos_qvariant_toBool(pointer(variant), result)

proc toString(variant: QVariant): cstring = 
 dos_qvariant_toString(pointer(variant), result)



block:
  var app: QApplication
  app.create()
  finally: app.delete()

  var engine: QQmlApplicationEngine
  engine.create()
  finally: engine.delete()

  engine.load("main.qml")

  app.exec()