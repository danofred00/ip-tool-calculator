
#include <stdio.h>
#include "ipv4.h"
#include "subnet.h"
#include "netip.h"

int main(int argc, char const *argv[])
{
    ipv4 ip = ipv4_create(192,168,0,1);
    ipv4_print(ip);

    return 0;
}
