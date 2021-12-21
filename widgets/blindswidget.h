#ifndef BLINDSWIDGET_H
#define BLINDSWIDGET_H

#include <QQuickPaintedItem>
#include <QUrl>

class QPropertyAnimation;

class BlindsWidget : public QQuickPaintedItem
{
    Q_OBJECT

    Q_PROPERTY(qreal m_factor READ factor WRITE setFactor NOTIFY factorChanged)
    Q_PROPERTY(QUrl prePixmap READ prePixmap WRITE setPrePixmap)
    Q_PROPERTY(QUrl nextPixmap READ nextPixmap WRITE setNextPixmap)
    Q_PROPERTY(Qt::Orientation orientation READ orientation WRITE setOrientation)

public:
    explicit BlindsWidget(QQuickPaintedItem *parent = nullptr);

    QUrl prePixmap();

    void setPrePixmap(const QUrl &pixmap);

    QUrl nextPixmap();

    void setNextPixmap(const QUrl &pixmap);

    Qt::Orientation orientation();

    void setOrientation(Qt::Orientation orientation);

    void setFactor(qreal factor);

    qreal factor();

    Q_INVOKABLE void start();

    Q_INVOKABLE void stop();

private:
    QString toLocalFileName(QUrl &name);

    QPixmap scalePixmap(const QPixmap &pixmap,int nMaxWidth,int nMaxHeight);

protected:
    void paint(QPainter *painter) Q_DECL_OVERRIDE;

signals:
    void factorChanged(qreal factor);

public slots:
    void animationValueChanged(const QVariant &value);

private:
    QPropertyAnimation *m_roateAnimation;
    QUrl m_prePixamp;
    QUrl m_nextPixamp;
    qreal m_factor = 0.0;
    Qt::Orientation m_orientation = Qt::Vertical;
};

#endif // BLINDSWIDGET_H
