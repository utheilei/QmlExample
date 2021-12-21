#include "blindswidget.h"

#include <QPainter>
#include <QPropertyAnimation>
#include <QDebug>

BlindsWidget::BlindsWidget(QQuickPaintedItem *parent) : QQuickPaintedItem(parent)
{
    m_roateAnimation = new QPropertyAnimation(this, "m_factor");
    m_roateAnimation->setDuration(2000);
    m_roateAnimation->setStartValue(0.0);
    m_roateAnimation->setEndValue(1.0);

    connect(m_roateAnimation, &QPropertyAnimation::valueChanged, this, &BlindsWidget::animationValueChanged);
}

QUrl BlindsWidget::prePixmap()
{
    return m_prePixamp;
}

QUrl BlindsWidget::nextPixmap()
{
    return m_nextPixamp;
}

void BlindsWidget::setPrePixmap(const QUrl &pixmap)
{
    m_prePixamp = pixmap;
    update();
}

void BlindsWidget::setNextPixmap(const QUrl &pixmap)
{
    m_nextPixamp = pixmap;
    update();
}

Qt::Orientation BlindsWidget::orientation()
{
    return m_orientation;
}

void BlindsWidget::setOrientation(Qt::Orientation orientation)
{
    m_orientation = orientation;
}

void BlindsWidget::setFactor(qreal factor)
{
    m_factor = factor;
}

qreal BlindsWidget::factor()
{
    return m_factor;
}

void BlindsWidget::start()
{
    if (m_roateAnimation->state() == QAbstractAnimation::Stopped)
        m_roateAnimation->start();
}

void BlindsWidget::stop()
{
    if (m_roateAnimation->state() == QAbstractAnimation::Running)
        m_roateAnimation->stop();
}

QString BlindsWidget::toLocalFileName(QUrl &name)
{
    QString fileName = name.toString();
    if (fileName.left(4) == "file")
        fileName = name.toLocalFile();
    else if (fileName.left(3) == "qrc")
        fileName = fileName.mid(3);

    return fileName;
}

void BlindsWidget::paint(QPainter *painter)
{
    QPixmap prePixamp = QPixmap(toLocalFileName(m_prePixamp));
    QPixmap nextPixamp = QPixmap(toLocalFileName(m_nextPixamp));

    if (prePixamp.isNull() || nextPixamp.isNull())
        return;

    if (prePixamp.width() != width() || prePixamp.height() != height())
        prePixamp = scalePixmap(prePixamp, width(), height());

    if (nextPixamp.width() != width() || nextPixamp.height() != height())
        nextPixamp = scalePixmap(nextPixamp, width(), height());

    painter->setRenderHints(QPainter::Antialiasing | QPainter::SmoothPixmapTransform);

    int i, n, w, h, x1, y1, x2, y2, dh, ddh;

    w = width();
    h = height();
    x1 = (w - prePixamp.width()) / 2;
    y1 = (h - prePixamp.height()) / 2;
    x2 = (w - nextPixamp.width()) / 2;
    y2 = (h - nextPixamp.height()) / 2;

    painter->drawPixmap(x1, y1, prePixamp);

    n = 10;

    if (Qt::Vertical == m_orientation) {
        dh = nextPixamp.height() / n;
        ddh = m_factor * dh;

        if (ddh < 1)
            return;

        for(i = 0; i < n; i++)
            painter->drawPixmap(x2, y2 + i * dh, nextPixamp, 0, i * dh, nextPixamp.width(), ddh);
    } else {
        dh = nextPixamp.width() / n;
        ddh = m_factor * dh;

        if (ddh < 1)
            return;

        for(i = 0; i < n; i++)
            painter->drawPixmap(x2 + i * dh, y2, nextPixamp, i * dh, 0, ddh, nextPixamp.height());
    }
}

QPixmap BlindsWidget::scalePixmap(const QPixmap &pixmap, int nMaxWidth, int nMaxHeight)
{
    return pixmap.scaled(nMaxWidth, nMaxHeight,
                         Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
}

void BlindsWidget::animationValueChanged(const QVariant &value)
{
    Q_UNUSED(value);

    emit factorChanged(value.toDouble());
    update();
}
