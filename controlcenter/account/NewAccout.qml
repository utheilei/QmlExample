import QtQuick 2.7
import QtQuick.Controls 2.4
import QtQuick.Layouts 1.0
import QuickItemDelegate 1.0
import IconItemModel 1.0
import an.window 1.0
import "../../"
import "../../controls"

Item {
    id: accoutItem

    property var currentSource
    signal newAccoutClicked(var source);
    signal closeAccoutItem();
    Label {
        id: titleLabel
        topPadding: 20
        text: qsTr("新帐户")
        font.pixelSize: 20
        anchors.top: parent.top
        anchors.horizontalCenter: parent.horizontalCenter
    }

    IconView {
        id: accoutIconView
        repeaterModel: iconItemModel
        anchors.top: titleLabel.bottom
        anchors.horizontalCenter: parent.horizontalCenter
        paddings: [20, 20, 0, 0]
        itemWidth: 40
        itemHeight: 40

        onAddItem: fileDialog.open()
        onIconClicked: {newAccoutClicked(source); currentSource = source}
    }

    Column {
        id: columnLayout
        anchors.top: accoutIconView.bottom
        anchors.left: parent.left
        anchors.right: parent.right
        spacing: 10
        topPadding: 20
        leftPadding: 20
        rightPadding: 20

        ListModel {
            id: columnModel
            ListElement {
                name: qsTr("用户名:")
                type: false
            }
            ListElement {
                name: qsTr("全名:")
                type: false
            }
            ListElement {
                name: qsTr("密码:")
                type: true
            }
            ListElement {
                name: qsTr("重复密码:")
                type: true
            }
        }

        Repeater {
            id: columnRepeater
            model: columnModel

            Item {
                width: repeaterItem.implicitWidth
                height: repeaterItem.implicitHeight
                Column {
                    id: repeaterItem
                    anchors.fill: parent
                    spacing: 5
                    Text {
                        text: name
                    }
                    Loader {
                        id: myLoader
                        width: accoutItem.width - 40
                        height: 38
                        source: type ? "qrc:/QmlPassWordLineEdit.qml" : "qrc:/QmlLineEdit.qml"
                    }
                }
                Connections {
                    target: myLoader.item
                    onReturnPressed: {handleLineEdit(index, myLoader.item)}
                }

                function lineEdit() {
                    return myLoader.item
                }
            }
        }
    }

    Row {
        anchors.bottom: parent.bottom
        anchors.horizontalCenter: parent.horizontalCenter
        spacing: 10
        bottomPadding: 20

        QmlButton {
            width: (accoutItem.width - 50)/2
            height: 35
            text: qsTr("取消")
            anchors.verticalCenter: parent.verticalCenter

            onClicked: {accoutItem.closeAccoutItem()}
        }
        QmlButton {
            id: creatButton
            width: (accoutItem.width - 50)/2
            height: 35
            text: qsTr("创建帐户")
            anchors.verticalCenter: parent.verticalCenter
            backgroundDefaultColor: sPalette.highlight

            onClicked: {
                var array = [];
                for (var i=0;i<columnRepeater.count;i++)
                    array.push(columnRepeater.itemAt(i).lineEdit().text);

                var result = Utils.checkPassword(array);

                if (!result[0] && result[2] !== "")
                    columnRepeater.itemAt(result[1]).lineEdit().showAlertMessage(result[2], 3000)

                if (result[0]) {
                    listViewModel.push([columnRepeater.itemAt(0).lineEdit().text, currentSource]);
                    accoutView.model = listViewModel
                    accoutItem.closeAccoutItem()
                }
            }
        }
    }

    function handleLineEdit(index, object) {
        if (object === null || object === undefined)
            return;

        if (columnRepeater.itemAt(index).lineEdit().text === "")
            columnRepeater.itemAt(index).lineEdit().showAlertMessage(qsTr("Content cannot be empty"), 3000)
    }
}


