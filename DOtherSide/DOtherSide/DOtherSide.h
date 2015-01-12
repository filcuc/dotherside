#ifndef DOTHERSIDE_H
#define DOTHERSIDE_H

#ifdef __cplusplus
extern "C"
{
#endif

  typedef char* CharPtr;
  typedef void(*Function)(void*);
  typedef void(*DObjectCallback)(void*, void*, int, void**);

  // QGuiApplication
  void dos_qguiapplication_create();
  void dos_qguiapplication_exec();
  void dos_qguiapplication_quit();
  void dos_qguiapplication_delete();

  // QApplication
  void dos_qapplication_create();
  void dos_qapplication_exec();
  void dos_qapplication_quit();
  void dos_qapplication_delete();
  
  // QQmlApplicationEngine
  void dos_qqmlapplicationengine_create(void** vptr);
  void dos_qqmlapplicationengine_load(void* vptr, const char* filename);
  void dos_qqmlapplicationengine_context(void* vptr, void** context);
  void dos_qqmlapplicationengine_delete(void* vptr);

  // QQuickView
  void dos_qquickview_create(void** vptr);
  void dos_qquickview_show(void* vptr);
  void dos_qquickview_source(void* vptr, CharPtr& result, int& length);
  void dos_qquickview_set_source(void* vptr, const char* filename);
  void dos_qquickview_delete(void* vptr);
  void dos_qquickview_rootContext(void* vptr, void** context);

  // QQmlContext
  void dos_qqmlcontext_baseUrl(void* vptr, CharPtr& result, int& length);
  void dos_qqmlcontext_setcontextproperty(void* vptr, const char* name, void* value);

  // CharArray
  void dos_chararray_create(CharPtr& ptr, int size);
  void dos_chararray_delete(CharPtr ptr);

  // QVariant
  void dos_qvariant_create(void **vptr);
  void dos_qvariant_create_int(void **vptr, int value);
  void dos_qvariant_create_bool(void **vptr, bool value);
  void dos_qvariant_create_string(void **vptr, const char* value);
  void dos_qvariant_create_qobject(void **vptr, void* value);
  void dos_qvariant_create_qvariant(void **vptr, void* value);
  void dos_qvariant_create_float(void **vptr, float value);
  void dos_qvariant_create_double(void **vptr, double value);
  void dos_qvariant_toInt(void* vptr, int& value);
  void dos_qvariant_setInt(void* vptr, int value);
  void dos_qvariant_toBool(void* vptr, bool& value);
  void dos_qvariant_setBool(void* vptr, bool value);
  void dos_qvariant_toFloat(void* vptr, float& value);
  void dos_qvariant_setFloat(void* vptr, float value);
  void dos_qvariant_toDouble(void* vptr, double& value);
  void dos_qvariant_setDouble(void* vptr, double value);
  void dos_qvariant_toString(void* vptr, CharPtr& ptr, int& size);
  void dos_qvariant_setString(void* vptr, const char* value);
  void dos_qvariant_setQObject(void* vptr, void* value);
  void dos_qvariant_isnull(void *vptr, bool& isNull);
  void dos_qvariant_delete(void *vptr);
  void dos_qvariant_assign(void* vptr, void* other);

  // QObject
  void dos_qobject_create(void **vptr,
			  void *dObjectPointer,
			  DObjectCallback dObjectCallback);

  void dos_qobject_slot_create(void* vptr,
			       const char* name,
			       int parametersCount,
			       int* parametersMetaTypes,
			       int* slotIndex);

  void dos_qobject_signal_create(void* vptr,
				 const char* name,
				 int parametersCount,
				 int* parametersMetaTypes,
				 int* signalIndex);

  void dos_qobject_signal_emit(void* vptr,
			       const char* name,
			       int parametersCount,
			       void** parameters);

  void dos_qobject_property_create(void* vptr,
				   const char* name,
				   int propertyMetaType,
				   const char* readSlot,
				   const char* writeSlot,
				   const char* notifySignal);
  void dos_qobject_delete(void *vptr);

#ifdef __cplusplus
}
#endif

#endif // DOTHERSIDE_H
