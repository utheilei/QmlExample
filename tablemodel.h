#ifndef TABLEMODEL_H
#define TABLEMODEL_H

#include <QAbstractTableModel>
#include <QQmlParserStatus>

class TableModel : public QAbstractTableModel, public QQmlParserStatus
{
    Q_OBJECT
    Q_INTERFACES(QQmlParserStatus)
    Q_PROPERTY(QStringList horHeader READ getHorHeader WRITE setHorHeader NOTIFY horHeaderChanged)
    Q_PROPERTY(QVector<QVector<QVariant>> modelData READ getModelData WRITE setModelData)

public:
    explicit TableModel(QObject *parent = nullptr);

    Q_INVOKABLE QStringList getHorHeader() const;
    Q_INVOKABLE void setHorHeader(const QStringList &header);

    Q_INVOKABLE QVector<QVector<QVariant>> getModelData() const;
    Q_INVOKABLE void setModelData(const QVector<QVector<QVariant>> &modelData);
    Q_INVOKABLE QString item(int row, int column) const;
    Q_INVOKABLE bool insertItem(int row, const QVariant &data);
    Q_INVOKABLE bool removeItem(int row);

    // QQmlParserStatus：构造前
    void classBegin() override;
    // QQmlParserStatus：构造后
    void componentComplete() override;
    // 自定义role
    QHash<int,QByteArray> roleNames() const override;

    // 表头
    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;
    bool setHeaderData(int section, Qt::Orientation orientation, const QVariant &value, int role = Qt::EditRole) override;

    // 数据，这三个必须实现
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

    // 编辑
    bool setData(const QModelIndex &index, const QVariant &value,
                 int role = Qt::EditRole) override;

    Qt::ItemFlags flags(const QModelIndex& index) const override;

    // Add data:
    bool insertRows(int row, int count, const QModelIndex &parent = QModelIndex()) override;
    //bool insertColumns(int column, int count, const QModelIndex &parent = QModelIndex()) override;

    // Remove data:
    bool removeRows(int row, int count, const QModelIndex &parent = QModelIndex()) override;
    //bool removeColumns(int column, int count, const QModelIndex &parent = QModelIndex()) override;

signals:
    void horHeaderChanged();

private:
    // 组件是否初始化完成
    bool m_completed = false;
    // 数据，我一般纯展示，用vector就行了
    QVector<QVector<QVariant>> m_modelData;
    // 横项表头
    QStringList m_horHeaderList;
};

#endif // TABLEMODEL_H
