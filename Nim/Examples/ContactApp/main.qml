import QtQuick 2.2
import QtQuick.Controls 1.2
import QtQuick.Layouts 1.1
import QtQuick.Window 2.1

ApplicationWindow
{
	width: 400
	height: 300
    title: "ContactApp"
	visible: true

    menuBar: MenuBar {
        Menu
        {
            title: "&File"
            MenuItem { text: "Load"; onTriggered: logic.onLoadTriggered() }
            MenuItem { text: "Save"; onTriggered: logic.onSaveTriggered() }
            MenuItem { text: "Exit"; onTriggered: logic.onExitTriggered() }
        }
    }
    
	ColumnLayout
	{
	    anchors.fill: parent
        
        ListView
        {
            Layout.fillWidth: true
            Layout.fillHeight: true
            model: logic.contactList.count
            spacing: 5
            delegate: RowLayout {
                width: ListView.view.width
                property QtObject contact: logic.contactList.get(index)
                TextField { Layout.fillWidth: true; text: contact.firstName }
                TextField { Layout.fillWidth: true; text: contact.surname }
                Button { text: "Save" }
                Button { text: "Delete"; onClicked: logic.contactList.del(index) }
            }
        }

        RowLayout
        {
            Label { text: "Name" }
            TextField { id: nameTextField; Layout.fillWidth: true; text: "" }
            Label { text: "Surname" }
            TextField { id: surnameTextField; Layout.fillWidth: true; text: "" }
            Button { text: "Add"; onClicked: logic.contactList.add(nameTextField.text, surnameTextField.text) }
        }
	}
}
