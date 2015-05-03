proc dos_qvariant_create(variant: var RawQVariant) {.cdecl, dynlib:dOtherSideDll, importc.}
proc dos_qvariant_create_int(variant: var RawQVariant, value: cint) {.cdecl, dynlib:dOtherSideDll, importc.}
proc dos_qvariant_create_bool(variant: var RawQVariant, value: bool) {.cdecl, dynlib:dOtherSideDll, importc.}
proc dos_qvariant_create_string(variant: var RawQVariant, value: cstring) {.cdecl, dynlib:dOtherSideDll, importc.}
proc dos_qvariant_create_qobject(variant: var RawQVariant, value: RawQObject) {.cdecl, dynlib:dOtherSideDll, importc.}
proc dos_qvariant_create_qvariant(variant: var RawQVariant, value: RawQVariant) {.cdecl, dynlib:dOtherSideDll, importc.}
proc dos_qvariant_create_float(variant: var RawQVariant, value: cfloat) {.cdecl, dynlib:dOtherSideDll, importc.}
proc dos_qvariant_create_double(variant: var RawQVariant, value: cdouble) {.cdecl, dynlib:dOtherSideDll, importc.}
proc dos_qvariant_delete(variant: RawQVariant) {.cdecl, dynlib:dOtherSideDll, importc.}
proc dos_qvariant_isnull(variant: RawQVariant, isNull: var bool) {.cdecl, dynlib:dOtherSideDll, importc.}
proc dos_qvariant_toInt(variant: RawQVariant, value: var cint) {.cdecl, dynlib:dOtherSideDll, importc.}
proc dos_qvariant_toBool(variant: RawQVariant, value: var bool) {.cdecl, dynlib:dOtherSideDll, importc.}
proc dos_qvariant_toString(variant: RawQVariant, value: var cstring) {.cdecl, dynlib:dOtherSideDll, importc.}
proc dos_qvariant_setInt(variant: RawQVariant, value: cint) {.cdecl, dynlib:dOtherSideDll, importc.}
proc dos_qvariant_setBool(variant: RawQVariant, value: bool) {.cdecl, dynlib:dOtherSideDll, importc.}
proc dos_qvariant_setString(variant: RawQVariant, value: cstring) {.cdecl, dynlib:dOtherSideDll, importc.}
proc dos_qvariant_assign(leftValue: RawQVariant, rightValue: RawQVariant) {.cdecl, dynlib:dOtherSideDll, importc.}
proc dos_qvariant_toFloat(variant: RawQVariant, value: var cfloat) {.cdecl, dynlib:dOtherSideDll, importc.}
proc dos_qvariant_setFloat(variant: RawQVariant, value: float)  {.cdecl, dynlib:dOtherSideDll, importc.}
proc dos_qvariant_toDouble(variant: RawQVariant, value: var cdouble) {.cdecl, dynlib:dOtherSideDll, importc.}
proc dos_qvariant_setDouble(variant: RawQVariant, value: cdouble) {.cdecl, dynlib:dOtherSideDll, importc.}
proc dos_qvariant_setQObject(variant: RawQVariant, value: RawQObject) {.cdecl, dynlib:dOtherSideDll, importc.}
proc dos_chararray_delete(rawCString: cstring) {.cdecl, dynlib:dOtherSideDll, importc.}

proc create*(variant: QVariant) =
  ## Create a new QVariant
  dos_qvariant_create(variant.data)
  variant.deleted = false

proc create*(variant: QVariant, value: cint) = 
  ## Create a new QVariant given a cint value
  dos_qvariant_create_int(variant.data, value)
  variant.deleted = false

proc create*(variant: QVariant, value: bool) =
  ## Create a new QVariant given a bool value  
  dos_qvariant_create_bool(variant.data, value)
  variant.deleted = false

proc create*(variant: QVariant, value: string) = 
  ## Create a new QVariant given a string value
  dos_qvariant_create_string(variant.data, value)
  variant.deleted = false

proc create*(variant: QVariant, value: QObject) =
  ## Create a new QVariant given a QObject
  dos_qvariant_create_qobject(variant.data, value.data.RawQObject)
  variant.deleted = false

proc create(variant: QVariant, value: RawQVariant) =
  ## Create a new QVariant given another QVariant.
  ## The inner value of the QVariant is copied
  dos_qvariant_create_qvariant(variant.data, value)
  variant.deleted = false
  
proc create(variant: QVariant, value: cfloat) =
  ## Create a new QVariant given a cfloat value
  dos_qvariant_create_float(variant.data, value)
  variant.deleted = false

proc create(variant: QVariant, value: QVariant) =
  ## Create a new QVariant given another QVariant.
  ## The inner value of the QVariant is copied
  create(variant, value.data)
  
proc delete*(variant: QVariant) = 
  ## Delete a QVariant
  if not variant.deleted:
    debugMsg("QVariant", "delete")
    dos_qvariant_delete(variant.data)
    variant.data = nil.RawQVariant
    variant.deleted = true

proc newQVariant*(): QVariant =
  ## Return a new QVariant  
  new(result, delete)
  result.create()

proc newQVariant*(value: cint): QVariant =
  ## Return a new QVariant given a cint
  new(result, delete)
  result.create(value)

proc newQVariant*(value: bool): QVariant  =
  ## Return a new QVariant given a bool
  new(result, delete)
  result.create(value)

proc newQVariant*(value: string): QVariant  =
  ## Return a new QVariant given a string
  new(result, delete)
  result.create(value)

proc newQVariant*(value: QObject): QVariant  =
  ## Return a new QVariant given a QObject
  new(result, delete)
  result.create(value)

proc newQVariant*(value: RawQVariant): QVariant =
  ## Return a new QVariant given a raw QVariant pointer
  new(result, delete)
  result.create(value)

proc newQVariant*(value: QVariant): QVariant =
  ## Return a new QVariant given another QVariant
  new(result, delete)
  result.create(value)

proc newQVariant*(value: float): QVariant =
  ## Return a new QVariant given a float
  new(result, delete)
  result.create(value)
  
proc isNull*(variant: QVariant): bool = 
  ## Return true if the QVariant value is null, false otherwise
  dos_qvariant_isnull(variant.data, result)

proc intVal*(variant: QVariant): int = 
  ## Return the QVariant value as int
  var rawValue: cint
  dos_qvariant_toInt(variant.data, rawValue)
  result = rawValue.cint

proc `intVal=`*(variant: QVariant, value: int) = 
  ## Sets the QVariant value int value
  var rawValue = value.cint
  dos_qvariant_setInt(variant.data, rawValue)

proc boolVal*(variant: QVariant): bool = 
  ## Return the QVariant value as bool
  dos_qvariant_toBool(variant.data, result)

proc `boolVal=`*(variant: QVariant, value: bool) =
  ## Sets the QVariant bool value
  dos_qvariant_setBool(variant.data, value)

proc floatVal*(variant: QVariant): float =
  ## Return the QVariant value as float
  var rawValue: cfloat
  dos_qvariant_toFloat(variant.data, rawValue)
  result = rawValue.cfloat

proc `floatVal=`*(variant: QVariant, value: float) =
  ## Sets the QVariant float value
  dos_qvariant_setFloat(variant.data, value.cfloat)  

proc doubleVal*(variant: QVariant): cdouble =
  ## Return the QVariant value as double
  var rawValue: cdouble
  dos_qvariant_toDouble(variant.data, rawValue)
  result = rawValue

proc `doubleVal=`*(variant: QVariant, value: cdouble) =
  ## Sets the QVariant double value
  dos_qvariant_setDouble(variant.data, value)  
  
proc stringVal*(variant: QVariant): string = 
  ## Return the QVariant value as string
  var rawCString: cstring
  dos_qvariant_toString(variant.data, rawCString)
  result = $rawCString
  dos_chararray_delete(rawCString)

proc `stringVal=`*(variant: QVariant, value: string) = 
  ## Sets the QVariant string value
  dos_qvariant_setString(variant.data, value)

proc `qobjectVal=`*(variant: QVariant, value: QObject) =
  ## Sets the QVariant qobject value
  dos_qvariant_setQObject(variant.data, value.data.RawQObject)
  
proc assign*(leftValue: QVariant, rightValue: QVariant) =
  ## Assign a QVariant with another. The inner value of the QVariant is copied
  dos_qvariant_assign(leftValue.data, rightValue.data)  
