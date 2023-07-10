#include "iptablemodel.h"

IpTableModel::IpTableModel(QList<QHash<QString, QString> > *list, QObject *parent)
    : QAbstractTableModel(parent)
{
    if(list != nullptr) {
        m_subnetList = list;
        freeSubnetList = false;
    } else {
        m_subnetList = new QList<QHash<QString, QString>>();
        // add a default value for headers
        m_subnetList->append(QHash<QString, QString>());
        //
        freeSubnetList = true;
    }
}

IpTableModel::~IpTableModel()
{
    if(freeSubnetList)
        delete m_subnetList;
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

QHash<int, QByteArray> IpTableModel::roleNames() const
{
    QHash<int, QByteArray> roles = {
        {DataRole, "data"},
        {HeadingRole, "heading"}
    };

    return roles;
}

int IpTableModel::rowCount(const QModelIndex &parent) const
{
    return m_subnetList->size();
}

int IpTableModel::columnCount(const QModelIndex &parent) const
{
    return COLUMN_COUNT;
}

QVariant IpTableModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    auto row = index.row();
    auto col = index.column();

    if(role == HeadingRole) {
        if(row == 0)
            return true;
        else
            return false;
    }

    if(role == DataRole || role == Qt::DisplayRole) {

        if(row == 0)
            return headerData(col, Qt::Horizontal, Qt::DisplayRole);

        // if user request any thing starting by row 1
        auto subnet = m_subnetList->value(row);
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
    for(int i=row; i<row+count; i++) {
        m_subnetList->append(QHash<QString, QString>());
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
    m_subnetList->remove(row, count);
    endRemoveRows();
    return true;
}

bool IpTableModel::removeColumns(int column, int count, const QModelIndex &parent)
{
    beginRemoveColumns(parent, column, column + count - 1);

    endRemoveColumns();
    return true;
}

bool IpTableModel::setData(const QModelIndex &index, const QVariant &value, int role)
{

    auto row = index.row();
    auto column = index.column();

    if(role == Qt::EditRole) {

        QString key;
        if(column == 1) key = "network";
        else if(column == 2) key = "netmask";
        else if(column == 3) key = "broadcast";
        else key = QString();

        if(!key.isEmpty()) {
            QHash<QString,QString> hash;
            hash.insert(m_subnetList->at(row));
            hash.insert(key,value.toString());

            // update hash in list
            m_subnetList->remove(row);
            m_subnetList->insert(row, hash);
        }
        // signal to the view thaht some data changed
        emit dataChanged(index, index, {role});
        return true;
    }

    return false;
}

QList<QHash<QString, QString> > *IpTableModel::subnetList() const
{
    return m_subnetList;
}

void IpTableModel::setSubnetList(QList<QHash<QString, QString> > *newSubnetList)
{
    if(newSubnetList == m_subnetList)
        return;

    m_subnetList = newSubnetList;
    emit subnetListChanged();
}
