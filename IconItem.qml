import QtQuick 2.7

Rectangle {
    id: item
    property alias icon: image.source
    property alias label: text.text
    signal itemClicked

    implicitWidth: Math.max(text.implicitWidth, image.implicitWidth) + 20
    implicitHeight: image.implicitHeight + text.implicitHeight + 25
    radius: 20
    color: sPalette.base

    Image {
        id: image
        fillMode: Image.PreserveAspectFit
        anchors.centerIn: parent
    }

    Text {
        id: text
        wrapMode: Text.Wrap
        anchors.top: image.bottom
        anchors.topMargin: 10
        anchors.horizontalCenter: parent.horizontalCenter
        color: sPalette.text
    }

    MouseArea {
        anchors.fill: parent
        hoverEnabled: true
        onClicked: itemClicked()
        onEntered: item.color = sPalette.button
        onExited: item.color = sPalette.base
    }
}
