import QtQuick 2.7
import QtQuick.Controls 2.4
import QtQuick.Layouts 1.0
import QtQuick.Window 2.11
import QtQuick.Controls.Styles 1.4
import an.window 1.0
import Qt.labs.platform 1.0
import "./controlcenter"
import "./controls"

MMainWindow {
    id: root
    visible: true
    width: 1010
    height: 670
    resized: false
    minimumWidth: 480
    minimumHeight: 320
    titleBarHeight: titleBar.height
    color: "transparent"
    x: Screen.width/2 - width/2
    y: Screen.height/2 - height/2
    title: qsTr("控制中心")

    property int itemWidth: 170
    property int count: Math.floor(root.width/190)

    onWindowActiveChanged: sPalette.colorGroup = isActive ? SystemPalette.Active : SystemPalette.Inactive

    SystemPalette {
        id: sPalette
        colorGroup: SystemPalette.Active
    }

    Rectangle {
        anchors.fill: parent
        color: "#F8F8F8"
        radius: 20
        border.width: 1
        border.color: sPalette.button
        clip: true
    }

    HLTitleBar {
        id: titleBar
        x: parent.x
        y: parent.y
        width: parent.width
        height: 50
    }

    Menu {
        id: barMenu
        MenuItem {text: "帮助";}
        Menu {
            title: "主题"
            MenuItem { text: "浅色"; checkable: true; checked: true}
            MenuItem { text: "深色" }
            MenuItem { text: "跟随主题" }
        }
        MenuSeparator {}
        MenuItem { text: "关于" }
        MenuItem { text: "退出"; onTriggered: Qt.quit()}
    }

    Loader {
        id:myLoader
        anchors.top: titleBar.bottom
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.bottom: parent.bottom
        sourceComponent: loginPage
    }

    Component {
        id: loginPage
        ScrollView {
            id: scrollView
            topPadding: 20
            clip: true
            Grid {
                anchors.centerIn: parent
                leftPadding: (root.width - count*itemWidth - (count-1)*20)/2
                rightPadding: (root.width - count*itemWidth - (count-1)*20)/2
                rowSpacing: 20
                columnSpacing: 20
                columns: count

                Repeater {
                    model: qmlHelper.listModel()
                    IconItem {
                        width: itemWidth
                        height: itemWidth
                        icon: modelData[1]
                        label: modelData[0]

                        onItemClicked: {
                            myLoader.sourceComponent = mainPage
                            myLoader.item.setCurrentItem(index)
                        }
                    }
                }
            }
        }
    }

    Component {
        id: mainPage
        QmlMainWidget {
            id: qmlMainWidget
            clip: true
        }
    }

    HLFloatingMessage {
        id: floatingMessage
        x: (parent.width - floatingMessage.width)/2
        y: (parent.height - floatingMessage.height) - 30
        maxWidth: parent.width/3*2
    }

    Connections {
        target: screenShotWindow
        onSaveFinished: {
            if (saveResult[1] !== "")
                showFloatingMessage(saveResult[0], saveResult[1], 5000)
        }
    }

    function showFloatingMessage(isOk, text, time) {
        if (floatingMessage.visible)
            return

        floatingMessage.iconSource = isOk ? "qrc:/icon/yes.svg" : "qrc:/icon/error.svg"
        floatingMessage.text = text
        floatingMessage.timeout = time
        floatingMessage.visible = true
    }
}


//ApplicationWindow {
//    id: mainWindow
//    visible: true
//    width: 900
//    height: 600
//    minimumWidth: 600
//    minimumHeight: 400
//    title: qsTr("Hello World")
//    flags: Qt.Window | Qt.FramelessWindowHint //去标题栏
//    color: "transparent"

//    property int cursorCtrlStyle: 0
//    property rect geometry: Qt.rect(mainWindow.x, mainWindow.y, mainWindow.width, mainWindow.height)
//    property rect mainWindowTopLeft: Qt.rect(backgroundMouseArea.x - 10, backgroundMouseArea.y - 10, 20, 20)
//    property rect mainWindowTop: Qt.rect(backgroundMouseArea.x + 10, backgroundMouseArea.y - 10, backgroundMouseArea.width - 20, 20)
//    property rect mainWindowTopRight: Qt.rect(backgroundMouseArea.x + backgroundMouseArea.width-10, backgroundMouseArea.y - 10, 20, 20)
//    property rect mainWindowLeft: Qt.rect(mainWindowTopLeft.x, backgroundMouseArea.y + 10, 20, backgroundMouseArea.height - 20)
//    property rect mainWindowRight: Qt.rect(mainWindowTopRight.x, backgroundMouseArea.y + 10, 20, backgroundMouseArea.height - 20)
//    property rect mainWindowBottomLeft: Qt.rect(mainWindowTopLeft.x, backgroundMouseArea.y + backgroundMouseArea.height - 10, 20, 20)
//    property rect mainWindowBottom: Qt.rect(backgroundMouseArea.x + 10, mainWindowBottomLeft.y, mainWindowTop.width, 20)
//    property rect mainWindowBottomRight: Qt.rect(mainWindowTopRight.x, mainWindowBottomLeft.y, 20, 20)

//    background: Rectangle {
//        id: backgroundRectangle
//        anchors.fill: parent
//        color: "#EEEEEE"
//        radius: 10
//        border.width: 0

//        ParallelAnimation {
//            running: true
//            SpringAnimation { target: backgroundRectangle; property: "width"; duration: 1000 }
//            SpringAnimation { target: backgroundRectangle; property: "height"; duration: 1000 }
//        }
//    }

//    MouseArea {
//        id: backgroundMouseArea
//        anchors.fill: parent
//        hoverEnabled: true
//        cursorShape: Qt.ArrowCursor
//        acceptedButtons: Qt.LeftButton //只处理鼠标左键
//        property point clickPos: "0, 0"
//        property point movePos: "0, 0"
//        property bool isClicked: false
//        property bool isResize: false
//        onPressed: { //接收鼠标按下事件
//            clickPos = Qt.point(mouse.x,mouse.y)
//            isClicked = true
//            if (cursorCtrlStyle !== 0) {
//                isResize = true
//                geometry = Qt.rect(mainWindow.x, mainWindow.y, mainWindow.width, mainWindow.height)
//            }
//        }
//        onReleased: {
//            isClicked = false
//            isResize = false
//            setMouseCursorShape(Qt.point(mouse.x,mouse.y))
//        }
//        onPositionChanged: { //鼠标按下后改变位置
//            if (!isClicked) {
//                setMouseCursorShape(Qt.point(mouse.x,mouse.y))
//            }

//            if (isClicked) {
//                var delta = Qt.point(mouse.x-clickPos.x, mouse.y-clickPos.y)

//                if (!isResize) {
//                    mainWindow.setX(mainWindow.x+delta.x)
//                    mainWindow.setY(mainWindow.y+delta.y)
//                } else {
//                    geometry = Qt.rect(mainWindow.x, mainWindow.y, mainWindow.width, mainWindow.height)
//                    clickPos = Qt.point(clickPos.x + delta.x, clickPos.y + delta.y)
////                    if (geometry.width <= mainWindow.minimumWidth || geometry.height <= mainWindow.minimumHeight)
////                        return
//                    var rect = qmlHelper.changeGeometry(geometry, delta, cursorCtrlStyle)
//                    console.info(rect)
//                    mainWindow.setGeometry(rect)
//                }
//            }
//        }

//        function setMouseCursorShape(pos) {
//            if (qmlHelper.contains(mainWindowTopLeft, pos)) {
//                cursorCtrlStyle = 1
//                cursorShape = Qt.SizeFDiagCursor
//            }
//            else if (qmlHelper.contains(mainWindowBottomRight, pos)) {
//                cursorCtrlStyle = 7
//                cursorShape = Qt.SizeFDiagCursor
//            }
//            else if (qmlHelper.contains(mainWindowTopRight, pos)) {
//                cursorCtrlStyle = 3
//                cursorShape = Qt.SizeBDiagCursor
//            }
//            else if (qmlHelper.contains(mainWindowBottomLeft, pos)) {
//                cursorCtrlStyle = 5
//                cursorShape = Qt.SizeBDiagCursor
//            }
//            else if (qmlHelper.contains(mainWindowLeft, pos)) {
//                cursorCtrlStyle = 4
//                cursorShape = Qt.SizeHorCursor
//            }
//            else if (qmlHelper.contains(mainWindowRight, pos)) {
//                cursorCtrlStyle = 8
//                cursorShape = Qt.SizeHorCursor
//            }
//            else if (qmlHelper.contains(mainWindowTop, pos)) {
//                cursorCtrlStyle = 2
//                cursorShape = Qt.SizeVerCursor
//            }
//            else if (qmlHelper.contains(mainWindowBottom, pos)) {
//                cursorCtrlStyle = 6
//                cursorShape = Qt.SizeVerCursor
//            }
//            else {
//                cursorCtrlStyle = 0
//                cursorShape = Qt.ArrowCursor
//            }
//        }
//    }
//}
