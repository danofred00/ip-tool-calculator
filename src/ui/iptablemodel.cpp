#include "iptablemodel.h"

IpTableModel::IpTableModel(QList<QHash<QString, QString> > *list, QObject *parent)
    : QAbstractTableModel(parent)
{
    subnetList = list;
}

QVariant IpTableModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if(orientation == Qt::Horizontal && section <COLUMN_COUNT) {

        if(role == Qt::DisplayRole) {
            if(section == 0) return QVariant(tr("No"));
            if(section == 1) return QVariant(tr("Net Address"));
            if(section == 2) return QVariant(tr("Subnet Mask"));
            if(section == 3) return QVariant(tr("Broadcast"));
        }
    }

    return QVariant();
}

int IpTableModel::rowCount(const QModelIndex &parent) const
{
    return subnetList->size();
}

int IpTableModel::columnCount(const QModelIndex &parent) const
{
    return COLUMN_COUNT;
}

QVariant IpTableModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    if(role == Qt::DisplayRole) {
        auto row = index.row();
        auto col = index.column();
        auto subnet = subnetList->value(row);
        // some parsing
        if(col == 0) return QVariant(row);
        else if(col == 1) return QVariant(subnet["network"]);
        else if(col == 2) return QVariant(subnet["netmask"]);
        else if(col == 3) return QVariant(subnet["broadcast"]);

        return QVariant();

    }

    return QVariant();
}

bool IpTableModel::insertRows(int row, int count, const QModelIndex &parent)
{
    beginInsertRows(parent, row, row + count - 1);
    for(int i=row; i<row+count-1; i++) {
        subnetList->insert(row, QHash<QString, QString>());
    }
    endInsertRows();
    return true;
}

bool IpTableModel::insertColumns(int column, int count, const QModelIndex &parent)
{
    beginInsertColumns(parent, column, column + count - 1);

    endInsertColumns();
    return true;
}

bool IpTableModel::removeRows(int row, int count, const QModelIndex &parent)
{
    beginRemoveRows(parent, row, row + count - 1);
    subnetList->remove(row, count);
    endRemoveRows();
    return true;
}

bool IpTableModel::removeColumns(int column, int count, const QModelIndex &parent)
{
    beginRemoveColumns(parent, column, column + count - 1);

    endRemoveColumns();
    return true;
}
