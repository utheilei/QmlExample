#include "iconitemmodel.h"

#include <QPixmap>
#include <QDebug>

IconItemModel::IconItemModel(QObject *parent)
    : QAbstractItemModel(parent)
{
    dataList.append(QVariantList() << Qt::Unchecked << "qrc:/icon/images/images.png");
    dataList.append(QVariantList() << Qt::Checked << "qrc:/icon/images/images1.png");
    dataList.append(QVariantList() << Qt::Unchecked << "qrc:/icon/images/images2.png");
    dataList.append(QVariantList() << Qt::Unchecked << "qrc:/icon/images/images3.png");
    dataList.append(QVariantList() << Qt::Unchecked << "qrc:/icon/images/images4.png");
    dataList.append(QVariantList() << Qt::Unchecked << "qrc:/icon/images/images.png");
    dataList.append(QVariantList() << Qt::Unchecked << "qrc:/icon/images/images1.png");
    dataList.append(QVariantList() << Qt::Unchecked << "qrc:/icon/images/images2.png");
    dataList.append(QVariantList() << Qt::Unchecked << "qrc:/icon/images/images3.png");
    dataList.append(QVariantList() << Qt::Unchecked << "qrc:/icon/images/images4.png");
    dataList.append(QVariantList() << Qt::Unchecked << "");
}

IconItemModel::~IconItemModel()
{
}

QList<QVariantList> IconItemModel::getModelData() const
{
    return dataList;
}

void IconItemModel::setModelData(const QList<QVariantList> &modelData)
{
    beginResetModel();
    dataList = modelData;
    endResetModel();
}

QVariant IconItemModel::item(int row, int role) const
{
    auto record = dataList.at(row);
    switch (role) {
    case Qt::CheckStateRole:
        return record.at(0);
    case Qt::DecorationRole:
        return record.at(1);
    default:
        break;
    }

    return QVariant();
}

bool IconItemModel::insertItem(int row, const QVariant &data)
{
    if (row < 0 || !data.isValid())
        return false;

    qInfo() << data.toList();

    beginInsertRows(QModelIndex(), row, row);
    dataList.insert(row, data.toList());
    endInsertRows();

    return true;
}

bool IconItemModel::removeItem(int row)
{
    if (row < 0 || row >= rowCount())
        return false;

    qInfo() << "removeItem:" << row;

    beginRemoveRows(QModelIndex(), row, row);
    dataList.removeAt(row);
    endRemoveRows();

    return true;
}

QModelIndex IconItemModel::index(int row, int column, const QModelIndex &parent) const
{
    Q_UNUSED(parent)

    if (row >= dataList.size())
        return QModelIndex();

    if (dataList.empty())
        return QModelIndex();

    if (!dataList.empty())
        return createIndex(row, column);

    return QModelIndex();
}

QModelIndex IconItemModel::parent(const QModelIndex &child) const
{
    Q_UNUSED(child)
    return QModelIndex();
}

int IconItemModel::rowCount(const QModelIndex &parent) const
{
    return parent.isValid() ? 0 : dataList.size();
}

int IconItemModel::columnCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent)
    return 1;
}

void IconItemModel::classBegin()
{
    qInfo() << "classBegin";
}

void IconItemModel::componentComplete()
{
    qInfo() << "componentComplete";
}

bool IconItemModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if (!index.isValid())
        return false;

    int row = index.row();
    if (row >= dataList.count())
        return false;

    switch (role) {
    case Qt::EditRole: {
        dataList[row][1] = value.toString();
        return true;
    }
    case Qt::CheckStateRole: {
        dataList[row][0] = value;
        return true;
    }
    case Qt::DecorationRole: {
        dataList[row][1] = value.toString();
        break;
    }
    default:
        break;
    }

    return false;
}

QHash<int, QByteArray> IconItemModel::roleNames() const
{
    return QAbstractItemModel::roleNames();
}

QVariant IconItemModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    int row = index.row();
    if (row >= dataList.count())
        return QVariant();

    auto record = dataList.at(row);

    switch (role) {
    case Qt::CheckStateRole:
        return record.at(0);
    case Qt::DecorationRole:
        return QPixmap(record.at(1).toString());
    default:
        break;
    }

    return QVariant();
}
