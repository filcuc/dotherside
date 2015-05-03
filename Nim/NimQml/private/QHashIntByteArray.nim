proc dos_qhash_int_qbytearray_create(qHash: var RawQHashIntByteArray) {.cdecl, dynlib:dOtherSideDll, importc.}
proc dos_qhash_int_qbytearray_delete(qHash: RawQHashIntByteArray) {.cdecl, dynlib:dOtherSideDll, importc.}
proc dos_qhash_int_qbytearray_insert(qHash: RawQHashIntByteArray, key: int, value: cstring) {.cdecl, dynlib:dOtherSideDll, importc.}
proc dos_qhash_int_qbytearray_value(qHash: RawQHashIntByteArray, key: int, value: var cstring) {.cdecl, dynlib:dOtherSideDll, importc.}

proc create(qHash: var QHashIntByteArray) =
  ## Create the QHash
  debugMsg("QHashIntByteArray", "create")
  dos_qhash_int_qbytearray_create(qHash.data)
  qHash.deleted = false

proc delete*(qHash: QHashIntByteArray) =
  ## Delete the QHash
  if not qHash.deleted:
    debugMsg("QHashIntByteArray", "delete")  
    dos_qhash_int_qbytearray_delete(qHash.data)
    qHash.deleted = true

proc insert*(qHash: QHashIntByteArray, key: int, value: cstring) =
  ## Insert the value at the given key
  dos_qhash_int_qbytearray_insert(qHash.data, key, value)

proc value*(qHash: QHashIntByteArray, key: int): string =
  ## Return the value associated at the given key  
  var rawString: cstring
  dos_qhash_int_qbytearray_value(qHash.data, key, rawString)
  result = $rawString
  dos_chararray_delete(rawString)

proc newQHashIntQByteArray*(): QHashIntByteArray =
  ## Create a new QHashIntQByteArray  
  new(result, delete)
  result.create()
