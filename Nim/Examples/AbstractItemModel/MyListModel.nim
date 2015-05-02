import NimQml, NimQmlMacros, Tables

QtObject:
  type
    MyListModel* = ref object of QAbstractListModel
      names*: seq[string]
    RoleNames {.pure.} = enum
      Name = 0,

  converter toCInt(value: RoleNames): cint = return value.cint
  converter toCInt(value: int): cint = return value.cint
  converter toInt(value: RoleNames): int = return value.int
  converter toInt(value: cint): int = return value.int
  converter toQVariant(value: string): QVariant = return value.newQVariant 

  proc delete(self: MyListModel) =
    let model = self.QAbstractListModel
    model.delete
    
  proc newMyListModel*(): MyListModel =
    new(result, delete)
    result.names = @["John", "Max", "Paul", "Anna"]
    result.create

  method rowCount(self: MyListModel, index: QModelIndex = nil): cint =
    return self.names.len

  method data(self: MyListModel, index: QModelIndex, role: cint): QVariant =
    if not index.isValid:
      return
    if index.row < 0 or index.row >= self.names.len:
      return
    return self.names[index.row]

  method roleNames(self: MyListModel): Table[cint, cstring] =
    result = initTable[cint, cstring]()
    result[RoleNames.Name] = "name"
