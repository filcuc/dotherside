import NimQml
import macros
import typeinfo

proc mainProc() =
  var myListModel = newQAbstractListModel()
  defer: myListModel.delete()
  
when isMainModule:
  mainProc()
  GC_fullcollect()

