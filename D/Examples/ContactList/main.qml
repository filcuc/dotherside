import QtQuick 2.3
import QtQuick.Controls 1.2
import QtQuick.Layouts 1.1
import QtQuick.Window 2.1

ApplicationWindow {
    width: 400
    height: 300

    Component.onCompleted: visible = true

    ColumnLayout {
        anchors.fill: parent
        ListView {
            Layout.fillWidth: true
            Layout.fillHeight: true
            model: contactList.count
            delegate: Label {
                property QtObject contact: contactList.getContact(index)
                text: contact.firstName + " " + contact.lastName
            }
        }
        
        RowLayout {
            Layout.fillWidth: true
            Item { Layout.fillWidth: true }
            Button {
                Layout.preferredWidth: 100
                text: "Add"
                onClicked: contactList.addContact("NewFirstName", "NewLastName")
            }
            Item { width: 10; }
        }
    }
}
