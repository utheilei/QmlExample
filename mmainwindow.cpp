#include "mmainwindow.h"

#include <QMouseEvent>
#include <QDebug>
#include <QApplication>
#include <QDesktopWidget>

constexpr int padding = 10;

MMainWindow::MMainWindow(QWindow *parent) : QQuickWindow(parent)
{
    setFlags(flags() | Qt::Window | Qt::FramelessWindowHint);

    connect(this, &MMainWindow::activeChanged, [=](){
        emit windowActiveChanged(isActive());
    });
}

MMainWindow::~MMainWindow()
{

}

bool MMainWindow::windowActived()
{
    return isActive();
}

int MMainWindow::setCursorStyle(const QPoint &curPoint)
{
    if (!m_isResized)
        return CursorNormal;

    int nCurWidth = this->width();
    int nCurHeight = this->height();
    int nRes = CursorNormal;

    if ((nCurWidth - curPoint.x() <= padding) && (nCurHeight - curPoint.y() <= padding)) {
        setCursor(Qt::SizeFDiagCursor);
        nRes = CursorBottomRight;
    } else if (curPoint.x() <= padding && curPoint.y() <= padding) {
        setCursor(Qt::SizeFDiagCursor);
        nRes = CursorTopLeft;
    } else if (curPoint.x() <= padding && (nCurHeight - curPoint.y() <= padding)) {
        setCursor(Qt::SizeBDiagCursor);
        nRes = CursorBottomLeft;
    } else if ((nCurWidth - curPoint.x() <= padding) && curPoint.y() <= padding) {
        setCursor(Qt::SizeBDiagCursor);
        nRes = CursorTopRight;
    } else if (nCurWidth - curPoint.x() <= padding) {
        setCursor(Qt::SizeHorCursor);
        nRes = CursorRight;
    } else if (nCurHeight - curPoint.y() <= padding) {
        setCursor(Qt::SizeVerCursor);
        nRes = CursorBottom;
    } else if (curPoint.x() <= 3) {
        setCursor(Qt::SizeHorCursor);
        nRes = CursorLeft;
    } else if (curPoint.y() <= 3) {
        setCursor(Qt::SizeVerCursor);
        nRes = CursorTop;
    } else {
        setCursor(Qt::ArrowCursor);
        nRes = CursorNormal;
    }

    return nRes;
}

int MMainWindow::titleBarHeight() const
{
    return m_titleBarHeight;
}

void MMainWindow::setTitleBarHeight(int height)
{
    if (m_titleBarHeight != height) {
        m_titleBarHeight = height;
        emit titleBarHeightChanged();
    }
}

bool MMainWindow::resized() const
{
    return m_isResized;
}

void MMainWindow::setResized(bool isResized)
{
    m_isResized = isResized;
}

void MMainWindow::mousePressEvent(QMouseEvent *event)
{
    if(event->button() == Qt::LeftButton) {
        m_MousePressPos = event->pos();
        m_bMousePressed = true;
    }

    if (CursorNormal != m_nMouseResize)
        m_bMouseResizePressed = true;

    QQuickWindow::mousePressEvent(event);
}

void MMainWindow::mouseReleaseEvent(QMouseEvent *event)
{
    if(event->button() == Qt::LeftButton) {
        m_bMousePressed = false;
        m_bMouseResizePressed = false;
        m_nMouseResize = setCursorStyle(event->pos());
    }

    QQuickWindow::mouseReleaseEvent(event);
}

void MMainWindow::mouseMoveEvent(QMouseEvent *event)
{
    if(Qt::WindowMaximized == windowState())
        return;

    if (!m_bMouseResizePressed)
        m_nMouseResize = setCursorStyle(event->pos());

    if (m_bMousePressed && (event->buttons() == Qt::LeftButton)) {
        QPoint movePoint = event->pos() - m_MousePressPos;
        if (!m_bMouseResizePressed) {
            if (m_titleBarHeight > 0) {
                QRect titleBarRect = QRect(QPoint(0, 0), QSize(width(), m_titleBarHeight));
                if (titleBarRect.contains(event->pos()))
                    this->setPosition(this->position() + movePoint);
            } else {
                this->setPosition(this->position() + movePoint);
            }
        } else {
            if (m_isResized) {
                QRect rect = geometry();

                switch (m_nMouseResize) {
                case CursorTopLeft:
                    rect.setTopLeft(rect.topLeft() + movePoint);
                    break;
                case CursorTop:
                    rect.setTop(rect.top() + movePoint.y());
                    break;
                case CursorTopRight:
                    rect.setTopRight(rect.topRight() + movePoint);
                    break;
                case CursorLeft:
                    rect.setLeft(rect.left() + movePoint.x());
                    break;
                case CursorBottomLeft:
                    rect.setBottomLeft(rect.bottomLeft() + movePoint);
                    break;
                case CursorBottom:
                    rect.setBottom(rect.bottom() + movePoint.y());
                    break;
                case CursorBottomRight:
                    rect.setBottomRight(rect.bottomRight() + movePoint);
                    break;
                case CursorRight:
                    rect.setRight(rect.right() + movePoint.x());
                    break;
                default:
                    break;
                }

                if(rect.width() <= minimumWidth() || rect.height() <= minimumHeight())
                    return;

                setGeometry(rect);
            }

            m_MousePressPos = event->pos();
        }
    }

    QQuickWindow::mouseMoveEvent(event);
}
