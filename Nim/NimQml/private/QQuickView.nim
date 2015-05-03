proc dos_qquickview_create(view: var RawQQuickView) {.cdecl, dynlib:dOtherSideDll, importc.}
proc dos_qquickview_delete(view: RawQQuickView) {.cdecl, dynlib:dOtherSideDll, importc.}
proc dos_qquickview_show(view: RawQQuickView) {.cdecl, dynlib:dOtherSideDll, importc.}
proc dos_qquickview_source(view: RawQQuickView, filename: var cstring, length: var int) {.cdecl, dynlib:dOtherSideDll, importc.}
proc dos_qquickview_set_source(view: RawQQuickView, filename: cstring) {.cdecl, dynlib:dOtherSideDll, importc.}

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
