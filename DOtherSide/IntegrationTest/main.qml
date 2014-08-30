import QtQuick 2.2
import QtQuick.Window 2.1

Window {
    visible: true
    width: 360
    height: 360

    MouseArea {
        anchors.fill: parent
        onClicked: {
            Qt.quit();
        }
    }

    Text {
        text: qsTr("Hello World")
        anchors.centerIn: parent
    }

    Component.onCompleted: {
        console.log(dynamicQObject)
        var result = 0;
        result = dynamicQObject.foo();
        console.log("Result:", result)
        result = dynamicQObject.bar(10);
        console.log("Result:", result)
    }


    Connections
    {
        target: dynamicQObject
        onNameChanged: console.log("Name Changed");
    }
}
