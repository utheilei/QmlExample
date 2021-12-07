import QtQuick 2.7
import QtQuick.Controls 2.4
import QtQuick.Window 2.11
import QtQuick.Controls.Styles 1.4
import Qt.labs.platform 1.0
import an.window 1.0

ScreenShotItem {
    visible: true
    width: 800
    height: 600

    SystemPalette {
        id: sPalette
        colorGroup: SystemPalette.Active
    }

    Image {
        id: backgroudImage
        anchors.fill: parent
    }

    Rectangle {
        anchors.fill: parent
        color: Qt.rgba(0.498039, 0.501961, 0.501961, 0.501961)
    }

    ImageItem {
        id: screenShotImage
        objectName: "screenShotImage"
    }

    Rectangle {
        id: toolBar
        z: 10
        width: rowLayout.implicitWidth + 40
        radius: 10
        height: 40
        anchors.top: screenShotImage.bottom
        anchors.right: screenShotImage.right
        visible: false

        Row {
            id: rowLayout
            anchors.centerIn: parent
            spacing: 30
            Repeater {
                model: ["qrc:/icon/download.svg",
                    "qrc:/icon/error.svg",
                    "qrc:/icon/yes.svg"]
                QmlButton {
                    anchors.verticalCenter: parent.verticalCenter
                    backgroundDefaultColor: sPalette.base
                    width: 35
                    height: 35
                    icon.source: modelData

                    onClicked: buttonClicked(index)
                }
            }
        }
    }

    FileDialog {
        id: fileDialog
        title: "Please choose a file"
        folder: StandardPaths.writableLocation(StandardPaths.DesktopLocation)
        fileMode: FileDialog.SaveFile
        nameFilters: ["Image files (*.png *.jpg *.jpeg *.svg)"]
        visible: false
        onAccepted: {
            saveScreenShotImage(1, fileDialog.file.toString())
        }
    }

    function buttonClicked(index) {
        switch(index) {
        case 0:
            fileDialog.open()
            break
        case 1:
            close()
            break
        case 2:
            saveScreenShotImage(0);
            break
        default:
            break
        }
    }

    function showToolBar(isVisible) {
       toolBar.visible = isVisible
    }

    function setBackgroudImage() {
       backgroudImage.source = "image://BackgroudView/" + "###" + Date.now();
    }
}
