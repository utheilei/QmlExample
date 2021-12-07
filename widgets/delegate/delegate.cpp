#include "delegate.h"

#include <QPainter>
#include <QApplication>
#include <QDebug>
#include <QPainterPath>

QuickItemDelegate::QuickItemDelegate(QQuickPaintedItem *parent) : QQuickPaintedItem(parent)
{
    setAcceptedMouseButtons(Qt::MouseButton::LeftButton);
}

QString QuickItemDelegate::source() const
{
    return m_source;
}

void QuickItemDelegate::setSource(QString source)
{
    if (m_source != source) {
        m_source = source;
        emit sourceChanged();
        update();
    }
}

Qt::CheckState QuickItemDelegate::checked() const
{
    return m_checked;
}

void QuickItemDelegate::setChecked(Qt::CheckState status)
{
    if (m_checked != status) {
        m_checked = status;
        emit checkedChanged();
        update();
    }
}

int QuickItemDelegate::mouseStatus() const
{
    return m_mouseStatus;
}

QString QuickItemDelegate::toLocalFileName(QString &name)
{
    if (name.left(4) == "file")
        name = QUrl(name).toLocalFile();
    else if (name.left(3) == "qrc")
        name = name.mid(3);

    return name;
}

void QuickItemDelegate::paint(QPainter *painter)
{
    painter->setRenderHints(painter->renderHints()
                            | QPainter::Antialiasing
                            | QPainter::SmoothPixmapTransform);

    auto style = QApplication::style();
    auto palette = QApplication::palette();
    QStyleOption option;

    int borderWidth = 2;
    int borderSpacing = 0;
    const QMargins margins(borderWidth + borderSpacing, borderWidth + borderSpacing,
                           borderWidth + borderSpacing, borderWidth + borderSpacing);

    QPixmap pixmap = QPixmap(toLocalFileName(m_source));
    QPainterPath path;
    QRect rect = QRect(0, 0, width(), height());
    path.addEllipse(rect.marginsRemoved(margins));
    painter->setClipPath(path);

    if(!pixmap.isNull()){
        painter->drawPixmap(rect.marginsRemoved(margins), pixmap);
        painter->setClipping(false);
    } else {
        qreal tw = rect.width() / 3.0;
        qreal th = rect.height() / 3.0;

        painter->setPen(Qt::NoPen);
        painter->setBrush(palette.brush(QPalette::Button));
        painter->drawEllipse(rect.marginsRemoved(margins));

        //画+号
        qreal x1 = rect.x() + tw ;
        qreal y1 = rect.y() + rect.height() / 2.0 - 0.5;
        qreal x2 = rect.x() + rect.width() / 2.0 - 0.5;
        qreal y2 = rect.y() + th;
        painter->setBrush(palette.brush(QPalette::Text));
        painter->drawRect(QRectF(x1, y1, tw, 1.0));
        painter->drawRect(QRectF(x2, y2, 1.0, th));
    }

    if ((m_checked == Qt::Checked) && !pixmap.isNull()) {
        painter->setPen(QPen(palette.highlight(), borderWidth));
        painter->setBrush(Qt::NoBrush);
        painter->drawEllipse(rect.adjusted(1, 1, -1, -1));

        //在中间绘制选中小图标
        int radius = 8;
        int cx = rect.marginsRemoved(margins).center().x();
        int cy = rect.marginsRemoved(margins).center().y();
        QRect crect(QPoint(cx - radius, cy - radius), QPoint(cx + radius, cy + radius));
        option.rect = crect;
        option.state |= QStyle::State_On;
        style->drawPrimitive(QStyle::PE_IndicatorItemViewItemCheck, &option, painter);
    }
}

void QuickItemDelegate::mousePressEvent(QMouseEvent *event)
{
    m_mouseStatus = 1;
    emit mouseStatusChanged(m_mouseStatus, event->pos());
    QQuickPaintedItem::mousePressEvent(event);
}

void QuickItemDelegate::mouseMoveEvent(QMouseEvent *event)
{
    m_mouseStatus = 2;
    emit mouseStatusChanged(m_mouseStatus, event->pos());
    QQuickPaintedItem::mouseMoveEvent(event);
}

void QuickItemDelegate::mouseReleaseEvent(QMouseEvent *event)
{
    m_mouseStatus = 3;
    emit mouseStatusChanged(m_mouseStatus, event->pos());
    QQuickPaintedItem::mouseReleaseEvent(event);
}

//StyledDelegate::StyledDelegate(QObject *parent) : QStyledItemDelegate(parent)
//{

//}

//void StyledDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
//{
//    if (!index.isValid()) {
//        QStyledItemDelegate::paint(painter, option, index);
//        return;
//    }

//    painter->setRenderHints(painter->renderHints()
//                            | QPainter::Antialiasing
//                            | QPainter::SmoothPixmapTransform);

//    QStyleOptionViewItem opt(option);
//    initStyleOption(&opt, index);

//    int borderWidth = 1;
//    int borderSpacing = 2;
//    const QMargins margins(borderWidth + borderSpacing, borderWidth + borderSpacing,
//                           borderWidth + borderSpacing, borderWidth + borderSpacing);

//    int width = qMin(opt.rect.width(),opt.rect.height())/4;
//    const QMargins margin(width, width, width, width);

//    QIcon icon = index.data(Qt::DecorationRole).value<QIcon>();

//    QBrush m_brush = opt.palette.brush(QPalette::ToolTipBase);

//    if (opt.state & QStyle::State_Enabled) {
//        if (opt.state & QStyle::State_MouseOver) {
//            m_brush = opt.palette.brush(QPalette::Button);
//        }
//    }

//    QPainterPath path;
//    path.addRoundedRect(opt.rect, radius, radius);
//    painter->setClipPath(path);
//    painter->fillPath(path, m_brush);

//    if(!icon.isNull()){
//        icon.paint(painter,opt.rect.marginsRemoved(margin),Qt::AlignCenter);
//    }

//    QRect textRect = opt.rect;
//    textRect.setY(opt.rect.y() + opt.rect.height()*5/6);
//    painter->drawText(textRect, Qt::TextSingleLine | Qt::AlignHCenter, opt.text);
//}

//QSize StyledDelegate::sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const
//{
//    Q_UNUSED(option)

//    return index.data(Qt::SizeHintRole).toSize();
//}
