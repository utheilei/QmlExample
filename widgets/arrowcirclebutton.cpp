/*
* Copyright (C) 2020 ~ 2025 Uniontech Software Technology Co.,Ltd.
*
* Author:     helei <helei@uniontech.com>
*
* Maintainer: helei <helei@uniontech.com>
*
* This program is free software: you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation, either version 3 of the License, or
* any later version.
*
* This program is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
* GNU General Public License for more details.
*
* You should have received a copy of the GNU General Public License
* along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include "arrowcirclebutton.h"

#include <QPainter>
#include <QPainterPath>

ArrowCircleButton::ArrowCircleButton(QQuickPaintedItem *parent)
    : QQuickPaintedItem(parent)
{
    setAcceptHoverEvents(true);
    setAcceptedMouseButtons(Qt::MouseButton::LeftButton);
    setAntialiasing(true);
}

QString ArrowCircleButton::source() const
{
    return m_source;
}

void ArrowCircleButton::setSource(const QString &source)
{
    if (m_source != source) {
        m_source = source;
        update();
        emit sourceChanged();
    }
}

void ArrowCircleButton::setChecked(bool isChecked)
{
    if (m_checked != isChecked) {
        m_checked = isChecked;
        emit checkedChanged(m_checked);
        update();
    }
}

QString ArrowCircleButton::toLocalFileName(QString &name)
{
    if (name.left(4) == "file")
        name = QUrl(name).toLocalFile();
    else if (name.left(3) == "qrc")
        name = name.mid(3);

    return name;
}

void ArrowCircleButton::mousePressEvent(QMouseEvent *e)
{
    QRectF rect = QRectF(0, 0, width(), height());

    if (rect.contains(e->pos())) {
        setChecked(!m_checked);
        update();
    }

    QQuickPaintedItem::mousePressEvent(e);
}

void ArrowCircleButton::paint(QPainter *painter)
{
    QRect rect = QRect(0, 0, width(), height());
    QPainterPath painterPath;
    painterPath.addEllipse(rect);

    painter->setRenderHints(QPainter::Antialiasing | QPainter::TextAntialiasing);
    painter->setClipPath(painterPath);
    painter->drawPixmap(rect, QPixmap(toLocalFileName(m_source)));

    //??????????????????????????????
    if (m_hover) {
        painter->setPen(Qt::NoPen);
        //??????
        int w = rect.width();
        int h = rect.height();
        //??????
        QRect rect(0, h - h / 4, w, h - h / 4);
        // ?????????
        painter->setRenderHint(QPainter::Antialiasing, true);
        // ???????????????
        QLinearGradient linear(QPoint(0, h - h / 4), QPoint(0, h));
        linear.setColorAt(0, QColor(0, 0, 0, 0.00 * 255));
        linear.setColorAt(1, QColor(0, 0, 0, 0.50 * 255));

        // ??????????????????
        linear.setSpread(QGradient::PadSpread);
        painter->setBrush(linear);
        painter->drawRect(rect);
    }

    if (!m_checked) {
        QPen pen(Qt::transparent);
        pen.setWidth(2);
        pen.setColor(Qt::white);
        painter->setPen(pen);
        //?????????????????????10???
        int portion = rect.width() / 10;
        //??????????????????
        QPoint cpt = rect.center();
        //??????????????????
        painter->drawLine(QPoint(cpt.x() - portion / 2, cpt.y() + portion * 4 - portion / 2),
                         QPoint(cpt.x(), cpt.y() + portion * 4));
        //??????????????????
        painter->drawLine(QPoint(cpt.x() + portion / 2, cpt.y() + portion * 4 - portion / 2),
                         QPoint(cpt.x(), cpt.y() + portion * 4));
    } else {
        QPen pen(Qt::transparent);
        pen.setWidth(2);
        pen.setColor(Qt::white);
        painter->setPen(pen);
        //?????????????????????10???
        int portion = rect.width() / 10;
        //??????????????????
        QPoint cpt = rect.center();
        //??????????????????
        painter->drawLine(QPoint(cpt.x() - portion / 2, cpt.y() + portion * 4),
                         QPoint(cpt.x(), cpt.y() + portion * 4 - portion / 2));
        //??????????????????
        painter->drawLine(QPoint(cpt.x() + portion / 2, cpt.y() + portion * 4),
                         QPoint(cpt.x(), cpt.y() + portion * 4 - portion / 2));
    }
}

void ArrowCircleButton::hoverEnterEvent(QHoverEvent *event)
{
    m_hover = true;
    update();
    emit hoverChanged(m_hover);

    QQuickPaintedItem::hoverEnterEvent(event);
}

void ArrowCircleButton::hoverLeaveEvent(QHoverEvent *event)
{
    m_hover = false;
    update();
    emit hoverChanged(m_hover);

    QQuickPaintedItem::hoverLeaveEvent(event);
}
