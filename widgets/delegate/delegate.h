#ifndef DELEGATE_H
#define DELEGATE_H

#include <QQuickPaintedItem>
#include <QStyledItemDelegate>

class QuickItemDelegate : public QQuickPaintedItem
{
    Q_OBJECT
    Q_PROPERTY(Qt::CheckState checked READ checked WRITE setChecked NOTIFY checkedChanged)
    Q_PROPERTY(QString source READ source WRITE setSource NOTIFY sourceChanged)
    Q_PROPERTY(int mouseStatus READ mouseStatus NOTIFY mouseStatusChanged)
public:
    explicit QuickItemDelegate(QQuickPaintedItem *parent = nullptr);

    QString source() const;
    void setSource(QString source);

    Qt::CheckState checked() const;
    void setChecked(Qt::CheckState status);

    int mouseStatus() const;

private:
    QString toLocalFileName(QString &name);

protected:
    // painting
    void paint(QPainter *painter) override;
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;

signals:
    void sourceChanged();
    void checkedChanged();
    void mouseStatusChanged(int status, const QPoint &pos);

private:
    QString m_source;
    Qt::CheckState m_checked = Qt::CheckState::Unchecked;
    int m_mouseStatus = 0;
};

//class StyledDelegate : public QStyledItemDelegate
//{
//    Q_OBJECT
//public:
//    explicit StyledDelegate(QObject *parent = nullptr);

//    // painting
//    void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const;

//    // set item size
//    QSize sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const;

//private:
//    int radius = 20;
//};

#endif // DELEGATE_H
