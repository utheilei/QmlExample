import QtQuick 2.7
import QtQuick.Controls 2.4
import QtQuick.Layouts 1.0
import QtQuick.Window 2.11
import QtQuick.Controls.Styles 1.4
import QtGraphicalEffects 1.0

ApplicationWindow {
    id: mainwindow
    width: 900
    height: 600
    minimumWidth: 600
    minimumHeight: 400
    visible: true
    flags: Qt.Window | Qt.FramelessWindowHint //去标题栏
    color: "transparent"
    property point startPoint: Qt.point(0, 0);
    property point fixedPont: Qt.point(0, 0);

    Rectangle {
        id: backgroundRectangle
        anchors.fill: parent
        radius: 20
        border.width: 0.5
        border.color: "#EEEEEE"
    }

    MouseArea {
        id: area1
        x: 0
        y: 0
        width: 8
        height: 8
        hoverEnabled: true
        onEntered: cursorShape = Qt.SizeFDiagCursor;
        onExited: cursorShape = Qt.ArrowCursor;
        onPressed: startPoint = Qt.point(mouseX, mouseY);
        onPositionChanged: {
            if(pressed) {
                var offsetX = mouse.x - startPoint.x;
                var offsetY = mouse.y - startPoint.y;
                if ((mainwindow.width - offsetX) >= mainwindow.minimumWidth && offsetX != 0) //如果本次调整小于最小限制，则调整为最小
                {
                    mainwindow.width -= offsetX;
                    mainwindow.x += offsetX;
                }
                if ((mainwindow.height - offsetY) >= mainwindow.minimumHeight && offsetY != 0)
                {
                    mainwindow.height -= offsetY;
                    mainwindow.y += offsetY;
                }
            }
        }
    }

    MouseArea
    {
        id: area2
        x: 8
        y: 0
        width: mainwindow.width - 16
        height: 8
        hoverEnabled: true

        onEntered: cursorShape = Qt.SizeVerCursor;
        onExited: cursorShape = Qt.ArrowCursor;
        onPressed: startPoint = Qt.point(mouseX, mouseY);
        onPositionChanged:
        {
            if(pressed)
            {
                var offsetY = mouse.y - startPoint.y;
                if ((mainwindow.height - offsetY) >= mainwindow.minimumHeight && offsetY != 0)
                {
                    mainwindow.height -= offsetY;
                    mainwindow.y += offsetY;
                }
            }
        }
    }

    MouseArea
    {
        id: area3
        x: mainwindow.width - 8
        y: 0
        width: 8
        height: 8
        hoverEnabled: true

        onEntered: cursorShape = Qt.SizeBDiagCursor;
        onExited: cursorShape = Qt.ArrowCursor
        onPressed:
        {
            startPoint = Qt.point(mouseX, mouseY);
            fixedPont = Qt.point(mainwindow.x, mainwindow.y)
        }
        onPositionChanged:
        {
            if(pressed)
            {
                var offsetX = mouse.x - startPoint.x;
                var offsetY = mouse.y - startPoint.y;
                print (offsetX, offsetY)
                if ((mainwindow.width + offsetX) >= mainwindow.minimumWidth && offsetX != 0)
                {
                    mainwindow.width += offsetX;
                    mainwindow.x = fixedPont.x;
                }
                if ((mainwindow.height - offsetY) >= mainwindow.minimumHeight && offsetY != 0)
                {
                    mainwindow.height -= offsetY;
                    mainwindow.y += offsetY;
                }
            }
        }
    }

    MouseArea
    {
        id: area4
        x: 0
        y: 8
        width: 8
        height: mainwindow.height - 16
        hoverEnabled: true

        onEntered: cursorShape = Qt.SizeHorCursor;
        onExited: cursorShape = Qt.ArrowCursor;
        onPressed: startPoint = Qt.point(mouseX, mouseY);
        onPositionChanged:
        {
            if(pressed)
            {
                var offsetX = mouse.x - startPoint.x;
                if ((mainwindow.width - offsetX) >= mainwindow.minimumWidth)
                {
                    mainwindow.width -= offsetX;
                    mainwindow.x += offsetX;
                }
            }
        }
    }

    MouseArea
    {
        id: area5
        x: 8
        y: 8
        width: mainwindow.width - 16
        height: mainwindow.height - 16
        hoverEnabled: true
        onPressed: startPoint = Qt.point(mouseX, mouseY)
        onPositionChanged: {
            if(pressed) {
                var delta = Qt.point(mouse.x-startPoint.x, mouse.y-startPoint.y)
                mainwindow.setX(mainwindow.x+delta.x)
                mainwindow.setY(mainwindow.y+delta.y)
            }
        }
    }

    MouseArea
    {
        id: area6
        x: mainwindow.width - 8
        y: 8
        width: 8
        height: mainwindow.height - 16
        hoverEnabled: true
        property real fixedX: 0;

        onEntered: cursorShape = Qt.SizeHorCursor;
        onExited: cursorShape = Qt.ArrowCursor;
        onPressed:
        {
            startPoint = Qt.point(mouseX, mouseY);
            fixedPont = Qt.point(mainwindow.x, mainwindow.y)
        }
        onPositionChanged:
        {
            if(pressed)
            {
                var offsetX = mouse.x - startPoint.x;
                if ((mainwindow.width + offsetX) >= mainwindow.minimumWidth && offsetX != 0)
                {
                    mainwindow.width += offsetX;
                    mainwindow.x = fixedPont.x;
                }
            }
        }
    }

    MouseArea
    {
        id: area7
        x: 0
        y: mainwindow.height - 8
        width: 8
        height: mainwindow.height - 16
        hoverEnabled: true
        property real fixedX: 0;

        onEntered: cursorShape = Qt.SizeBDiagCursor;
        onExited: cursorShape = Qt.ArrowCursor;
        onPressed:
        {
            startPoint = Qt.point(mouseX, mouseY);
            fixedPont = Qt.point(mainwindow.x, mainwindow.y)
        }
        onPositionChanged:
        {
            if (pressed)
            {
                var offsetX = mouse.x - startPoint.x;
                var offsetY = mouse.y - startPoint.y;
                if ((mainwindow.width - offsetX) >= mainwindow.minimumWidth && offsetX != 0)
                {
                    mainwindow.width -= offsetX;
                    mainwindow.x += offsetX;
                }
                if ((mainwindow.height + offsetY) >= mainwindow.minimumHeight && offsetY != 0)
                {
                    mainwindow.height += offsetY;
                    mainwindow.y = fixedPont.y;
                }
            }
        }
    }

    MouseArea
    {
        id: area8
        x: 8
        y: mainwindow.height - 8
        width: mainwindow.height - 16
        height: 8
        hoverEnabled: true
        property real fixedX: 0;

        onEntered: cursorShape = Qt.SizeVerCursor;
        onExited: cursorShape = Qt.ArrowCursor;
        onPressed:
        {
            startPoint = Qt.point(mouseX, mouseY);
            fixedPont = Qt.point(mainwindow.x, mainwindow.y)
        }
        onPositionChanged:
        {
            if (pressed)
            {
                var offsetY = mouse.y - startPoint.y;
                if ((mainwindow.height + offsetY) >= mainwindow.minimumHeight && offsetY != 0)
                {
                    mainwindow.height += offsetY;
                    mainwindow.y = fixedPont.y;
                }
            }
        }
    }

    MouseArea
    {
        id: area9
        x: mainwindow.width - 8
        y: mainwindow.height - 8
        width: 8
        height: 8
        hoverEnabled: true

        onEntered: cursorShape = Qt.SizeFDiagCursor;
        onExited: cursorShape = Qt.ArrowCursor
        onPressed:
        {
            startPoint = Qt.point(mouseX, mouseY);
            fixedPont = Qt.point(mainwindow.x, mainwindow.y)
        }
        onPositionChanged:
        {
            if(pressed)
            {
                var offsetX = mouse.x - startPoint.x;
                var offsetY = mouse.y - startPoint.y;
                if ((mainwindow.width + offsetX) >= mainwindow.minimumWidth && offsetX != 0)
                {
                    mainwindow.width += offsetX;
                    mainwindow.x = fixedPont.x;
                }
                if ((mainwindow.height + offsetY) >= mainwindow.minimumHeight && offsetY != 0)
                {
                    mainwindow.height += offsetY;
                    mainwindow.y = fixedPont.y;
                }
            }
        }
    }
}
