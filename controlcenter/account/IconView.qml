import QtQuick 2.7
import QtQuick.Controls 2.4
import QtQuick.Layouts 1.0
import QuickItemDelegate 1.0
import an.window 1.0
import "../../"
import "../../controls"

Item {
    signal iconClicked(var source);
    signal addItem;

    property var repeaterModel
    property int itemWidth: 80
    property int itemHeight: 80
    property var paddings: [20, 40, 0, 0]

    width: parent.width - 20
    height: flowlayout.implicitHeight

    Flow {
        id: flowlayout
        anchors.fill: parent
        spacing: 10
        topPadding: paddings[0]
        leftPadding: paddings[1]
        clip: true

        Repeater {
            id: repeaterlist
            model: repeaterModel
            delegate: listDelegate
        }

        Component {
            id: listDelegate
            QuickItemDelegate {
                width: itemWidth
                height: itemHeight
                source: repeaterModel.item(index, 1)
                checked: repeaterModel.item(index, 10)

                onMouseStatusChanged: {
                    if (repeaterModel.rowCount() < 1)
                        return
                    if (index === repeaterModel.rowCount()-1) {
                        addItem()
                    } else {
                        for(var i=0; i<repeaterModel.rowCount()-1; i++) {
                            if (index === i) {
                                repeaterlist.itemAt(i).checked = Qt.Checked
                                iconClicked(repeaterModel.item(i, 1))
                            }
                            else {
                                repeaterlist.itemAt(i).checked = Qt.Unchecked
                            }
                        }
                    }
                }
            }
        }
    }
}


