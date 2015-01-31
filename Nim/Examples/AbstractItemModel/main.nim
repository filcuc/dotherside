import NimQml
import macros
import typeinfo
import tables

type
  Roles {.pure.} = enum
    Name = cint(0)
  MyQAbstractListModel = ref object of QAbstractListModel
    m_roleNames: Table[int, cstring]
    m_names: seq[string]
  
proc create(self: MyQAbstractListModel) = 
  var qAbstractListModel = self.QAbstractListModel
  qAbstractListModel.create
  self.m_names = @["John", "Max", "Paul", "Anna"]
  self.m_roleNames = initTable[int, cstring]()
  self.m_roleNames[0] = "name"

proc delete(self: MyQAbstractListModel) = 
  var qAbstractListModel = self.QAbstractListModel
  qAbstractListModel.delete

proc newMyQAbstractListModel(): MyQAbstractListModel =
  new(result, delete)
  result.create
  
method rowCount(self: MyQAbstractListModel, index: QModelIndex): cint =
  return self.m_names.len.cint

method data(self: MyQAbstractListModel, index: QModelIndex, role: cint): QVariant =
  if not index.isValid:
    return
  if index.row < 0 or index.row >= self.m_names.len:
    return  
  if role == Roles.Name.cint:
    return newQVariant(self.m_names[index.row])

method roleNames(self: MyQAbstractListModel): Table[int, cstring] =
  return self.m_roleNames  
  
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

when isMainModule:
  mainProc()
  GC_fullcollect()

