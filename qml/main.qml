import QtQuick
import QtQuick.Controls

Window {
    width: 360
    height: 520
    visible: true
    title: qsTr("Tic Tac Toe Game V.1.0.0")
    property list<Rectangle> rectList
    property int numRows: _game_board.rows
    property int numColums: _game_board.columns
    property bool enableButton: false
    property int gameOver: 0
    Connections {
        target: _game_board
        function onUpdateCell(row, column) {
            console.log("recieved signal from c++ row:", row, "column:", column)
            rectList[row * numRows + column].stateVal = 2

            showMessage("Player Turn; Click on your cell")
        }
    }

    Connections {
        target: _game_board
        function onShowStatus(message) {
            showMessage(message)
            enableButton = true
            gameOver = 1
        }
    }

    function showMessage(msg) {
        messageTxt.text = msg
    }
    function resetCells(msg) {
        for (var i = 0; i < numRows * numColums; i++) {
            rectList[i].stateVal = 0
        }
    }
    Rectangle {
        id: parentRectangle
        color: "cyan"
        anchors.fill: parent

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
                text: gameOver ? "Reset" : "Play Computer"
                anchors.centerIn: topRectangle
                enabled: enableButton
                background: Rectangle {
                    implicitWidth: 100
                    implicitHeight: 40
                    color: prevButtonTop.down ? "#d6d6d6" : "darkcyan"
                    border.color: "#26282a"
                    border.width: 1
                    radius: 4
                }
                onClicked: {
                    if (gameOver) {
                        _game_board.resetBoard()
                        gameOver = 0
                        enableButton = false
                        resetCells()
                        showMessage("Player Turn; Click on your cell")
                    } else {
                        enableButton = false
                        _game_board.playComputer()
                    }
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
                columns: numRows
                rows: numColums
                spacing: 6
                anchors.centerIn: middleRectangle
                Repeater {
                    id: repeater
                    model: parent.rows * parent.columns
                    Rectangle {
                        id: cell
                        color: "darkcyan"
                        width: 50
                        height: 50
                        border.color: "black"
                        property int stateVal: 0
                        Component.onCompleted: {
                            console.log("Loading rectangle index is", index)
                            if (repeater.count > 0) {
                                rectList.push(repeater.itemAt(index))
                                // do something
                            }
                        }
                        Image {
                            id: image1

                            width: cell.width
                            height: cell.height

                            fillMode: Image.PreserveAspectFit
                            source: {
                                if (cell.stateVal == 0)
                                    ""
                                else if (cell.stateVal == 1)
                                    "images/x.png"
                                else if (cell.stateVal == 2)
                                    "images/0.png"
                            }
                        }

                        MouseArea {
                            id: mouse
                            anchors.fill: parent
                            enabled: !enableButton && !stateVal

                            onClicked: {
                                showMessage("Computer Turn; Click on playComputer Button")
                                cell.stateVal = 1
                                var index_field = parseInt(model.index)
                                var row = Math.floor(
                                            index_field / _game_board.columns)
                                var col = index_field % _game_board.columns
                                _game_board.onCellClick(row, col)
                                enableButton = true
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
            //radius: 10
            Text {
                id: messageTxt
                text: "Player Turn; Click on your cell"
                font.family: "Helvetica"
                font.pointSize: 13
                color: "black"
                anchors.centerIn: bottomRectangle
            }
        }
    }
}
