#include <MockQObject.h>
#include <Global.h>
#include <QMetaType>

using namespace std;

namespace {
    std::string toStringFromQVariant(DosQVariant* variant) {
        CharPointer charArray(dos_qvariant_toString(variant), &dos_chararray_delete);
        return std::string(charArray.get());
    }

    VoidPointer initializeMetaObject()
    {
        void* superClassMetaObject = dos_qobject_qmetaobject();
        // Signals
        ::SignalDefinition signalDefinitionArray[1];
        signalDefinitionArray[0].name = "nameChanged";
        signalDefinitionArray[0].parametersCount = 1;
        int nameChanged[1];
        nameChanged[0] = QMetaType::QString;
        signalDefinitionArray[0].parametersMetaTypes = nameChanged;

        ::SignalDefinitions signalDefinitions;
        signalDefinitions.count = 1;
        signalDefinitions.definitions = signalDefinitionArray;

        // Slots
        ::SlotDefinition slotDefinitionArray[2];

        slotDefinitionArray[0].name = "name";
        slotDefinitionArray[0].returnMetaType = QMetaType::QString;
        slotDefinitionArray[0].parametersCount = 0;
        slotDefinitionArray[0].parametersMetaTypes = nullptr;

        slotDefinitionArray[1].name = "setName";
        slotDefinitionArray[1].returnMetaType = QMetaType::Void;
        int setNameParameters[1];
        setNameParameters[0] = QMetaType::QString;
        slotDefinitionArray[1].parametersCount = 1;
        slotDefinitionArray[1].parametersMetaTypes = setNameParameters;

        ::SlotDefinitions slotDefinitions;
        slotDefinitions.count = 2;
        slotDefinitions.definitions = slotDefinitionArray;

        // Properties
        ::PropertyDefinition propertyDefinitionArray[1];
        propertyDefinitionArray[0].name = "name";
        propertyDefinitionArray[0].notifySignal = "nameChanged";
        propertyDefinitionArray[0].propertyMetaType = QMetaType::QString;
        propertyDefinitionArray[0].readSlot = "name";
        propertyDefinitionArray[0].writeSlot = "setName";

        ::PropertyDefinitions propertyDefinitions;
        propertyDefinitions.count = 1;
        propertyDefinitions.definitions = propertyDefinitionArray;

        return VoidPointer(dos_qmetaobject_create(superClassMetaObject, "MockQObject", &signalDefinitions, &slotDefinitions, &propertyDefinitions),
                           &dos_qmetaobject_delete);
    }
}


MockQObject::MockQObject()
    : m_vptr(dos_qobject_create(this, metaObject(), &onSlotCalled), &dos_qobject_delete)
{}

MockQObject::~MockQObject() = default;

DosQMetaObject *MockQObject::staticMetaObject()
{
    static VoidPointer result = initializeMetaObject();
    return result.get();
}

::DosQMetaObject *MockQObject::metaObject()
{
    return staticMetaObject();
}

std::string MockQObject::objectName() const
{
    CharPointer result (dos_qobject_objectName(m_vptr.get()), &dos_chararray_delete);
    return string(result.get());
}

void MockQObject::setObjectName(const string &objectName)
{
    dos_qobject_setObjectName(m_vptr.get(), objectName.c_str());
}

::DosQObject *MockQObject::data()
{
    return m_vptr.get();
}

void MockQObject::swapData(VoidPointer &data)
{
    std::swap(m_vptr, data);
}

std::string MockQObject::name() const
{
    return m_name;
}

void MockQObject::setName(const string &name)
{
    if (name == m_name)
        return;
    m_name = name;
    nameChanged(name);
}

void MockQObject::nameChanged(const string &name)
{
    int argc = 1;
    DosQVariant* argv[1];
    argv[0] = dos_qvariant_create_string(name.c_str());
    dos_qobject_signal_emit(m_vptr.get(), "nameChanged", argc, argv);
    dos_qvariant_delete(argv[0]);
}

void MockQObject::onSlotCalled(void *selfVPtr, DosQVariant *dosSlotNameVariant, int dosSlotArgc, DosQVariant **dosSlotArgv) {
    MockQObject* self = static_cast<MockQObject*>(selfVPtr);

    string slotName = toStringFromQVariant(dosSlotNameVariant);
    if (slotName == "name") {
        VoidPointer name(dos_qvariant_create_string(self->name().c_str()), &dos_qvariant_delete);
        dos_qvariant_assign(dosSlotArgv[0], name.get());
        return;
    }

    if (slotName == "setName") {
        self->setName(toStringFromQVariant(dosSlotArgv[1]));
        return;
    }
}
