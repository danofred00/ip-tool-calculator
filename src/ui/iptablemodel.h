#ifndef IPTABLEMODEL_H
#define IPTABLEMODEL_H

#include <QAbstractTableModel>
#include "ipv4.h"
#include "subnet.h"
#include "netip.h"

#define COLUMN_COUNT 4

class IpTableModel : public QAbstractTableModel
{
    Q_OBJECT

public:

    enum class Role {
        StringRole = Qt::UserRole + 1
    };

    explicit IpTableModel(QList<subnetv4> * list, QObject *parent = nullptr);

    // Header:
    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;

    // Basic functionality:
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

    // Add data:
    bool insertRows(int row, int count, const QModelIndex &parent = QModelIndex()) override;
    bool insertColumns(int column, int count, const QModelIndex &parent = QModelIndex()) override;

    // Remove data:
    bool removeRows(int row, int count, const QModelIndex &parent = QModelIndex()) override;
    bool removeColumns(int column, int count, const QModelIndex &parent = QModelIndex()) override;

private:

    QList<subnetv4> * subnetList;
};

#endif // IPTABLEMODEL_H
