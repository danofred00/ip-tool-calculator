#ifndef __NETIP_H__
#define __NETIP_H__

    #include <stdbool.h>
    #include "ipv4.h"

    typedef struct netipv4
    {
        ipv4 ip;
        uint8_t cidr;
    } netipv4;

    netipv4 netipv4_create(ipv4 ip, uint8_t cidr);

    netipv4 netipv4_create_from_str(const char * netip);

    netipv4 netipv4_network(const netipv4 netip);
    
    netipv4 netipv4_broadcast(const netipv4 netip);

    bool netipv4_is_network(const netipv4 netip);

    bool netipv4_is_broadcast(const netipv4 netip);

    char * netipv4_toString(const netipv4 netip);

    void netipv4_print(const netipv4 netip);


#endif