#ifndef DOTHERSIDE_H
#define DOTHERSIDE_H

#ifdef __cplusplus
extern "C"
{
#endif

typedef char* CharPtr;
typedef void(*Function)(void*);
typedef void(*DObjectCallback)(void*, int, int, void**);

void dos_guiapplication_create();
void dos_guiapplication_exec();
void dos_guiapplication_delete();

void dos_quickview_create(void** vptr);
void dos_quickview_show(void* vptr);
void dos_quickview_source(void* vptr, CharPtr& result, int& length);
void dos_quickview_set_source(void* vptr, const char* filename);
void dos_quickview_delete(void* vptr);
void dos_quickview_rootContext(void* vptr, void** context);

void dos_qmlcontext_baseUrl(void* vptr, CharPtr& result, int& length);
void dos_qmlcontext_setcontextproperty(void* vptr, const char* name, void* value);

void dos_chararray_create(CharPtr& ptr, int size);
void dos_chararray_delete(CharPtr& ptr);

void dos_qvariant_create(void **vptr);
void dos_qvariant_create_int(void **vptr, int value);
void dos_qvariant_create_bool(void **vptr, bool value);
void dos_qvariant_create_string(void **vptr, const char* value);
void dos_qvariant_create_qobject(void **vptr, void* value);
void dos_qvariant_toInt(void* vptr, int& value);
void dos_qvariant_setInt(void* vptr, int value);
void dos_qvariant_toBool(void* vptr, bool& value);
void dos_qvariant_setBool(void* vptr, bool value);
void dos_qvariant_toString(void* vptr, CharPtr& ptr, int& size);
void dos_qvariant_setString(void* vptr, const char* value);
void dos_qvariant_isnull(void *vptr, bool& isNull);
void dos_qvariant_delete(void *vptr);

void dos_qobject_create(void **vptr, void *dObjectPointer, DObjectCallback dObjectCallback);
void dos_qobject_slot_create(void* vptr, const char* name, int parametersCount, int* parametersMetaTypes, int* slotIndex);
void dos_qobject_signal_create(void* vptr, const char* name, int parametersCount, int* parametersMetaTypes, int* signalIndex);
void dos_qobject_signal_emit(void* vptr, const char* name, int parametersCount, void** parameters);
void dos_qobject_delete(void *vptr);

#ifdef __cplusplus
}
#endif

#endif // DOTHERSIDE_H
