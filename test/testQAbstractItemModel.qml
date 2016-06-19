import QtQuick 2.3

QtObject {
    id: testCase
    objectName: "testCase"

    function testRowCount() {
        if (!testObject)
            return false
        return testObject.rowCount() === 4
    }

    function testColumnCount() {
        if (!testObject)
            return false
        return testObject.columnCount() === 0;
    }

    function testData() {
        return true
    }
}
