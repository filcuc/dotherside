import QtQuick 2.2
import QtQuick.Controls 1.2
import QtQuick.Window 2.1

ApplicationWindow
{
	width: 400
	height: 300
	Component.onCompleted: {
	    visible = true 
	    myQObject.myVoidSlot()
	    myQObject.myIntSlot(10)
	    var result = myQObject.myIntSlot2(20)
	    console.log("QML: result ", result)
        myQObject.intValueChanged.connect(temp)
	}

	function temp()
	{
	    console.log("temp called")
	}

	Button
	{
	    anchors.centerIn: parent
	    text: "Click Me"
	    onClicked: myQObject.myVoidSlot()
	}
}
