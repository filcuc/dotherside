import QtQuick 2.0

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
    //myObject.foo()
    var result = myObject.bar(1345);
    console.log("From qml received value:", result)
  }
}