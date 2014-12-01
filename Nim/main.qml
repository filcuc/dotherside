import QtQuick 2.2
import QtQuick.Controls 1.2
import QtQuick.Window 2.1

ApplicationWindow
{
	width: 400
	height: 300
	Component.onCompleted: visible = true

	Button
	{
	    anchors.centerIn: parent
	    text: "Click Me"
	}
}
