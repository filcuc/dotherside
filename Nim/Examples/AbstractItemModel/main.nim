import NimQml
import macros
import typeinfo

type MyQAbstractListModel = ref object of QAbstractListModel

proc create(self: MyQAbstractListModel) = 
  var qAbstractListModel = self.QAbstractListModel
  qAbstractListModel.create

proc delete(self: MyQAbstractListModel) = 
  var qAbstractListModel = self.QAbstractListModel
  qAbstractListModel.delete

proc newMyQAbstractListModel(): MyQAbstractListModel =
  new(result, delete)
  result.create
  
method rowCount(self: MyQAbstractListModel, index: QModelIndex): cint =
  echo "index valid: " & $index.isValid & " row: " & $index.row & " column: " & $index.column  
  return 3

method data(self: MyQAbstractListModel, index: QModelIndex, role: cint): QVariant =
  echo "index valid: " & $index.isValid & " row: " & $index.row & " column: " & $index.column  
  return nil  
  
proc mainProc() =
  var app = newQApplication()
  defer: app.delete
  
  var myListModel = newMyQAbstractListModel()
  defer: myListModel.delete

  var engine = newQQmlApplicationEngine()
  defer: engine.delete

  var variant = newQVariant(myListModel)
  defer: variant.delete

  engine.rootContext.setContextProperty("myListModel", variant)
  engine.load("main.qml")
  
  app.exec()

proc mainProc2() =
  var qhash = newQHashIntQByteArray()
  defer: qHash.delete
  qhash.insert(0,"Name")
  qhash.insert(1, "Surname")
  echo qhash.value(0)
  echo qhash.value(1)
  
when isMainModule:
  mainProc2()
  GC_fullcollect()

