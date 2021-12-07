import QtQuick 2.7
import QtQuick.Controls 2.4
import QtQuick.Layouts 1.0
import QuickItemDelegate 1.0
import IconItemModel 1.0
import Qt.labs.platform 1.0
import an.window 1.0
import "../../"
import "../../controls"

Item {
    enum LoginType {
        AutoLogin,
        NoPassWordLogin
    }

    property var listViewModel: [["帐户", "qrc:/icon/dcc_nav_accounts_84px.svg"]]

    Rectangle {
        id: leftRectangle
        width: parent.width/3.5
        height: parent.height
        anchors.top: parent.top
        anchors.left: parent.left
        radius: 10
        HLListView {
            id: accoutView
            width: parent.width
            height: parent.height - circleButton.height
            anchors.top: parent.top
            anchors.left: parent.left
            model: listViewModel
            itemColor: sPalette.alternateBase
            iconVisible: true
            clip: true
            onCurrentIndexChanged: console.info(currentIndex)
            leftMargin: 10
            rightMargin: 10
            topMargin: 10
            bottomMargin: 10
        }

        HLCircleButton {
            id: circleButton
            width: 44
            height: 44
            anchors.top: accoutView.bottom
            anchors.left: parent.left
            anchors.leftMargin: (parent.width - width)/2
            onButtonPressed: {
                contentScrollView.visible = false;
                newAccoutLoader.source = "qrc:/controlcenter/account/NewAccout.qml"
            }
        }
    }

    Rectangle {
        id: rightRectangle
        anchors.left: leftRectangle.right
        anchors.leftMargin: 5
        anchors.top: parent.top
        width: parent.width - leftRectangle.width - 5
        height: parent.height
        radius: 10

        ScrollView {
            id: contentScrollView
            anchors.fill: parent
            clip: true
            Column {
                id: column
                anchors.fill: parent
                topPadding: 50
                spacing: 5

                ArrowCircleButton {
                    id: arrowCircleButton
                    width: 80
                    height: 80
                    source: ":/icon/images/images1.png"
                    anchors.horizontalCenter: parent.horizontalCenter

                    onCheckedChanged: {iconView.visible = isChecked}
                }

                Item {
                    width: rowLayout.implicitWidth
                    height: rowLayout.implicitHeight
                    anchors.horizontalCenter: parent.horizontalCenter
                    Row {
                        id: rowLayout
                        anchors.fill: parent
                        spacing: 5
                        Image {
                            source: "qrc:/icon/images/images6.png"
                            anchors.verticalCenter: parent.verticalCenter
                        }
                        Label {
                            enabled: false
                            text: qsTr("yaphetshl")
                            anchors.verticalCenter: parent.verticalCenter
                        }
                    }
                }

                Item {
                    width: fullNameLayout.implicitWidth
                    height: 38
                    anchors.horizontalCenter: parent.horizontalCenter
                    Row {
                        id: fullNameLayout
                        anchors.fill: parent
                        leftPadding: 20
                        spacing: 5
                        Label {
                            id: fullName
                            text: qsTr("yaphetshl")
                            enabled: false
                            anchors.verticalCenter: parent.verticalCenter
                        }
                        Image {
                            id: editImage
                            source: "qrc:/icon/images/edit_normal.png"
                            anchors.verticalCenter: parent.verticalCenter

                            MouseArea {
                                anchors.fill: parent
                                onClicked: {
                                    fullName.visible = false;
                                    editImage.visible = false;
                                    fullNameEdit.forceActiveFocus();
                                    fullNameEdit.visible = true;
                                }
                            }
                        }

                        QmlLineEdit {
                            id: fullNameEdit
                            width: contentScrollView.width - 40
                            anchors.verticalCenter: parent.verticalCenter
                            visible: false
                            focus: true
                            focusReason: Qt.MouseFocusReason

                            onReturnPressed: {
                                if (fullNameEdit.text !== "") {
                                    fullName.text = fullNameEdit.text;
                                    fullNameEdit.clear();
                                }
                                fullNameEdit.visible = false;
                                fullName.visible = true;
                                editImage.visible = true;
                            }
                        }

                        move: Transition {
                            NumberAnimation { properties: "x,y"; duration: 1000}
                        }
                    }
                }

                IconView {
                    id: iconView
                    visible: false
                    anchors.horizontalCenter: parent.horizontalCenter
                    repeaterModel: iconItemModel

                    IconItemModel {
                        id: iconItemModel
                    }

                    onAddItem: fileDialog.open()

                    onIconClicked: {arrowCircleButton.source = source;arrowCircleButton.checked = false}
                }

                Row {
                    id: buttonLayout
                    anchors.horizontalCenter: parent.horizontalCenter
                    spacing: 10
                    topPadding: 30
                    bottomPadding: 30
                    leftPadding: 20
                    QmlButton {
                        width: (contentScrollView.width - 50)/2
                        height: 35
                        text: qsTr("修改密码")
                        anchors.verticalCenter: parent.verticalCenter
                    }
                    QmlButton {
                        id: deleteButton
                        width: (contentScrollView.width - 50)/2
                        height: 35
                        text: qsTr("删除帐户")
                        textColor: "#FD5D71"
                        anchors.verticalCenter: parent.verticalCenter
                    }
                }

                HLRoundedWidget {
                    width: contentScrollView.width - 40
                    height: content.contentHeight
                    anchors.left: parent.left
                    anchors.leftMargin: 20

                    ListModel {
                        id: viewModel
                        ListElement {
                            name: qsTr("自动登录")
                            type: 0
                        }
                        ListElement {
                            name: qsTr("无密码登录")
                            type: 1
                        }
                    }

                    ListView {
                        id: content
                        anchors.fill: parent
                        spacing: 2
                        model: viewModel
                        delegate: viewDelegate
                        clip: true
                        Component {
                            id: viewDelegate
                            Rectangle {
                                height: 36
                                width: content.width
                                color: sPalette.alternateBase
                                Text {
                                    text: name
                                    anchors.left: parent.left
                                    anchors.leftMargin: 10
                                    anchors.verticalCenter: parent.verticalCenter
                                    color: sPalette.text
                                }

                                Switch {
                                    anchors.right: parent.right
                                    anchors.verticalCenter: parent.verticalCenter

                                    onClicked: {console.info(checked);console.info(type);}
                                }
                            }
                        }
                    }
                }
            }
        }

        Loader {
            id: newAccoutLoader
            anchors.fill: parent

            function onDeleteThis() {
                newAccoutLoader.item.visible = false;
                contentScrollView.visible = true;
                newAccoutLoader.source = ''
            }

            onLoaded: {
                newAccoutLoader.item.closeAccoutItem.connect(newAccoutLoader.onDeleteThis)
            }
        }
    }

    FileDialog {
        id: fileDialog
        title: "Please choose a file"
        folder: StandardPaths.writableLocation(StandardPaths.DesktopLocation)
        fileMode: FileDialog.OpenFiles
        visible: false
        onAccepted: {
            var fileName = fileDialog.file.toString();
            console.log("You chose: " + fileName)
            iconItemModel.insertItem(iconItemModel.rowCount() - 1, [Qt.Unchecked, fileName])
        }
    }
}
