#pragma once

#include <Global.h>

class MockQObject
{
public:
    MockQObject();

    ::DosQMetaObject *metaObject();
    ::DosQObject *data();

    std::string objectName() const;
    void setObjectName(const std::string& objectName);

    std::string name() const;
    void setName(const std::string& name);
    void nameChanged(const std::string& name);

private:
    static void onSlotCalled(void *selfVPtr, DosQVariant *dosSlotNameVariant, int dosSlotArgc, DosQVariant **dosSlotArgv);

    VoidPointer m_vptr;
    std::string m_name;
};
