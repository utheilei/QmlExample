#include "tablemodel.h"

#include <QDebug>
#include <QJsonArray>
#include <QJsonObject>

TableModel::TableModel(QObject *parent)
    : QAbstractTableModel(parent)
{
    QVector<QVector<QVariant> > modelData;
    modelData.append(QVector<QVariant>() << 1 << "hl" << 28 << "ddddddddd");
    modelData.append(QVector<QVariant>() << 2 << "ada" << 32 << "ddddddddd");
    setModelData(modelData);
}

QStringList TableModel::getHorHeader() const
{
    return m_horHeaderList;
}

void TableModel::setHorHeader(const QStringList &header)
{
    m_horHeaderList=header;
    emit horHeaderChanged();
}

QVector<QVector<QVariant> > TableModel::getModelData() const
{
    return m_modelData;
}

void TableModel::setModelData(const QVector<QVector<QVariant> > &modelData)
{
    beginResetModel();
    m_modelData = modelData;
    endResetModel();
}

void TableModel::classBegin()
{
    qInfo() << "TableModel::classBegin()";
}

void TableModel::componentComplete()
{
    qInfo() << "TableModel::componentComplete()";
    m_completed = true;
}

QHash<int, QByteArray> TableModel::roleNames() const
{
    return QAbstractItemModel::roleNames();
}

QString TableModel::item(int row, int column) const
{
    return index(row, column).data().toString();
}

bool TableModel::insertItem(int row, const QVariant &data)
{
    if (row < 0 || !data.isValid())
        return false;

    beginInsertRows(QModelIndex(), row, row);
    m_modelData.insert(row, data.toList().toVector());
    endInsertRows();

    return true;
}

bool TableModel::removeItem(int row)
{
    return removeRows(row, 1);
}

QVariant TableModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    //返回表头数据，无效的返回None
    if(role==Qt::DisplayRole) {
        if(orientation == Qt::Horizontal)
            return m_horHeaderList.value(section);
        else if(orientation==Qt::Vertical)
            return QString::number(section);
    }

    return QVariant();
}

bool TableModel::setHeaderData(int section, Qt::Orientation orientation, const QVariant &value, int role)
{
    if (value != headerData(section, orientation, role)) {
        if(orientation==Qt::Horizontal&&role==Qt::EditRole){
            m_horHeaderList[section]=value.toString();
            emit headerDataChanged(orientation, section, section);
            return true;
        }
    }
    return false;
}


int TableModel::rowCount(const QModelIndex &parent) const
{
    if (parent.isValid())
        return 0;
    return m_modelData.count();
}

int TableModel::columnCount(const QModelIndex &parent) const
{
    if (parent.isValid())
        return 0;
    return m_horHeaderList.count();
}

QVariant TableModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    switch (role) {
    case Qt::DisplayRole:
        return m_modelData.at(index.row()).at(index.column());
    default:
        break;
    }
    return QVariant();
}

bool TableModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if (value.isValid()&&index.isValid()) {
        if(Qt::EditRole==role) {
            m_modelData[index.row()][index.column()] = value;
            emit dataChanged(index, index, QVector<int>() << role);
            return true;
        }
    }
    return false;
}

Qt::ItemFlags TableModel::flags(const QModelIndex &index) const
{
    if (!index.isValid())
        return Qt::NoItemFlags;
    return Qt::ItemIsEnabled|Qt::ItemIsSelectable|Qt::ItemIsEditable;
}

bool TableModel::insertRows(int row, int count, const QModelIndex &parent)
{
    beginInsertRows(parent, row, row + count - 1);

    for (int i = row; i <= row + count - 1; ++i)
        m_modelData.insert(i, QVector<QVariant>());

    endInsertRows();

    return true;
}

//bool EasyTableModel::insertColumns(int column, int count, const QModelIndex &parent)
//{
//    beginInsertColumns(parent, column, column + count - 1);
//    // FIXME: Implement me!
//    endInsertColumns();
//}

bool TableModel::removeRows(int row, int count, const QModelIndex &parent)
{
    beginRemoveRows(parent, row, row + count - 1);

    for (int i = row + count - 1; i >= row; --i)
        m_modelData.removeAt(i);

    endRemoveRows();

    return true;
}

//bool EasyTableModel::removeColumns(int column, int count, const QModelIndex &parent)
//{
//    beginRemoveColumns(parent, column, column + count - 1);
//    // FIXME: Implement me!
//    endRemoveColumns();
//}
