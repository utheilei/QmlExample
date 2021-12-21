import QtQuick 2.7
import QtQuick.Controls 2.4
import "../../"
import "../../controls"

Item {
    id: defaultWidget

    QmlButton {
        x: 20
        y: 180
        backgroundDefaultColor: sPalette.highlight
        text: qsTr("open")

        onClicked: {dialog.open()}
    }

    QmlDialog {
        id: dialog

        Component.onCompleted: {
            setIcon("qrc:/icon/dialog.svg")
            setTitle("MyDialog")
            setContentTitle("Title")
            setMessage("Hello world")
        }

        onAccepted: {
            console.info(dialog.clickBtnText)
        }

        onRejected: {
            console.info(dialog.clickBtnText)
        }
    }

    QmlWaterProgress {
        id: qmlWaterProgress
        width: 200
        height: 200
        anchors.centerIn: parent
        runing: true
    }

    Slider {
        id: slider
        anchors.top: qmlWaterProgress.bottom
        anchors.horizontalCenter: parent.horizontalCenter
        from: 0
        value: 30
        to: 100
        onMoved: qmlWaterProgress.setValue(slider.value)
    }
}
