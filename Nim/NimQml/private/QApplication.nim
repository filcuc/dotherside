proc dos_qapplication_create() {.cdecl, dynlib: dOtherSideDll, importc.}
proc dos_qapplication_exec() {.cdecl, dynlib:dOtherSideDll, importc.}
proc dos_qapplication_quit() {.cdecl, dynlib:dOtherSideDll, importc.}
proc dos_qapplication_delete() {.cdecl, dynlib:dOtherSideDll, importc.}

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
  new(result, delete)
  result.create()
