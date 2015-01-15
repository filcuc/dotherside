import QtQuick 2.2
import QtQuick.Controls 1.2
import QtQuick.Layouts 1.1
import QtQuick.Window 2.1

ApplicationWindow
{
    width: 400
    height: 300
    title: "SimpleData"
    Component.onCompleted: visible = true

    ColumnLayout
    {
        anchors.fill: parent
        SpinBox { value: qVar1}
        TextField { text: qVar2}
        CheckBox { checked: qVar3}
        SpinBox { value: qVar4; decimals: 1 }
    }
}
