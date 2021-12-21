#ifndef PIEIMAGEDISPLAY_H
#define PIEIMAGEDISPLAY_H

#include <QUrl>
#include <QQuickPaintedItem>

class QVariantAnimation;

class PieImageWidget : public QQuickPaintedItem
{
    Q_OBJECT

    Q_PROPERTY(int roateAngle READ roateAngle WRITE setRoateAngle NOTIFY roateAngleChanged)
    Q_PROPERTY(QUrl prePixmap READ prePixmap WRITE setPrePixmap)
    Q_PROPERTY(QUrl nextPixmap READ nextPixmap WRITE setNextPixmap)

public:
    explicit PieImageWidget(QQuickPaintedItem *parent = nullptr);

    QUrl prePixmap();

    void setPrePixmap(const QUrl &pixmap);

    QUrl nextPixmap();

    void setNextPixmap(const QUrl &pixmap);

    int roateAngle();

    void setRoateAngle(int roateAngle);

    Q_INVOKABLE void start();

    Q_INVOKABLE void stop();

    Q_INVOKABLE void pause();

    Q_INVOKABLE bool isRuning();

private:
    QString toLocalFileName(QUrl &name);

    QPixmap scalePixmap(const QPixmap &pixmap,int nMaxWidth,int nMaxHeight);

protected:
    void paint(QPainter *painter) Q_DECL_OVERRIDE;

signals:
    void animationFinished();
    void roateAngleChanged(int roateAngle);

public slots:
    void animationValueChanged(const QVariant &value);

private:
    QVariantAnimation *m_roateAnimation;
    QUrl m_prePixamp;
    QUrl m_nextPixamp;
    int m_roateAngle = 0;
    bool isFinished = false;
};

#endif // PIEIMAGEDISPLAY_H
