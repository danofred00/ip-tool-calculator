#include "ipcalculator.h"

IpCalculator::IpCalculator(QObject *parent) : QObject(parent)
{ }

QVariantMap IpCalculator::calculBasic(QString ip)
{
    std::string ip_std = ip.toStdString();
    return basic(netipv4_create_from_str(ip_std.c_str()));
}

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

QVariantMap IpCalculator::calculSubnets(QString ip)
{
    std::string ipStr = ip.toStdString();
    netipv4 netip = netipv4_create_from_str(ipStr.c_str());
    return subnets(subnetv4_create(netip));
}

QVariantMap IpCalculator::subnets(subnetv4 subnet)
{
    QVariantMap map;
    netipv4 netip = subnet.netip;

    map.insert("netmask",QString(ipv4_toString(ipv4_create_from_cidr(netip.cidr))));
    map.insert("class", QChar(ipv4_class2char(ipv4_class(netip.ip))));
    map.insert("bin", QString(ipv4_tobin(netip.ip)));
    map.insert("type", QString(ipv4_type2str(ipv4_type(netip.ip))));
    map.insert("base", QString(ipv4_toString(subnetv4_base(netip))));
    auto nets = subnetv4_net_maxcount(subnet);
    map.insert("subnetcount", nets);
    map.insert("decimal", netip.ip);
    map.insert("hex", "0x" + QString::number(netip.ip, 16).toUpper());
    map.insert("hosts", subnetv4_host_maxcount(subnet));

    // insert subnets
    QList<QVariant> list;
    QHash<QString,QVariant> hash;
    for (quint32 i = 0; i < nets; ++i) {
        netipv4 net = subnetv4_subnet(subnet, i);
        hash.insert("network", QString(ipv4_toString(net.ip)));
        hash.insert("netmask", QString(ipv4_toString(ipv4_create_from_cidr(net.cidr))));
        hash.insert("broadcast", QString(ipv4_toString(netipv4_broadcast(net).ip)));
        list.append(hash);
    }
    map.insert("subnetlist", list);

    // return final result
    return map;
}

bool IpCalculator::isValidIpv4(QString ipv4)
{
    std::string ip_str = ipv4.toStdString();
    netipv4 netip = netipv4_create_from_str(ip_str.c_str());
    return ipv4_is_correct_str(ip_str.c_str()) && netip.cidr < 25;
}

bool IpCalculator::isValidNetWorkIpv4(QString ipv4)
{
    std::string ip_str = ipv4.toStdString();
    netipv4 netip = netipv4_create_from_str(ip_str.c_str());
    return isValidIpv4(ipv4) && netipv4_is_network(netip);
}
