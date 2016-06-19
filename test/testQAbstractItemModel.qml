import QtQuick 2.3

QtObject {
    id: testCase
    objectName: "testCase"

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
