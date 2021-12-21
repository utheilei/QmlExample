import QtQuick 2.7
import QtQuick.Controls 2.4

Item {
    property alias prePixmap: currentImage.source
    property alias nextPixmap: effectImage.source
    signal animationFinished

    Image {
        id: currentImage
        anchors.fill: parent
    }

    Image {
        id: effectImage
        property real percentage: 1.0
        anchors.centerIn: parent
        width: parent.width * percentage
        height: parent.height * percentage
        transform: Rotation {
            origin.x: effectImage.width/2
            origin.y: effectImage.height/2
            axis { x: 0; y: 0; z: 1 }
            angle: 360 * effectImage.percentage
        }
    }

    NumberAnimation {
        id: imageAnimation
        target: effectImage
        property: "percentage"
        from: 0.0
        to: 1.0
        duration: 2000
        onStopped: animationFinished()
    }

    function start() {
        imageAnimation.start()
    }

    function stop() {
        imageAnimation.stop()
    }
}


