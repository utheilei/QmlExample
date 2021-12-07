import QtQuick 2.7
import QtQuick.Controls 2.4
import QtQuick.Layouts 1.0
import "../"
import "./account"
import "./unionid"
import "./display"
import "./defaultapp"

Rectangle {
    id: mainRectangle
    color: "transparent"
    radius: 20

    property var listWidget: [accountWidget, unionIDWidget, displayWidget, defaultAppWidget]

    HLListView {
        id: listView
        anchors.left: parent.left
        anchors.top: parent.top
        anchors.bottom: parent.bottom
        width: parent.width/5
        model: qmlHelper.listModel()
        iconVisible: true
        clip: true
        onCurrentIndexChanged: rightRectangle.setCurrentIndex(currentIndex)
        leftMargin: 10
        rightMargin: 10
        topMargin: 10
        bottomMargin: 10
    }

    Item {
        id: rightRectangle
        anchors.left: listView.right
        anchors.top: parent.top
        anchors.topMargin: 10
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 10
        anchors.right: parent.right
        anchors.rightMargin: 10
        clip: true

        AccountWidget {
            id: accountWidget
            anchors.fill: parent
            visible: true
        }

        UnionIDWidget {
            id: unionIDWidget
            anchors.fill: parent
            visible: false
        }

        DisplayWidget {
            id: displayWidget
            anchors.fill: parent
            visible: false
        }

        DefaultAppWidget {
            id: defaultAppWidget
            anchors.fill: parent
            visible: false
        }

        function setCurrentIndex(index) {
            if (index >= listWidget.length)
                return

            for (var i=0; i<listWidget.length; i++) {
                if (i === index)
                    listWidget[i].visible = true
                else
                    listWidget[i].visible = false
            }
        }
    }

    function setCurrentItem(index) {
        listView.currentIndex = index
    }
}
