extern(C)
{
    // QApplication
    void dos_qapplication_create();
    void dos_qapplication_exec();
    void dos_qapplication_delete();
    void dos_qapplication_quit();

    // QGuiApplication
    void dos_qguiapplication_create();
    void dos_qguiapplication_exec();
    void dos_qguiapplication_delete();
    void dos_qguiapplication_quit();
  
    // QQmlApplicationEngine
    void dos_qqmlapplicationengine_create(ref void*);
    void dos_qqmlapplicationengine_load(void*, immutable (char)* filename);
    void dos_qqmlapplicationengine_context(void*, ref void*);
    void dos_qqmlapplicationengine_delete(void*);

    // QQuickView
    void dos_qquickview_create(ref void*);
    void dos_qquickview_show(void*);
    void dos_qquickview_source(void*, ref char *);
    void dos_qquickview_set_source(void*, immutable (char)* filename);
    void dos_qquickview_rootContext(void*, ref void*);
    void dos_qquickview_delete(void*);

    // CharArray
    void dos_chararray_delete(char*);

    // QQmlContext
    void dos_qqmlcontext_baseUrl(void*, ref char*);
    void dos_qqmlcontext_setcontextproperty(void*, immutable (char)*, void*);

    // QVariant
    void dos_qvariant_create(ref void*);
    void dos_qvariant_create_int(ref void*, int);
    void dos_qvariant_create_bool(ref void*, bool);
    void dos_qvariant_create_string(ref void*, immutable(char)*);
    void dos_qvariant_create_qobject(ref void*, void*);
    void dos_qvariant_create_float(ref void*, float);
    void dos_qvariant_create_double(ref void*, double);
    void dos_qvariant_toInt(void*, ref int);
    void dos_qvariant_setInt(void*, int);
    void dos_qvariant_toBool(void*, ref bool);
    void dos_qvariant_setBool(void*, bool);
    void dos_qvariant_toString(void*, ref char*);
    void dos_qvariant_setString(void*, immutable(char)*);
    void dos_qvariant_toFloat(void*, ref float);
    void dos_qvariant_setFloat(void*, float);
    void dos_qvariant_toDouble(void*, ref double);
    void dos_qvariant_setDouble(void*, double);
    void dos_qvariant_isnull(void*, ref bool);
    void dos_qvariant_delete(void*);
    void dos_qvariant_assign(void*, void*);
    void dos_qvariant_setQObject(void*, void*);

    // QObject
    void dos_qobject_create(ref void*,
                            void* dobject,
                            void function (void*, void*, int , void**));

    void dos_qobject_slot_create(void*,
                                 immutable (char)* name,
                                 int parametersCount,
                                 int* parametersMetaTypes,
                                 ref int slotIndex);

    void dos_qobject_signal_create(void*,
                                   immutable(char)* name,
                                   int parametersCount,
                                   int* parametersMetaTypes,
                                   ref int signalIndex);

    void dos_qobject_signal_emit(void*, immutable(char)* name,
                                 int parametersCount,
                                 void** parameters);

    void dos_qobject_property_create(void*,
                                     immutable(char)* name,
                                     int propertyMetaType,
                                     immutable(char)* readSlot,
                                     immutable(char)* writeSlot,
                                     immutable(char)* notifySignal);

    void dos_qobject_delete(void*);

    // QModelIndex
    void dos_qmodelindex_create(ref void* index);
    void dos_qmodelindex_delete(void* index);
    void dos_qmodelindex_row(void*, ref int result);
    void dos_qmodelindex_column(void*, ref int result);
    void dos_qmodelindex_isValid(void* index, ref bool result);
    void dos_qmodelindex_data(void* index, int role, void* variant);
    void dos_qmodelindex_parent(void* index, void* parent);
    void dos_qmodelindex_child(void* index, int r, int c, void* child);
    void dos_qmodelindex_sibling(void* index, int r, int c, void* sibling);

    // QHashIntByteArray
    void dos_qhash_int_qbytearray_create(ref void*);
    void dos_qhash_int_qbytearray_delete(void*);
    void dos_qhash_int_qbytearray_insert(void*, int, immutable(char)*);
    void dos_qhash_int_qbytearray_value(void*, int, ref char*);
}
