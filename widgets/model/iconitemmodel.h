#ifndef WAITUSEMODEL_H
#define WAITUSEMODEL_H

#include "tablemodeltemplate.h"

#include <QQmlParserStatus>

class IconItemModel : public QAbstractItemModel, public QQmlParserStatus
{
    Q_OBJECT
    Q_PROPERTY(QList<QVariantList> modelData READ getModelData WRITE setModelData)
public:
    explicit IconItemModel(QObject *parent = Q_NULLPTR);
    ~IconItemModel() Q_DECL_OVERRIDE;

    QList<QVariantList> getModelData() const;
    void setModelData(const QList<QVariantList> &modelData);

    Q_INVOKABLE QVariant item(int row, int role) const;
    Q_INVOKABLE bool insertItem(int row, const QVariant &data);
    Q_INVOKABLE bool removeItem(int row);

    virtual QModelIndex index(int row, int column, const QModelIndex &parent = QModelIndex()) const Q_DECL_OVERRIDE;

    virtual QModelIndex parent(const QModelIndex &child) const Q_DECL_OVERRIDE;

    virtual int rowCount(const QModelIndex &parent = QModelIndex()) const Q_DECL_OVERRIDE;

    virtual int columnCount(const QModelIndex &parent = QModelIndex()) const Q_DECL_OVERRIDE;

    // QQmlParserStatus：构造前
    void classBegin() override;
    // QQmlParserStatus：构造后
    void componentComplete() override;

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const Q_DECL_OVERRIDE;
    bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::EditRole) Q_DECL_OVERRIDE;
    // 自定义role
    QHash<int,QByteArray> roleNames() const Q_DECL_OVERRIDE;

private:
    QList<QVariantList> dataList;
};

#endif // WAITUSEMODEL_H
