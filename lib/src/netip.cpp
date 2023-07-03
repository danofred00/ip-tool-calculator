
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "netip.h"

netipv4 netipv4_create(ipv4 ip, uint8_t cidr)
{
    netipv4 _netip;
    _netip.ip = ip;
    _netip.cidr = cidr;
    return _netip;
}

netipv4 netipv4_create_from_str(const char * netip)
{
    char * s = strtok(strdup(netip), "/");
    ipv4 ip = ipv4_create_from_str(s);
    uint8_t cidr = (uint8_t) atoi(s+strlen(s)+1);
    return netipv4_create(ip, cidr);
}

netipv4 netipv4_network(const netipv4 netip)
{
    ipv4 subnetmask = ipv4_create_from_cidr(netip.cidr);
    return netipv4_create(netip.ip & subnetmask, netip.cidr);
}

netipv4 netipv4_broadcast(const netipv4 netip)
{
    ipv4 _ip = 0x00000000;
    for(uint8_t i=0; i<(IPV4_BIT_MAXLENGHT-netip.cidr); i++)
        _ip += (0x01) << (i);
    
    return netipv4_create(netipv4_network(netip).ip | _ip, netip.cidr);
}

bool netipv4_is_network(const netipv4 netip)
{
    return netip.ip == netipv4_network(netip).ip;
}

bool netipv4_is_broadcast(const netipv4 netip)
{
    return netip.ip == netipv4_broadcast(netip).ip;
}

char * netipv4_toString(const netipv4 netip)
{
    char buffer[32];
    sprintf(buffer, "%s/%u", ipv4_toString(netip.ip), netip.cidr);
    return strdup(buffer);
}

void netipv4_print(const netipv4 netip)
{
    char *addr;
    char *netmask;
    char *broadcast;
    char *network;
    char classIp;
    // init vars
    addr = ipv4_toString(netip.ip);
    netmask = ipv4_toString(ipv4_create_from_cidr(netip.cidr));
    broadcast = ipv4_toString(netipv4_broadcast(netip).ip);
    classIp = ipv4_class2char(ipv4_class(netip.ip));
    network = ipv4_toString(netipv4_network(netip).ip);
    // print
    printf("NetIP(address=%s, class=%c, netmask=%s", addr, classIp, netmask);
    // we check if he's network address
    if(!netipv4_is_network(netip))
        printf(", network=%s", network);
    else 
        printf(", isnetwork=%d", true);
    // check here if it's a broadcast
    if(!netipv4_is_broadcast(netip))
        printf(", broadcast=%s", broadcast);
    else 
        printf(", isbroadcast=%d", true);
    // close the bracket
    printf(")\n");
}
