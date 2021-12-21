#include "pieimagedisplay.h"

#include <QPainter>
#include <QVariantAnimation>
#include <QDebug>
#include <QtMath>

#define ROTATE_ANGLE 360

PieImageWidget::PieImageWidget(QQuickPaintedItem *parent) : QQuickPaintedItem(parent)
{
    m_roateAnimation = new QVariantAnimation(this);
    m_roateAnimation->setDuration(2000);
    m_roateAnimation->setStartValue(0);
    m_roateAnimation->setEndValue(ROTATE_ANGLE);

    connect(m_roateAnimation, &QVariantAnimation::valueChanged,
            this, &PieImageWidget::animationValueChanged);
}

QUrl PieImageWidget::prePixmap()
{
    return m_prePixamp;
}

QUrl PieImageWidget::nextPixmap()
{
    return m_nextPixamp;
}

void PieImageWidget::setPrePixmap(const QUrl &pixmap)
{
    m_prePixamp = pixmap;
    update();
}

void PieImageWidget::setNextPixmap(const QUrl &pixmap)
{
    m_nextPixamp = pixmap;
    update();
}

int PieImageWidget::roateAngle()
{
    return m_roateAngle;
}

void PieImageWidget::setRoateAngle(int roateAngle)
{
    m_roateAngle = roateAngle;
    update();
}

QPixmap PieImageWidget::scalePixmap(const QPixmap& pixmap,int nMaxWidth,int nMaxHeight)
{
    return pixmap.scaled(nMaxWidth, nMaxHeight,
                             Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
}

void PieImageWidget::start()
{
    if (m_roateAnimation->state() != QAbstractAnimation::Running) {
        isFinished = false;
        m_roateAnimation->start();
    }
}

void PieImageWidget::stop()
{
    if (m_roateAnimation->state() == QAbstractAnimation::Running) {
        m_roateAnimation->stop();
        isFinished = true;
    }
}

void PieImageWidget::pause()
{
    if (m_roateAnimation->state() == QAbstractAnimation::Running)
        m_roateAnimation->pause();
}

bool PieImageWidget::isRuning()
{
    return (m_roateAnimation->state() == QAbstractAnimation::Running);
}

QString PieImageWidget::toLocalFileName(QUrl &name)
{
    QString fileName = name.toString();
    if (fileName.left(4) == "file")
        fileName = name.toLocalFile();
    else if (fileName.left(3) == "qrc")
        fileName = fileName.mid(3);

    return fileName;
}

void PieImageWidget::paint(QPainter *painter)
{
    QPixmap pixmap = QPixmap(toLocalFileName(m_prePixamp));
    QPixmap nextPixamp = QPixmap(toLocalFileName(m_nextPixamp));
    QRect rect = QRect(0, 0, width(), height());

    if (pixmap.width() != width() || pixmap.height() != height())
        pixmap = scalePixmap(pixmap, width(), height());

    painter->setRenderHints(QPainter::Antialiasing | QPainter::SmoothPixmapTransform);
    painter->setClipping(true);
    QPainterPath canDrawingPathArea;
    canDrawingPathArea.addRect(rect);
    int rectWidth = qSqrt(width()*width() + height()*height());
    QRect fillRect((rect.center().x() - rectWidth/2), (rect.center().y() - rectWidth/2), rectWidth, rectWidth);
    canDrawingPathArea.moveTo(rect.center());
    canDrawingPathArea.arcTo(fillRect, 0, m_roateAngle);
    painter->setBrush(QBrush(pixmap));
    painter->setPen(Qt::NoPen);
    painter->drawPixmap(rect, nextPixamp);
    if (!isFinished)
        painter->drawPath(canDrawingPathArea);
}

void PieImageWidget::animationValueChanged(const QVariant &value)
{
    m_roateAngle = value.toInt();
    emit roateAngleChanged(m_roateAngle);
    if (ROTATE_ANGLE == value.toInt()) {
        m_roateAngle = 0;
        isFinished = true;
        emit animationFinished();
    }

    update();
}
