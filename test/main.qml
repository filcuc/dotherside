import QtQuick 2.4
import QtQuick.Controls 1.3

ApplicationWindow {
    width: 100
    height: 100
    objectName: "testWindow"
    Component.onCompleted: {
        visible = true
        console.log(testObject)
        console.log(testObject.name)
    }
}
