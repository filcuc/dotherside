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
    var result1 = myObject.bar(1);
    var result2 = myObject.foo(2);
    var result3 = myObject.tor("3")
    console.log("From qml received values:", result1, result2, result3)
  }

  Connections
  {
    target: myObject
    onNameChanged: console.log("name changed in qml ")
  }
}