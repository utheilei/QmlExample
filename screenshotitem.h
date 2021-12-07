#ifndef SCREENSHOTITEM_H
#define SCREENSHOTITEM_H

#include "imageitem.h"

#include <QQuickImageProvider>
#include <QQuickWindow>

class ViewProvider;
class ScreenShotItem : public QQuickWindow
{
    Q_OBJECT
    Q_ENUMS(SaveType)
public:
    enum SaveType {
        AutoSave,
        DownloadSave
    };

    explicit ScreenShotItem(QQuickWindow *parent = nullptr);
    ~ScreenShotItem() Q_DECL_OVERRIDE;

    Q_INVOKABLE void saveScreenShotImage(int type, const QString &fileName = QString());

    bool saveImage(QString &savePath, const QString &fileName = QString());

    QQuickImageProvider *providerView() const;

protected:
    void mousePressEvent(QMouseEvent *event) Q_DECL_OVERRIDE;
    void mouseReleaseEvent(QMouseEvent *event) Q_DECL_OVERRIDE;
    void mouseMoveEvent(QMouseEvent *event) Q_DECL_OVERRIDE;
    void showEvent(QShowEvent *event) Q_DECL_OVERRIDE;
    void hideEvent(QHideEvent *event) Q_DECL_OVERRIDE;

private:
    bool saveSvgImage(const QString &fileName, const QImage &image);
    ImageItem *imageItem() const;
    QPoint topLeft(const QPoint &clickedPoint , const QPoint &delta) const;
    void setImageItem(const QPoint &topLeftPoint , const QPoint &delta);
    QString defalutPath() const;

signals:
    void saveFinished(const QVariant &saveResult);

public slots:

private:
    QPoint m_clickedPoint;
    QPoint m_releasePoint;
    bool isClicked = false;
    bool isFinished = false;
    ViewProvider *m_viewProvider = Q_NULLPTR;
    QImage originalImage;
};

#endif // SCREENSHOTITEM_H
