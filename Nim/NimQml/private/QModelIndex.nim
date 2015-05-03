proc dos_qmodelindex_create(modelIndex: var RawQModelIndex) {.cdecl, dynlib:dOtherSideDll, importc.}
proc dos_qmodelindex_delete(modelIndex: RawQModelIndex) {.cdecl, dynlib:dOtherSideDll, importc.}
proc dos_qmodelindex_row(modelIndex: RawQModelIndex, row: var cint) {.cdecl, dynlib:dOtherSideDll, importc.}
proc dos_qmodelindex_column(modelIndex: RawQModelIndex, column: var cint) {.cdecl, dynlib:dOtherSideDll, importc.}
proc dos_qmodelindex_isValid(modelIndex: RawQModelIndex, column: var bool) {.cdecl, dynlib:dOtherSideDll, importc.}
proc dos_qmodelindex_data(modelIndex: RawQModelIndex, role: cint, data: RawQVariant) {.cdecl, dynlib:dOtherSideDll, importc.}
proc dos_qmodelindex_parent(modelIndex: RawQModelIndex, parent: RawQModelIndex) {.cdecl, dynlib:dOtherSideDll, importc.}
proc dos_qmodelindex_child(modelIndex: RawQModelIndex, row: cint, column: cint, parent: RawQModelIndex) {.cdecl, dynlib:dOtherSideDll, importc.}
proc dos_qmodelindex_sibling(modelIndex: RawQModelIndex, row: cint, column: cint, sibling: RawQModelIndex) {.cdecl, dynlib:dOtherSideDll, importc.}

proc create*(modelIndex: var QModelIndex) =
  ## Create a new QModelIndex
  dos_qmodelindex_create(modelIndex.data)
  modelIndex.deleted = false

proc create*(modelIndex: var QModelIndex, rawQModelIndex: RawQModelIndex) =
  ## Create a new QModelIndex
  modelIndex.data = rawQModelIndex
  modelIndex.deleted = false
  
proc delete*(modelIndex: QModelIndex) =
  ## Delete the given QModelIndex
  if not modelIndex.deleted:
    debugMsg("QModelIndex", "delete")
    dos_qmodelindex_delete(modelIndex.data)
    modelIndex.data = nil.RawQModelIndex
    modelIndex.deleted = true

proc newQModelIndex*(): QModelIndex =
  ## Return a new QModelIndex
  new(result, delete)
  result.create()

proc newQModelIndex*(rawQModelIndex: RawQModelIndex): QModelIndex =
  ## Return a new QModelIndex given a raw index
  new(result, delete)
  result.create(rawQModelIndex)

proc row*(modelIndex: QModelIndex): cint =
  ## Return the index row
  dos_qmodelindex_row(modelIndex.data, result)

proc column*(modelIndex: QModelIndex): cint =
  ## Return the index column
  dos_qmodelindex_column(modelIndex.data, result)

proc isValid*(modelIndex: QModelIndex): bool =
  ## Return true if the index is valid, false otherwise
  dos_qmodelindex_isValid(modelIndex.data, result)

proc data*(modelIndex: QModelIndex, role: cint): QVariant =
  ## Return the model data associated to the given role  
  result = newQVariant()
  dos_qmodelindex_data(modelIndex.data, role, result.data)

proc parent*(modelIndex: QModelIndex): QModelIndex =
  ## Return the parent index
  result = newQModelIndex()
  dos_qmodelindex_parent(modelIndex.data, result.data)

proc child*(modelIndex: QModelIndex, row: cint, column: cint): QModelIndex =
  ## Return the child index associated to the given row and column
  result = newQModelIndex()
  dos_qmodelindex_child(modelIndex.data, row, column, result.data)

proc sibling*(modelIndex: QModelIndex, row: cint, column: cint): QModelIndex =
  ## Return the sibling index associated to the given row and column
  result = newQModelIndex()
  dos_qmodelindex_sibling(modelIndex.data, row, column, result.data)
