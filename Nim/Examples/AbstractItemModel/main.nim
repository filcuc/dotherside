import NimQml
import macros
import typeinfo

proc mainProc() =
  var myListModel = newQAbstractListModel()
  defer: myListModel.delete()
  let rows = myListModel.rowCount
  echo rows
  
  
when isMainModule:
  mainProc()
  GC_fullcollect()

