type QMetaType* {.pure.} = enum ## \
  ## Qt metatypes values used for specifing the 
  ## signals and slots argument and return types.
  ##
  ## This enum mimic the QMetaType::Type C++ enum
  UnknownType = cint(0), 
  Bool = cint(1),
  Int = cint(2), 
  QString = cint(10), 
  VoidStar = cint(31),
  QObjectStar = cint(39),
  QVariant = cint(41), 
  Void = cint(43),
