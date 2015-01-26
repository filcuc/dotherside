import QtQuick 2.2
import QtQuick.Controls 1.2
import QtQuick.Layouts 1.1
import QtQuick.Window 2.1

ApplicationWindow
{
    width: 400
    height: 300
    title: "AbstractItemModel"
    Component.onCompleted: visible = true

    Component
    {
        id: myListModelDelegate
        Rectangle
        {
            width: 10
            height: 10
            color: index % 2 == 0 ? "red" : "black"
        }
    }
    
    ListView
    {
        anchors.fill: parent
        model: myListModel
        delegate: myListModelDelegate
    }
}