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
            MenuItem { text: "&Load"; onTriggered: logic.onLoadTriggered() }
            MenuItem { text: "&Save"; onTriggered: logic.onSaveTriggered() }
            MenuItem { text: "&Exit"; onTriggered: logic.onExitTriggered() }
        }
    }
    
	ColumnLayout
	{
	    anchors.fill: parent

        ScrollView
        {
            Layout.fillWidth: true
            Layout.fillHeight: true

            ListView
            {
                model: logic.contactList
                spacing: 5
                delegate: RowLayout {
                    width: ListView.view.width
                    TextField { Layout.fillWidth: true; text: firstName }
                    TextField { Layout.fillWidth: true; text: surname }
                    Button { text: "Delete"; onClicked: logic.delContact(index) }
                }
            }
        }

        RowLayout
        {
            Label { text: "Name" }
            TextField { id: nameTextField; Layout.fillWidth: true; text: "" }
            Label { text: "Surname" }
            TextField { id: surnameTextField; Layout.fillWidth: true; text: "" }
            Button { text: "Add"; onClicked: logic.addContact(nameTextField.text, surnameTextField.text) }
        }
	}
}
