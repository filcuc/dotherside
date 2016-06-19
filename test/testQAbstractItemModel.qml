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

    function testRowCount() {
        return testObject && testObject.rowCount() === 4
    }

    function testColumnCount() {
        return testObject && testObject.columnCount() === 1;
    }

    function testData() {
        return testObject && testObject.data(testObject.index(0,0, null)) === "John"
                          && testObject.data(testObject.index(1,0, null)) === "Mary"
                          && testObject.data(testObject.index(2,0, null)) === "Andy"
                          && testObject.data(testObject.index(3,0, null)) === "Anna"
    }
}
