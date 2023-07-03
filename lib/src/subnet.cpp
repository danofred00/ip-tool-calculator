
#include "subnet.h"
#include "utils.h"

subnetv4 subnetv4_create(netipv4 netip)
{
    subnetv4 subnet;

    if(!netipv4_is_network(netip)) {
        subnet.base = 0;
        subnet.netip = netipv4_create(0, 0); 
    } else {
        subnet.base = subnetv4_base(netip);
        subnet.netip = netip;
    }
    
    return subnet;
}

ipv4 subnetv4_base(const netipv4 netip)
{
    ipv4 ip = 0x00000000;
    IpClass _class = ipv4_class(netip.ip);

    if(_class == IP_CLASSA || _class == IP_CLASSB || _class == IP_CLASSC)
        ipv4_set(&ip, 0, ipv4_get(netip.ip, 0));

    if(_class == IP_CLASSB || _class == IP_CLASSC)
        ipv4_set(&ip, 1, ipv4_get(netip.ip, 1));
    
    if(_class == IP_CLASSC)
        ipv4_set(&ip, 2, ipv4_get(netip.ip, 2));

    return ip;
}

ipv4 subnetv4_first_address(const subnetv4 subnet)
{
    return netipv4_network(subnet.netip).ip + 1;
}

ipv4 subnetv4_last_address(const subnetv4 subnet)
{
    return netipv4_broadcast(subnet.netip).ip - 1;
}

uint32_t subnetv4_host_maxcount(const subnetv4 subnet)
{
    return subnetv4_last_address(subnet) - subnetv4_first_address(subnet) + 1;
}

uint32_t subnetv4_net_maxcount(const subnetv4 net)
{
    IpClass _class = ipv4_class(net.base);
    int8_t count = 0;
    // count additionnal bytes use for network
    switch (_class)
    {
    case IP_CLASSA:
        count = net.netip.cidr - IPV4_CLASSA_DEFAULT_LENGTH + 1;
        break;
    case IP_CLASSB:
        count = net.netip.cidr - IPV4_CLASSB_DEFAULT_LENGTH + 1;
        break;
    case IP_CLASSC:
        count = net.netip.cidr - IPV4_CLASSC_DEFAULT_LENGTH + 1;
        break;
    }
    // 
    if(count <= 0) 
        return 0;
    // if everything is correct, return the good answer
    return (uint32_t) math_pow(2, (double)count-1);
}

netipv4 subnetv4_subnet(const subnetv4 subnet, const uint32_t pos)
{
    uint32_t count = subnetv4_net_maxcount(subnet);
    if(pos >= count || pos < 0)
        return netipv4_create(0,0);
    
    // get number of hosts
    uint32_t hosts = subnetv4_host_maxcount(subnet);
    // pos*count + base = last ip of subnet
    // adding 2 means we take network and broadcast addresses
    return netipv4_create(subnet.base + pos*(hosts+2), subnet.netip.cidr);
}

//char * subnetv4_toString(const subnetv4 subnet)
//{

//}
