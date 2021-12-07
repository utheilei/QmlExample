import QtQuick 2.7
import QtQuick.Controls 2.4
import QtQuick.Layouts 1.0
import Qt.labs.platform 1.0
import QtGraphicalEffects 1.0
import an.window 1.0
import "../../"
import "../../controls"

Item {
    id: unionIDWidget

    HLRoundedWidget {
        anchors.fill: parent
        Image {
            anchors.fill: parent
            source: "qrc:/icon/images/backgroud.jpeg"
        }
    }

    ListView {
        id: listView
        anchors.top: parent.top
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.margins: 20
        width: parent.width - 30
        height: parent.height/5*3
        spacing: 15
        model: listModel
        delegate: listDelegate
        highlightFollowsCurrentItem: false
        onModelChanged: listView.positionViewAtEnd();

        Component.onCompleted: listModel.clear()
    }

    Item {
        id: middleBar
        width: parent.width
        height: 40
        anchors.top: listView.bottom
        anchors.left: parent.left

        Row {
            anchors.centerIn: parent
            spacing: 30
            Repeater {
                model: ["qrc:/icon/images/font.svg",
                    "qrc:/icon/images/fontcolor.svg",
                    "qrc:/icon/images/expression.svg",
                    "qrc:/icon/images/picture.svg",
                    "qrc:/icon/images/screenshot.svg"]
                QmlButton {
                    anchors.verticalCenter: parent.verticalCenter
                    width: 30
                    height: 30
                    icon.source: modelData

                    onClicked: buttonClicked(index)
                }
            }
        }
    }

    HLTextArea {
        id: inputTextArea
        anchors.top: middleBar.bottom
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.bottom: parent.bottom

        background: Rectangle {
            radius: 8
            color: sPalette.button
        }

        function sendMessage(isPeer) {
            if (inputTextArea.length === 0) {
                control.text = qsTr("消息内容不能为空！")
                control.visible = true
                return
            }
            listModel.append({"roles": isPeer, "messages":inputTextArea.text})
            inputTextArea.clearText()
        }
    }

    QmlButton {
        id: sendButton
        width: 80
        height: 30
        anchors.bottom: parent.bottom
        anchors.right: parent.right
        anchors.margins: 10
        backgroundDefaultColor: sPalette.highlight
        text: qsTr("发送")
        onClicked: inputTextArea.sendMessage(false)
    }

    QmlButton {
        width: 80
        height: 30
        anchors.right: sendButton.left
        anchors.bottom: parent.bottom
        anchors.margins: 10
        backgroundDefaultColor: sPalette.highlight
        text: qsTr("对方发送")
        onClicked: inputTextArea.sendMessage(true)
    }

    ToolTip {
        id: control
        visible: false
        timeout: 3000
        parent: sendButton
        padding: 5

        contentItem: Text {
            text: control.text
            font: control.font
            color: Qt.rgba(0.945, 0.224, 0.196, 1)
        }

        background: Rectangle {
            color: sPalette.base
            radius: 8
            layer.enabled: true
            layer.effect: DropShadow {
                transparentBorder: true
                radius: 8.0
                samples: 17
                color: "#80000000"
            }
        }
    }

    Component {
        id: listDelegate
        Item {
            width: listView.width
            height: hlTextArea.contentHeight + 10
            Row {
                anchors.fill: parent
                layoutDirection: roles ? Qt.LeftToRight : Qt.RightToLeft
                spacing: 10

                AnimatedImage {
                    id: animatedImage
                    playing: true
                    width: 40
                    height: 40
                    mipmap: true
                    source: roles ? "qrc:/icon/images/woman.svg" : "qrc:/icon/images/man.svg"
                    anchors.verticalCenter: parent.verticalCenter
                }

                HLTextArea {
                    id: hlTextArea
                    text: messages
                    readOnly: true
                    maximumWidth: listView.width - 120
                    anchors.verticalCenter: parent.verticalCenter
                    background: Rectangle {
                        radius: 8
                        color: roles ? sPalette.base : sPalette.highlight
                    }
                }
            }
        }
    }

    ListModel {
        id: listModel
        ListElement { roles: true; messages: "#E4E4E4";}
    }

    FontDialog {
        id: fontDialog
        currentFont.family: inputTextArea.font
        visible: false
        onAccepted: inputTextArea.font = fontDialog.currentFont
    }

    ColorDialog {
        id: colorDialog
        currentColor: inputTextArea.color
        onAccepted: inputTextArea.color = colorDialog.color
    }

    FileDialog {
        id: fileDialog
        title: "Please choose a file"
        folder: StandardPaths.writableLocation(StandardPaths.DesktopLocation)
        fileMode: FileDialog.OpenFile
        nameFilters: ["Image files (*.git *.GIF *.png *.jpg *.jpeg *.svg)"]
        visible: false
        onAccepted: {
            inputTextArea.insertQuickImage(fileDialog.file)
        }
    }

    ScrollView {
        id: scrollView
        padding: 10
        width: 300
        height: 200
        anchors.bottom: middleBar.top
        anchors.horizontalCenter: parent.horizontalCenter
        clip: true
        visible: false
        background: Rectangle {
            radius: 10
            color: sPalette.alternateBase
        }
        Grid {
            anchors.fill: parent
            rowSpacing: 8
            columnSpacing: 8
            columns: Math.floor(scrollView.width/50)

            Repeater {
                model: 111
                AnimatedImage {
                    playing: true
                    width: 40
                    height: 40
                    mipmap: true
                    source: "qrc:/icon/wxFace/" + (index + 1) + ".gif"

                    MouseArea {
                        anchors.fill: parent
                        onClicked: {
                            inputTextArea.insertQuickImage(source)
                            scrollView.visible = false
                        }
                    }
                }
            }
        }
    }

    Connections {
        target: screenShotWindow
        onSaveFinished: {
            if (saveResult[2] === 0)
                inputTextArea.insertQuickImage(saveResult[3])
        }
    }

    function buttonClicked(index) {
        switch(index) {
        case 0:
            fontDialog.open()
            break
        case 1:
            colorDialog.open()
            break
        case 2:
            scrollView.visible = !scrollView.visible
            break
        case 3:
            fileDialog.open()
            break
        case 4:
            screenShotWindow.showFullScreen()
            break
        default:
            break
        }
    }
}
