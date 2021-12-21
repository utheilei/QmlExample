import QtQuick 2.7
import QtQuick.Controls 2.4
import QtQuick.Layouts 1.0
import QtGraphicalEffects 1.0
import an.window 1.0
import "../../"
import "../../controls"

Item {
    id: networkWidget

    property var imageList: ["qrc:/icon/images/nba.jpeg", "qrc:/icon/images/pixmap1.jpeg",
        "qrc:/icon/images/pixmap2.jpg", "qrc:/icon/images/pixmap3.jpg", "qrc:/icon/images/pixmap4.jpg"]

    property int currentIndex: 0

    HLRoundedWidget {
        anchors.fill: parent
        color: sPalette.base

        HLRotationImage {
            id: rotationImage
            anchors.fill: parent
            prePixmap: imageList[currentImage(currentIndex)]
            nextPixmap: imageList[currentImage(currentIndex + 1)]
            visible: false

            onAnimationFinished: {
                currentIndex++
                rotationImage.visible = false
                blindsItem.visible = true
                blindsItem.start()
            }
        }

        BlindsItem {
            id: blindsItem
            anchors.fill: parent
            prePixmap: imageList[currentImage(currentIndex)]
            nextPixmap: imageList[currentImage(currentIndex + 1)]
            orientation: Qt.Horizontal
            visible: false

            onFactorChanged: {
                if (factor === 1.0) {
                    currentIndex++
                    blindsItem.visible = false
                    pieImageItem.visible = true
                    pieImageItem.start()
                }
            }
        }

        PieImageItem {
            id: pieImageItem
            anchors.fill: parent
            prePixmap: imageList[currentImage(currentIndex)]
            nextPixmap: imageList[currentImage(currentIndex + 1)]
            visible: false

            onRoateAngleChanged: {
                if (roateAngle === 360) {
                    currentIndex++
                    pieImageItem.visible = false
                    rotationImage.visible = true
                    rotationImage.start()
                }
            }
        }
    }

    Text {
        id: titleText
        text: qsTr("回忆录")
        anchors.centerIn: parent
        font.family: "Helvetica"
        font.pointSize: 40
        font.letterSpacing: 10
        wrapMode: Text.WordWrap
        color: "#ff5500"
    }

    Glow {
        id: titleTextGlow
        source: titleText
        anchors.fill: titleText
        radius: 8
        samples: 17
        color: "#aaffff"
    }

    NumberAnimation {
        id: opacityAnimation
        targets: [titleText, titleTextGlow]
        properties: "opacity"
        from: 1.0
        to: 0.0
        duration: 2000
        running: true
        onStopped: {
            rotationImage.visible = true
            rotationImage.start()
        }
    }

    Item {
        id: textureCubeItem
        width: 160
        height: 160
        anchors.top: parent.top
        anchors.left: parent.left
        HLTextureCube {
            id: hlTextureCube
            imageUrl: imageList[currentImage(currentIndex)]
        }
    }

    function currentImage(index) {
        var result = index % imageList.length;
        return result;
    }
}
