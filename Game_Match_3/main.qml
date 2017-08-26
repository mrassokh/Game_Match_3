import QtQuick 2.5
import QtQuick.Controls 1.4
import QtQuick.Dialogs 1.2
import QtQuick.Window 2.1

ApplicationWindow {
    id: mainWindow
    visible: true
    width: logic.getWidth() * 80
    height: logic.getHeight() * 80 + 80
    minimumWidth: 150
    minimumHeight: 230
    maximumWidth: Screen.width - 100
    maximumHeight: Screen.height - 100
    title: qsTr("The Game")


    property int squareSizeX: (width - 5) / logic.getWidth()
    property int squareSizeY: (height - 85) / (logic.getHeight())
    property int animationTime: 1000
    property var images: [
      {'imgPath' : "/dolphin_PNG9125.png"},
      {'imgPath' : "/elephants_PNG18806.png"},
      {'imgPath' : "/falcon_PNG30.png"},
      {'imgPath' : "/flamingo_PNG15114.png"},
      {'imgPath' : "/giraffe_PNG13539.png"},
      {'imgPath' : "/parrot_PNG730.png"},
      {'imgPath' : "/orangutan_PNG24.png"},
    ]

    GameBoard {
        id: gameBoard
    }

    Button {
         id: mixButton
         text: qsTr("Refresh!")
         anchors.left: parent.left
         anchors.right: parent.right
         anchors.top: gameBoard.bottom
         anchors.topMargin: 10
         anchors.leftMargin: 10
         anchors.rightMargin: 10

         onClicked: {
                logic.refresh();
         }
    }

    Button {
         id: exit
         text: qsTr("Exit")
         anchors.left: parent.left
         anchors.right: parent.right
         anchors.top: mixButton.bottom
         anchors.topMargin: 10
         anchors.leftMargin: 10
         anchors.rightMargin: 10

         onClicked: {
            Qt.quit();
         }
    }

    ResultWindow{
        id: resultWindow
   }

    Component.onCompleted: {
           setX(Screen.width / 2 - width / 2);
           setY(Screen.height / 2 - height / 2);
    }
}
