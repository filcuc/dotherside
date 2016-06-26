import QtQuick 2.3

QtObject {
    id: testCase
    objectName: "testCase"

    function testObjectName() {
        return testObject && testObject.objectName === "testObject"
    }

    function testPropertyReadAndWrite() {
        if (!testObject)
            return false
        if (testObject.name !== "foo")
            return false
        testObject.name = "bar"
        if (testObject.name !== "bar")
            return false
        return true
    }

    function testSignalEmittion() {
        if (!testObject)
            return false
        if (testObject.name !== "foo")
            return false
        var result = false
        testObject.nameChanged.connect(function(name){ result = name === "bar" })
        testObject.name = "bar"
        return result
    }
}
