#ifndef IPTABLEMODEL_H
#define IPTABLEMODEL_H

#include <QAbstractTableModel>
#include <QHash>

#define COLUMN_COUNT 4

class IpTableModel : public QAbstractTableModel
{
    Q_OBJECT
    Q_PROPERTY(QList<QHash<QString, QString>> * subnetList READ subnetList WRITE setSubnetList NOTIFY subnetListChanged)
public:

    enum Role {
        DataRole = Qt::UserRole + 1,
        HeadingRole
    };
    Q_ENUM(Role)

    //IpTableModel(QObject *parent = nullptr);
    IpTableModel(QList<QHash<QString, QString>> * list = nullptr, QObject *parent = nullptr);
    ~IpTableModel();

    // Header:
    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;
    QHash<int,QByteArray> roleNames() const override;

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

    // Update data:
    bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::EditRole) override;

    QList<QHash<QString, QString> > *subnetList() const;
    void setSubnetList(QList<QHash<QString, QString> > *newSubnetList);


signals:
    void subnetListChanged();

private:

    QList<QHash<QString, QString>> * m_subnetList;
    bool freeSubnetList;
};

#endif // IPTABLEMODEL_H
