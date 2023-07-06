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

    static QVariantMap basic(netipv4 ip);
};

#endif // IPCALCULATOR_H
