import QtQuick 2.7
import QtQuick.Controls 2.4
import QtQuick.Layouts 1.0
import QtQuick.Controls 1.4 as Old
import QtQuick.Controls.Styles 1.4
import an.model 1.0
import "../../"
import "../../controls"

Item {
    id: displayWidget

    TreeModel {
        id: treeModel
    }

    HLRoundedWidget {
        id: roundedWidget
        anchors.top: parent.top
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.margins: 20
        width: 300
        height: parent.height/5*2
        color: sPalette.alternateBase

        Old.TreeView {
            id: treeView
            anchors.fill: parent
//            anchors.margins: 5
            model: treeModel
            backgroundVisible: false
            alternatingRowColors : false
            sortIndicatorVisible:true
            horizontalScrollBarPolicy: Qt.ScrollBarAlwaysOff
            headerVisible: false
            frameVisible : false

            onDoubleClicked: {
                isExpanded(index) ? collapse(index) : expand(index)
            }

            Old.TableViewColumn {
                title: "Name"
                role: "fileName"
                width: treeView.viewport.width
            }

            style: TreeViewStyle {
                branchDelegate : Image {
                    anchors.centerIn: parent
                    sourceSize: Qt.size(15, 15)
                    source: styleData.isExpanded ? "qrc:/icon/dcc_expand_48px.svg" : "qrc:/icon/dcc_collapse_48px.svg"
                }
                itemDelegate: Rectangle {
                    color: styleData.selected ? sPalette.highlight : sPalette.alternateBase
                    height: 26
                    radius: 10
                    Image {
                        id: icon
                        anchors.left: parent.left
                        anchors.leftMargin: 10
                        anchors.verticalCenter: parent.verticalCenter
                        sourceSize: Qt.size(16, 16)
                        source: treeModel.item(styleData.index, 1)
                    }
                    Text {
                        anchors.left: icon.right
                        anchors.verticalCenter: parent.verticalCenter
                        leftPadding: 10
                        color: styleData.selected ? sPalette.highlightedText : sPalette.text
                        elide: styleData.elideMode
                        text: treeModel.item(styleData.index)
                    }
                }

                rowDelegate: Rectangle {
                    height: 26
                    color: "transparent"
                }
            }
        }
    }

    HLTableView {
        id: hlTableView
        anchors.top: roundedWidget.bottom
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.margins: 20
        width: 500
    }
}
