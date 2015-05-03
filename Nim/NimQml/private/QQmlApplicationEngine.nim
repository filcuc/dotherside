proc dos_qqmlapplicationengine_create(engine: var RawQQmlApplicationEngine) {.cdecl, dynlib:dOtherSideDll, importc.}
proc dos_qqmlapplicationengine_load(engine: RawQQmlApplicationEngine, filename: cstring) {.cdecl, dynlib:dOtherSideDll, importc.}
proc dos_qqmlapplicationengine_context(engine: RawQQmlApplicationEngine, context: var QQmlContext) {.cdecl, dynlib:dOtherSideDll, importc.}
proc dos_qqmlapplicationengine_delete(engine: RawQQmlApplicationEngine) {.cdecl, dynlib:dOtherSideDll, importc.}

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
