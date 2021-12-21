import QtQuick 2.4
import QtQuick.Controls 2.4
import QtQuick.Layouts 1.0

ToolBar {
    leftPadding: 10
    property bool isMax: false
    property alias buttonEnabled: leftButton.enabled

    background: Rectangle {
        width: parent.width
        height: 50
        radius: 20

        Rectangle {
            width: parent.width
            height: parent.height/2
            anchors.bottom: parent.bottom
            anchors.left: parent.left
        }
    }
    RowLayout {
        anchors.fill: parent
        Image {
            id: titleImage
            source: "qrc:/icon/controlcenter_24px.svg"
            sourceSize: Qt.size(40, 40)
        }
        QmlButton {
            id: leftButton
            Layout.leftMargin: 10
            icon.source: "qrc:/icon/left.svg"
            implicitWidth: 35
            implicitHeight: 35
            enabled: myLoader.sourceComponent === mainPage
            onClicked: myLoader.sourceComponent = loginPage
        }
        Rectangle {
            id: contentRectangle
            Layout.fillWidth: true
        }
        HLButton {
            id: menuButton
            width: titleBar.height
            height: titleBar.height
            icon.source: "qrc:/icon/menu.svg"
            icon.width: 20
            icon.height: 20
            onClicked: barMenu.open(menuButton)
        }
        HLButton {
            width: titleBar.height
            height: titleBar.height
            icon.source: "qrc:/icon/hide.svg"
            icon.width: 20
            icon.height: 20
            onClicked: root.showMinimized()
        }
        HLButton {
            id: maxButton
            width: titleBar.height
            height: titleBar.height
            icon.source: "qrc:/icon/max.svg"
            icon.width: 20
            icon.height: 20
            onClicked: showWindow()
        }
        HLButton {
            width: titleBar.height
            height: titleBar.height
            buttonPosition: 3
            icon.source: "qrc:/icon/close.svg"
            icon.width: 20
            icon.height: 20
            onClicked: Qt.quit()
        }
    }

    Label {
        id: name
        text: root.title
        anchors.centerIn: parent
    }

    function showWindow() {
        if (!isMax) {
            root.showFullScreen()
            maxButton.icon.source = "qrc:/icon/min.svg"
        } else {
            root.showNormal()
            maxButton.icon.source = "qrc:/icon/max.svg"
        }
        isMax = !isMax
    }
}
