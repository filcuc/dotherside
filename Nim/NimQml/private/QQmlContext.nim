proc dos_qqmlcontext_setcontextproperty(context: QQmlContext, propertyName: cstring, propertyValue: RawQVariant) {.cdecl, dynlib:dOtherSideDll, importc.}

proc setContextProperty*(context: QQmlContext, propertyName: string, propertyValue: QVariant) = 
  ## Sets a new property with the given value
  dos_qqmlcontext_setcontextproperty(context, propertyName, propertyValue.data)
