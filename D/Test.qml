import QtQuick 2.3

Rectangle
{
  width: 100
  height: 100
  color: "red"
  
  Text
  {
    anchors.fill: parent
    text: model
  }
  
  Component.onCompleted: {
    var result = myObject.tor("sfsdk");
    console.log("From qml received value:", result)
  }

  Connections
  {
    target: myObject
    onNameChanged: console.log("name changed in qml ")
  }
}