import QtQuick 2.7
import QtQuick.Controls 2.4

Item {
    id: name
    signal returnPressed
    property alias text: qmlLineEdit.text

    QmlLineEdit {
        id: qmlLineEdit
        width: parent.width - qmlButton.width - 10
        height: parent.height
        isPassword: true
        anchors.left: parent.left
        anchors.verticalCenter: parent.verticalCenter

        onReturnPressed: {name.returnPressed()}
    }

    QmlButton {
        id: qmlButton
        width: qmlLineEdit.height + 2
        height: qmlLineEdit.height
        anchors.left: qmlLineEdit.right
        anchors.leftMargin: 10
        anchors.verticalCenter: parent.verticalCenter
        backgroundDefaultColor: sPalette.highlight
        icon.source: "qrc:/show.svg"

        onClicked: {
            qmlLineEdit.isPassword = !qmlLineEdit.isPassword
            icon.source = qmlLineEdit.isPassword ? "qrc:/show.svg" : "qrc:/hide.svg"
        }
    }

    function lineEdit() {
        return qmlLineEdit
    }

    function showAlertMessage(text, duration) {
        qmlLineEdit.showAlertMessage(text, duration)
    }
}


