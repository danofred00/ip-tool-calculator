#include "iptablemodel.h"

IpTableModel::IpTableModel(QList<subnetv4> *list, QObject *parent)
    : QAbstractTableModel(parent)
{
    subnetList = list;
}

QVariant IpTableModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if(orientation == Qt::Horizontal && section <COLUMN_COUNT) {

        if(role == Qt::DisplayRole) {
            if(section == 0) return QVariant("No");
            if(section == 1) return QVariant("Net Address");
            if(section == 2) return QVariant("Subnet Mask");
            if(section == 3) return QVariant("Broadcast");
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
        ipv4 ip = 0x00000000;

        // some parsing
        auto netip = subnetList->at(row).netip;
        if(col == 0) return QVariant(row);
        else if(col == 1) ip = netip.ip;
        else if(col == 2) ip = ipv4_create_from_cidr(netip.cidr);
        else if(col == 3) ip = netipv4_broadcast(netip).ip;

        return QVariant(QString(ipv4_toString(ip)));

    }

    return QVariant();
}

bool IpTableModel::insertRows(int row, int count, const QModelIndex &parent)
{
    beginInsertRows(parent, row, row + count - 1);
    subnetv4 subnet = subnetv4_create(netipv4_create(0,0));
    for(int i=row; i<row+count-1; i++) {
        subnetList->insert(row, subnet);
    }
    endInsertRows();
    return true;
}

bool IpTableModel::insertColumns(int column, int count, const QModelIndex &parent)
{
    beginInsertColumns(parent, column, column + count - 1);

//    for(int i=column; i<column+count-1; i++) {

//    }

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
