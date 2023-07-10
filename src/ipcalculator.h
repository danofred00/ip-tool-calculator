#ifndef IPCALCULATOR_H
#define IPCALCULATOR_H

#include <QObject>
#include <QVariantMap>
#include "subnet.h"
#include "ipv4.h"
#include "netip.h"

class IpCalculator : public QObject
{
    Q_OBJECT
public:
    IpCalculator(QObject * parent = nullptr);

public slots:

    QVariantMap calculBasic(QString ip);

    static QVariantMap basic(netipv4 ip);

    QVariantMap calculSubnets(QString ip);

    static QVariantMap subnets(subnetv4 ip);

    static bool isValidIpv4(QString ipv4);

    static bool isValidNetWorkIpv4(QString ipv4);
};

#endif // IPCALCULATOR_H
