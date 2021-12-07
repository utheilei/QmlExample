#include "screenshotitem.h"
#include "core/viewprovider.h"

#include <QApplication>
#include <QMouseEvent>
#include <QQuickItem>
#include <QScreen>
#include <QUuid>
#include <QFileInfo>
#include <QSvgGenerator>
#include <QPainter>

const QString fileFormat = "png";

ScreenShotItem::ScreenShotItem(QQuickWindow *parent) : QQuickWindow(parent)
{
    setFlags(flags() | Qt::Window | Qt::FramelessWindowHint);
    setWindowState(Qt::WindowState::WindowFullScreen);
    m_viewProvider = new ViewProvider;
}

ScreenShotItem::~ScreenShotItem()
{
//    if (m_viewProvider)     delete会导致程序崩溃，程序退出会自动释放ViewProvider
//        delete m_viewProvider;
}

void ScreenShotItem::saveScreenShotImage(int type, const QString &fileName)
{
    QString savePath;
    bool isSaved = saveImage(savePath, fileName);
    QString message = savePath + (isSaved ? tr(" Save success.") : tr(" Save fail."));
    QFileInfo info(savePath);
    close();
    emit saveFinished(QVariantList() << isSaved << message <<
                      type << QUrl::fromLocalFile(info.absoluteFilePath()));
}

bool ScreenShotItem::saveImage(QString &savePath, const QString &fileName)
{
    QImage image = imageItem()->source();
    if (image.isNull())
        return false;

    savePath = fileName.isEmpty() ? defalutPath() : QUrl(fileName).toLocalFile();

    if (savePath.contains("svg"))
        return saveSvgImage(savePath, image);
    else
        return image.save(savePath);
}

bool ScreenShotItem::saveSvgImage(const QString &fileName, const QImage &image)
{
    if (image.isNull())
        return false;

    QSvgGenerator generator;
    generator.setFileName(fileName);
    generator.setSize(QSize(image.width(), image.height()));
    generator.setViewBox(QRect(0, 0, image.width(), image.height()));
    generator.setTitle(tr("SVG Generator With Drawing"));
    generator.setDescription(tr("SVG Generator with Qt."));

    QPainter painter;
    painter.begin(&generator);
    painter.drawImage(QPoint(0, 0), image);
    painter.end();

    return true;
}

QQuickImageProvider *ScreenShotItem::providerView() const
{
    return m_viewProvider;
}

void ScreenShotItem::mousePressEvent(QMouseEvent *event)
{
    if (isFinished) {
        QQuickWindow::mousePressEvent(event);
    } else {
        if (event->button() == Qt::MouseButton::LeftButton) {
            m_clickedPoint = event->pos();
            isClicked = true;
            setImageItem(m_clickedPoint, QPoint(0, 0));
        }
    }

    if (event->button() == Qt::MouseButton::RightButton)
        close();
}

void ScreenShotItem::mouseMoveEvent(QMouseEvent *event)
{
    if (isClicked) {
        isFinished = false;
        QPoint delta = event->pos() - m_clickedPoint;
        QRect rect = QRect(topLeft(m_clickedPoint, delta), QSize(qAbs(delta.x()), qAbs(delta.y())));
        QImage pixmap = originalImage.copy(rect);
        imageItem()->setSource(pixmap);
        setImageItem(topLeft(m_clickedPoint, delta), delta);
    }
}

void ScreenShotItem::showEvent(QShowEvent *event)
{
    QScreen *screen = QApplication::primaryScreen();
    QPixmap pixmap = screen->grabWindow(0);
    m_viewProvider->updateView(pixmap.toImage());
    originalImage = pixmap.toImage();
    QMetaObject::invokeMethod(this, "setBackgroudImage");

    QQuickWindow::showEvent(event);
}

void ScreenShotItem::hideEvent(QHideEvent *event)
{
    QMetaObject::invokeMethod(this, "showToolBar", Q_ARG(QVariant, false));
    setImageItem(m_releasePoint, QPoint(0, 0));
    isClicked = false;
    isFinished = false;

    QQuickWindow::hideEvent(event);
}

ImageItem *ScreenShotItem::imageItem() const
{
    auto item = findChild<QQuickItem *>("screenShotImage");
    return qobject_cast<ImageItem *>(item);
}

QPoint ScreenShotItem::topLeft(const QPoint &clickedPoint, const QPoint &delta) const
{
    if (delta.x() > 0 && delta.y() >= 0)
        return clickedPoint;

    if (delta.x() > 0 && delta.y() < 0)
        return QPoint(clickedPoint.x(), clickedPoint.y() + delta.y());

    if (delta.x() < 0 && delta.y() > 0)
        return QPoint(clickedPoint.x() + delta.x(), clickedPoint.y());

    if (delta.x() < 0 && delta.y() < 0)
        return QPoint(clickedPoint.x() + delta.x(), clickedPoint.y() + delta.y());

    return QPoint(0, 0);
}

void ScreenShotItem::setImageItem(const QPoint &topLeftPoint, const QPoint &delta)
{
    if (imageItem() != Q_NULLPTR) {
        imageItem()->setPosition(topLeftPoint);
        imageItem()->setWidth(qAbs(delta.x()));
        imageItem()->setHeight(qAbs(delta.y()));
    }
}

QString ScreenShotItem::defalutPath() const
{
    QString fileName = QUuid::createUuid().toString().remove("-");
    fileName = fileName.mid(1, fileName.length()-2);
    fileName = fileName + QString(".%1").arg(fileFormat);
    return fileName;
}

void ScreenShotItem::mouseReleaseEvent(QMouseEvent *event)
{
    isClicked = false;
    m_releasePoint = event->pos();
    if (imageItem()->width() > 0 && imageItem()->height() > 0) {
        isFinished = true;
        QMetaObject::invokeMethod(this, "showToolBar", Q_ARG(QVariant, true));
    }

    QQuickWindow::mouseReleaseEvent(event);
}
