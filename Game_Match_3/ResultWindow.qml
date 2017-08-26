import QtQuick 2.0
import QtQuick.Window 2.2
import QtQuick.Controls 1.3


ApplicationWindow {
    title: qsTr("Game Over!!!")
    color: "orchid"
    visible: false
    width: 400
    height: 80
    modality: Qt.WindowModal

    Rectangle{
        id: labelItem
        x:0
        y:0
        height: 40
        width: 400
        color: "bisque"

        Label {
            id: label
            anchors.centerIn: parent
            text: logic.getResultText()
      }
    }

    Button{
        id: newGame
        text: qsTr("New Game")
        width: 150
        anchors.left: parent.left
        anchors.top:  labelItem.bottom
        anchors.topMargin: 10
        anchors.leftMargin: 25
        anchors.rightMargin: 25

        onClicked: {
            logic.refresh();
             resultWindow.hide();
        }
    }

    Button{
        id: exitGame
        text: qsTr("Exit")
        width: 150
        anchors.left: newGame.right
        anchors.top:  labelItem.bottom
        anchors.topMargin: 10
        anchors.leftMargin: 50
        anchors.rightMargin: 25

        onClicked: {
            Qt.quit();
        }
     }
    onVisibleChanged: {
       label.text = logic.getResultText();
    }
}
