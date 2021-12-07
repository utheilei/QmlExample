#include "imageitem.h"

#include <QPainter>
#include <QPainterPath>

ImageItem::ImageItem(QQuickPaintedItem *parent) : QQuickPaintedItem(parent)
{
    setAntialiasing(true);
    connect(this, &ImageItem::widthChanged, [=](){update();});
    connect(this, &ImageItem::heightChanged, [=](){update();});
}

QImage ImageItem::source() const
{
    return m_source;
}

void ImageItem::setSource(const QImage &source)
{
    if (m_source != source) {
        m_source = source;
        update();
        emit sourceChanged();
    }
}

void ImageItem::paint(QPainter *painter)
{
    QRect rect = QRect(QPoint(0, 0), QSize(width(), height()));
    QPainterPath painterPath;
    painterPath.addRect(rect);

    painter->setRenderHints(QPainter::Antialiasing | QPainter::SmoothPixmapTransform);
    painter->setClipPath(painterPath);
    if (!m_source.isNull())
        painter->drawImage(rect, m_source);

    QPen pen;
    pen.setWidth(5);
    pen.setBrush(Qt::green);
    painter->setPen(pen);
    painter->drawRect(rect);
}
