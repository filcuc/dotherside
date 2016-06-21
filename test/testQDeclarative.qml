import QtQuick 2.3
import MockModule 1.0

Item {
    id: testCase
    objectName: "testCase"

    Component {
        id: mockQObjectComponent

        MockQObject {}
    }

    function testQmlRegisterType() {
        var testObject = mockQObjectComponent.createObject(testCase, {"name":"foo"})

        if (!testObject)
            return false

        if (testObject.name !== "foo") {
            testObject.destroy()
            return false
        }

        var nameChangedEmitted = false
        testObject.nameChanged.connect(function(name){nameChangedEmitted = name === "bar"});
        testObject.name = "bar"
        if (!nameChangedEmitted || !testObject.name !== "bar") {
            testObject.destroy()
            return false
        }

        testObject.destroy()
        return true
    }
}
