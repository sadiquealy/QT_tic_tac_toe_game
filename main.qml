import QtQuick
import QtQuick.Controls

Window {
    width: 360
    height: 520
    visible: true
    title: qsTr("Hello World")

    Rectangle {
        id: parentRectangle
        color: "cyan"
        anchors.fill: parent
        property int numRows: 4
        property int numColums: 4
        Rectangle {
            x: 0
            y: 0
            color: "#9E2F48"
            id: topRectangle
            anchors.top: parentRectangle.top
            width: parentRectangle.width
            height: (parentRectangle.height / 10)
            border.color: "black"
            Button {
                id: prevButtonTop
                text: "PlayComputer"
                anchors.centerIn: topRectangle
                background: Rectangle {
                    implicitWidth: 100
                    implicitHeight: 40
                    color: prevButtonTop.down ? "#d6d6d6" : "darkcyan"
                    border.color: "#26282a"
                    border.width: 1
                    radius: 4
                }
            }
        }

        Rectangle {
            color: "#A15F47"
            id: middleRectangle
            anchors.top: topRectangle.bottom
            width: parentRectangle.width
            height: (parentRectangle.height * 7 / 10)
            border.color: "black"
            property int clickVal: 1
            Grid {
                id: grid_id1
                columns: parentRectangle.numRows
                rows: parentRectangle.numRows
                spacing: 6
                anchors.centerIn: middleRectangle
                Repeater {
                    id: repeater1
                    model: parent.rows * parent.columns
                    Rectangle {
                        id: cell1
                        color: "darkcyan"
                        width: 50
                        height: 50
                        border.color: "black"

                        Image {
                            id: image1

                            width: cell.width
                            height: cell.height

                            fillMode: Image.PreserveAspectFit
                            source: {
                                if (middleRectangle.clickVal === 0)
                                    ""
                                else if (middleRectangle.clickVal === 1)
                                    ":/images/x.png"
                                else if (middleRectangle.clickVal === 2)
                                    ":/images/0.png"
                            }
                        }
                    }
                }
            }
        }

        Rectangle {
            x: 0
            y: 0
            color: "#A1475C"
            id: bottomRectangle
            anchors.top: middleRectangle.bottom
            width: parentRectangle.width
            height: (parentRectangle.height * 2 / 10)
            border.color: "black"
            radius: 10
        }
    }
}
