#ifndef __SUBNET_H__
#define __SUBNET_H__

    #include <stdint.h>
    #include "ipv4.h"
    #include "netip.h"

    typedef struct subnetv4
    {
        ipv4 base;
        netipv4 netip;

    } subnetv4;
    
    subnetv4 subnetv4_create(netipv4 netip);

    ipv4 subnetv4_base(const netipv4 netip);

    ipv4 subnetv4_first_address(const subnetv4 subnet);

    ipv4 subnetv4_last_address(const subnetv4 subnet);

    uint32_t subnetv4_host_maxcount(const subnetv4 subnet);

    uint32_t subnetv4_net_maxcount(const subnetv4 net);

    netipv4 subnetv4_subnet(const subnetv4 subnet, const uint32_t pos);

    // char * subnetv4_toString(const subnetv4 subnet);

#endif
