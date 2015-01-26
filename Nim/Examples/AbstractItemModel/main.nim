import NimQml
import macros
import typeinfo

type MyQAbstractListModel = ref object of QAbstractListModel
  m_name: string

proc create(self: MyQAbstractListModel) = 
  var qAbstractListModel = self.QAbstractListModel
  qAbstractListModel.create()

proc delete(self: MyQAbstractListModel) = 
  var qAbstractListModel = self.QAbstractListModel
  qAbstractListModel.delete()

proc newMyQAbstractListModel(): MyQAbstractListModel =
  new(result, delete)
  result.create()
  
method rowCount(self: MyQAbstractListModel): cint =
  return 103
  
proc mainProc() =
  var myListModel = newMyQAbstractListModel()
  defer: myListModel.delete()
  let rows = myListModel.rowCount
  echo rows
  
  
when isMainModule:
  mainProc()
  GC_fullcollect()

