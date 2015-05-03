type
  RowCountCallback = proc(modelObject: ptr QAbstractListModelObj, rawIndex: RawQModelIndex, result: var cint) {.cdecl.}
  ColumnCountCallback = proc(modelObject: ptr QAbstractListModelObj, rawIndex: RawQModelIndex, result: var cint) {.cdecl.}
  DataCallback = proc(modelObject: ptr QAbstractListModelObj, rawIndex: RawQModelIndex, role: cint, result: RawQVariant) {.cdecl.}
  SetDataCallback = proc(modelObject: ptr QAbstractListModelObj, rawIndex: RawQModelIndex, value: RawQVariant, role: cint, result: var bool) {.cdecl.}
  RoleNamesCallback = proc(modelObject: ptr QAbstractListModelObj, result: RawQHashIntByteArray) {.cdecl.}
  FlagsCallback = proc(modelObject: ptr QAbstractListModelObj, index: RawQModelIndex, result: var cint) {.cdecl.}
  HeaderDataCallback = proc(modelObject: ptr QAbstractListModelObj, section: cint, orientation: cint, role: cint, result: RawQVariant) {.cdecl.}

proc dos_qabstractlistmodel_create(model: var RawQAbstractListModel,
                                   modelPtr: ptr QAbstractListModelObj,
                                   qobjectCallback: QObjectCallBack,
                                   rowCountCallback: RowCountCallback,
                                   columnCountCallback: ColumnCountCallback,
                                   dataCallback: DataCallback,
                                   setDataCallback: SetDataCallBack,
                                   roleNamesCallback: RoleNamesCallback,
                                   flagsCallback: FlagsCallback,
                                   headerDataCallback: HeaderDataCallback) {.cdecl, dynlib:dOtherSideDll, importc.}
proc dos_qabstractlistmodel_delete(model: RawQAbstractListModel) {.cdecl, dynlib:dOtherSideDll, importc.}
proc dos_qabstractlistmodel_beginInsertRows(model: RawQAbstractListModel,
                                            parentIndex: RawQModelIndex,
                                            first: cint,
                                            last: cint) {.cdecl, dynlib:dOtherSideDll, importc.}
proc dos_qabstractlistmodel_endInsertRows(model: RawQAbstractListModel) {.cdecl, dynlib:dOtherSideDll, importc.}
proc dos_qabstractlistmodel_beginRemoveRows(model: RawQAbstractListModel,
                                            parentIndex: RawQModelIndex,
                                            first: cint,
                                            last: cint) {.cdecl, dynlib:dOtherSideDll, importc.}
proc dos_qabstractlistmodel_endRemoveRows(model: RawQAbstractListModel) {.cdecl, dynlib:dOtherSideDll, importc.}
proc dos_qabstractlistmodel_beginResetModel(model: RawQAbstractListModel) {.cdecl, dynlib:dOtherSideDll, importc.}
proc dos_qabstractlistmodel_endResetModel(model: RawQAbstractListModel) {.cdecl, dynlib:dOtherSideDll, importc.}
proc dos_qabstractlistmodel_dataChanged(model: RawQAbstractListModel,
                                        parentLeft: RawQModelIndex,
                                        bottomRight: RawQModelIndex,
                                        rolesArrayPtr: ptr cint,
                                        rolesArrayLength: cint) {.cdecl, dynlib:dOtherSideDll, importc.}

method rowCount*(model: QAbstractListModel, index: QModelIndex): cint =
  ## Return the model's row count
  return 0

proc rowCountCallback(modelObject: ptr QAbstractListModelObj, rawIndex: RawQModelIndex, result: var cint) {.cdecl, exportc.} =
  debugMsg("QAbstractListModel", "rowCountCallback")
  let model = cast[QAbstractListModel](modelObject)
  let index = newQModelIndex(rawIndex)
  result = model.rowCount(index)

method columnCount*(model: QAbstractListModel, index: QModelIndex): cint =
  ## Return the model's column count
  return 1

proc columnCountCallback(modelObject: ptr QAbstractListModelObj, rawIndex: RawQModelIndex, result: var cint) {.cdecl, exportc.} =
  debugMsg("QAbstractListModel", "columnCountCallback")
  let model = cast[QAbstractListModel](modelObject)
  let index = newQModelIndex(rawIndex)
  result = model.columnCount(index)
  
method data*(model: QAbstractListModel, index: QModelIndex, role: cint): QVariant =
  ## Return the data at the given model index and role
  return nil  
  
proc dataCallback(modelObject: ptr QAbstractListModelObj, rawIndex: RawQModelIndex, role: cint, result: RawQVariant) {.cdecl, exportc.} =
  debugMsg("QAbstractListModel", "dataCallback")
  let model = cast[QAbstractListModel](modelObject)
  let index = newQModelIndex(rawIndex)
  let variant = data(model, index, role)
  if variant != nil:
    dos_qvariant_assign(result, variant.data)
    variant.delete

method setData*(model: QAbstractListModel, index: QModelIndex, value: QVariant, role: cint): bool =
  ## Sets the data at the given index and role. Return true on success, false otherwise
  return false 

proc setDataCallback(modelObject: ptr QAbstractListModelObj, rawIndex: RawQModelIndex, rawQVariant: RawQVariant,  role: cint, result: var bool) {.cdecl, exportc.} =
  debugMsg("QAbstractListModel", "setDataCallback")
  let model = cast[QAbstractListModel](modelObject)
  let index = newQModelIndex(rawIndex)
  let variant = newQVariant(rawQVariant)
  result = model.setData(index, variant, role)
    
method roleNames*(model: QAbstractListModel): Table[cint, cstring] =
  ## Return the model role names  
  result = initTable[cint, cstring]()

proc roleNamesCallback(modelObject: ptr QAbstractListModelObj, hash: RawQHashIntByteArray) {.cdecl, exportc.} =
  debugMsg("QAbstractListModel", "roleNamesCallback")
  let model = cast[QAbstractListModel](modelObject)
  let table = model.roleNames()
  for key, val in table.pairs:
    dos_qhash_int_qbytearray_insert(hash, key, val)

method flags*(model: QAbstractListModel, index: QModelIndex): QtItemFlag =
  ## Return the item flags and the given index
  return QtItemFlag.None

proc flagsCallback(modelObject: ptr QAbstractListModelObj, rawIndex: RawQModelIndex, result: var cint) {.cdecl, exportc.} =
  debugMsg("QAbstractListModel", "flagsCallback")
  let model = cast[QAbstractListModel](modelObject)
  let index = newQModelIndex(rawIndex)
  result = model.flags(index).cint

method headerData*(model: QAbstractListModel, section: cint, orientation: QtOrientation, role: cint): QVariant =
  ## Returns the data for the given role and section in the header with the specified orientation
  return nil

proc headerDataCallback(modelObject: ptr QAbstractListModelObj, section: cint, orientation: cint, role: cint, result: RawQVariant) {.cdecl, exportc.} =
  debugMsg("QAbstractListModel", "headerDataCallback")
  let model = cast[QAbstractListModel](modelObject)
  let variant = model.headerData(section, orientation.QtOrientation, role)
  if variant != nil:
    dos_qvariant_assign(result, variant.data)
    variant.delete
    
proc create*(model: var QAbstractListModel) =
  ## Create a new QAbstractListModel
  debugMsg("QAbstractListModel", "create")
  model.slots = initTable[string,cint]()
  model.signals = initTable[string, cint]()
  model.properties = initTable[string, cint]()
  model.deleted = false
  let modelPtr = addr(model[])
  dos_qabstractlistmodel_create(model.data.RawQAbstractListModel, modelPtr, qobjectCallback, rowCountCallback, columnCountCallback, dataCallback, setDataCallback, roleNamesCallback, flagsCallback, headerDataCallback)
  qobjectRegistry[modelPtr] = true

proc delete*(model: QAbstractListModel) =
  ## Delete the given QAbstractListModel
  if not model.deleted:
    debugMsg("QAbstractListModel", "delete")
    let modelPtr = addr(model[])
    qobjectRegistry.del modelPtr
    dos_qabstractlistmodel_delete(model.data.RawQAbstractListModel)
    model.data = nil.RawQObject
    model.deleted = true

proc newQAbstractListModel*(): QAbstractListModel =
  ## Return a new QAbstractListModel
  new(result, delete)
  result.create()

proc beginInsertRows*(model: QAbstractListModel, parentIndex: QModelIndex, first: int, last: int) =
  ## Notify the view that the model is about to inserting the given number of rows 
  dos_qabstractlistmodel_beginInsertRows(model.data.RawQAbstractListModel, parentIndex.data, first.cint, last.cint)

proc endInsertRows*(model: QAbstractListModel) =
  ## Notify the view that the rows have been inserted
  dos_qabstractlistmodel_endInsertRows(model.data.RawQAbstractListModel)

proc beginRemoveRows*(model: QAbstractListModel, parentIndex: QModelIndex, first: int, last: int) =
  ## Notify the view that the model is about to remove the given number of rows 
  dos_qabstractlistmodel_beginRemoveRows(model.data.RawQAbstractListModel, parentIndex.data, first.cint, last.cint)

proc endRemoveRows*(model: QAbstractListModel) =
  ## Notify the view that the rows have been removed
  dos_qabstractlistmodel_endRemoveRows(model.data.RawQAbstractListModel)

proc beginResetModel*(model: QAbstractListModel) =
  ## Notify the view that the model is about to resetting
  dos_qabstractlistmodel_beginResetModel(model.data.RawQAbstractListModel)

proc endResetModel*(model: QAbstractListModel) =
  ## Notify the view that model has finished resetting
  dos_qabstractlistmodel_endResetModel(model.data.RawQAbstractListModel)

proc dataChanged*(model: QAbstractListModel,
                 topLeft: QModelIndex,
                 bottomRight: QModelIndex,
                 roles: seq[cint]) =
  ## Notify the view that the model data changed
  var copy = roles
  dos_qabstractlistmodel_dataChanged(model.data.RawQAbstractListModel, topLeft.data, bottomRight.data, copy[0].addr, copy.len.cint)  
