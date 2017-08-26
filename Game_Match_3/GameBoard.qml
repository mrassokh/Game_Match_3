import QtQuick 2.0
import "functions.js" as Functions

Item {
    id: gameBoard
    width: parent.width
    height: parent.height - 80
    Rectangle {
        width: parent.width
        height: parent.height
        color: "lightgreen"
        Repeater {
            model: logic
            width: parent.width
            height: parent.height
            property bool click: false

            Image {
                width: squareSizeX - 5;
                height: squareSizeY - 5
                x: squareSizeX * positionX + 6
                y: squareSizeY * (positionY - logic.getHeight() ) + 3
                opacity: vis
                source: images[type].imgPath

                Behavior on x { PropertyAnimation { duration:  animationTime ; easing.type: Easing.OutQuart } }
                Behavior on y { PropertyAnimation { duration:  animationTime; easing.type: Easing.OutQuart } }
                Behavior on opacity { PropertyAnimation { duration:  animationTime; easing.type: Easing.InQuart } }


                MouseArea {
                    property int startIndex: 0
                    property int endIndex: 0
                    anchors.fill: parent

                    Timer {
                         id: timer
                         interval:  animationTime + 100; running: false; repeat: false
                         onTriggered: {logic.swapElements(logic.getStartIndex(), logic.getEndIndex());}
                     }

                    Timer {
                         id: timer1
                         interval:  animationTime + 100; running: false; repeat: false
                         onTriggered: {logic.bubbleSwapEmptyElements()}
                     }

                    Timer {
                         id: timer2
                         interval:  animationTime * 2 + 100; running: false; repeat: false
                         onTriggered: { Functions.recursiveMatch(timer1, timer2);}
                     }

                     onClicked: {
                         Functions.clickProccesing(timer,timer1,timer2, index);
                     }
                }
            }
        }
    }
}

