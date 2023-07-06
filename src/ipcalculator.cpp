#include "ipcalculator.h"

IpCalculator::IpCalculator(QObject *parent) : QObject(parent)
{ }

QVariantMap IpCalculator::basic(netipv4 ip)
{
    QVariantMap resultMap;

    resultMap.insert(tr("ip"), QString(ipv4_toString(ip.ip)));
    resultMap.insert(tr("network"), QString(ipv4_toString(netipv4_network(ip).ip)));
    resultMap.insert(tr("type"), QString(ipv4_type2str(ipv4_type(ip.ip))));

    auto bin = QString(ipv4_tobin(ip.ip));
    for(auto i=1; i<=3; i++)
        bin.insert(i*8 + i-1, '.'); // add '.' char after one octect
    resultMap.insert(tr("binary"), bin);
    resultMap.insert(tr("class"), QChar(ipv4_class2char(ipv4_class(ip.ip))));
    resultMap.insert(tr("netmask"), QString(ipv4_toString(ipv4_create_from_cidr(ip.cidr))));
    resultMap.insert(tr("broadcast"), QString(ipv4_toString(netipv4_broadcast(ip).ip)));
    resultMap.insert(tr("hex"), "0x" + QString::number(ip.ip, 16).toUpper());
    resultMap.insert(tr("decimal"), ip.ip);

    return resultMap;
}
