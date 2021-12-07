#ifndef IMAGEITEM_H
#define IMAGEITEM_H

#include <QQuickPaintedItem>
#include <QImage>

class ImageItem : public QQuickPaintedItem
{
    Q_OBJECT

    Q_PROPERTY(QImage source READ source WRITE setSource NOTIFY sourceChanged)
public:
    explicit ImageItem(QQuickPaintedItem *parent = Q_NULLPTR);

    QImage source() const;
    void setSource(const QImage &source);

protected:
    void paint(QPainter *painter) Q_DECL_OVERRIDE;

signals:
    void sourceChanged();

private:
    QImage m_source;

};

#endif // IMAGEITEM_H
