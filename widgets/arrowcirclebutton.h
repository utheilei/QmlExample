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

#ifndef ARROWCIRCLEBUTTON_H
#define ARROWCIRCLEBUTTON_H

#include <QQuickPaintedItem>

class ArrowCircleButton : public QQuickPaintedItem
{
    Q_OBJECT

    Q_PROPERTY(bool checked READ checked WRITE setChecked NOTIFY checkedChanged)
    Q_PROPERTY(QString source READ source WRITE setSource NOTIFY sourceChanged)
    Q_PROPERTY(READ hoverd NOTIFY hoverChanged)

public:
    explicit ArrowCircleButton(QQuickPaintedItem *parent = Q_NULLPTR);

    QString source() const;

    void setSource(const QString &source);

    void setChecked(bool isChecked);

    bool checked() const { return m_checked; }

private:
    QString toLocalFileName(QString &name);

Q_SIGNALS:
    void checkedChanged(bool isChecked);
    void hoverChanged(bool isHover);
    void sourceChanged();

protected:
    void mousePressEvent(QMouseEvent *event) Q_DECL_OVERRIDE;
    void paint(QPainter *painter) Q_DECL_OVERRIDE;
    void hoverEnterEvent(QHoverEvent *event) Q_DECL_OVERRIDE;
    void hoverLeaveEvent(QHoverEvent *event) Q_DECL_OVERRIDE;

private:
    bool m_hover = false;
    bool m_checked = false;

    QString m_source;
};

#endif // ARROWCIRCLEBUTTON_H
