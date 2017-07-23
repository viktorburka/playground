import QtQuick 2.5
import QtQuick.Window 2.2

import "minesweeper.js" as Ms

Window {

    visible: true
    width: 600; height: 600

    Rectangle {
        id: field
        anchors.fill: parent
        color: "lightgray"

        Rectangle {
            id: outline
            anchors.fill: parent
            anchors.margins: 20
            border.width: 2
            border.color: "darkred"
            Canvas {
                anchors.fill: parent
                id: canvas
                onPaint:{
                    var ctx = canvas.getContext('2d');
                    Ms.field.renderOn(ctx, width, height);
                }
                onImageLoaded: canvas.requestPaint()
            }
            MouseArea {
                anchors.fill: parent
                onClicked: {
                    console.log("Clicked")
                }
            }
        }
    }

    Component.onCompleted: {

        canvas.loadImage('qrc:/images/closed_button.png')
        canvas.loadImage('qrc:/images/opened_button.png')
        canvas.loadImage('qrc:/images/bomb.png')

        Ms.shuffle(Ms.field)
//        Ms.field.oneach(function(cell) {
//            console.log('row: ', cell.row, 'column: ', cell.column, 'bomb: ', cell.bomb)
//        })
    }
}

