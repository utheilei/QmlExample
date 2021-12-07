#ifndef MMAINWINDOW_H
#define MMAINWINDOW_H

#include <QQuickWindow>

class MMainWindow : public QQuickWindow
{
    Q_OBJECT
    Q_PROPERTY(bool windowActive READ windowActived NOTIFY windowActiveChanged)
    Q_PROPERTY(int titleBarHeight READ titleBarHeight WRITE setTitleBarHeight NOTIFY titleBarHeightChanged)
    Q_PROPERTY(bool resized READ resized WRITE setResized)

public:
    explicit MMainWindow(QWindow *parent = nullptr);
    ~MMainWindow() Q_DECL_OVERRIDE;

    enum tagCursorCtrlStyle
    {
        CursorNormal = 0,    // 普通鼠标
        CursorTopLeft,
        CursorTop,
        CursorTopRight,
        CursorLeft,
        CursorBottomLeft,
        CursorBottom,
        CursorBottomRight,
        CursorRight
    };

    int setCursorStyle(const QPoint& curPoint);    // 当前位置设置鼠标样式

    int titleBarHeight() const;
    void setTitleBarHeight(int height);

    bool resized() const;
    void setResized(bool isResized);

    Q_INVOKABLE bool windowActived();

protected:
    void mousePressEvent(QMouseEvent *event) Q_DECL_OVERRIDE;
    void mouseReleaseEvent(QMouseEvent *event) Q_DECL_OVERRIDE;
    void mouseMoveEvent(QMouseEvent *event) Q_DECL_OVERRIDE;

signals:
    void windowActiveChanged(bool isActive);
    void titleBarHeightChanged();

public slots:

private:
    QPoint m_MousePressPos;                 // 鼠标点击位置
    bool m_bMousePressed = false;         // 鼠标是否按下
    int m_nMouseResize;                  // 鼠标设置大小
    bool m_bMouseResizePressed = false;   // 设置大小的按下
    int m_titleBarHeight = 0;
    bool m_isResized = true;
};

#endif // MMAINWINDOW_H
