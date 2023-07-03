#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ipv4.h"

uint8_t ipv4_get(const ipv4 ip, int pos)
{
    if(pos >=4)
        exit(EXIT_FAILURE);
    
    uint8_t result = 0x00;
    switch (pos)
    {
    case 3:
        result = (uint8_t) ip;
        break;
    case 2:
        result = (uint8_t) (ip >> 8);
        break;
    case 1:
        result = (uint8_t) (ip >> 16);
        break;
    case 0:
        result = (uint8_t) (ip >> 24);
        break;
    }

    return result;
}

void ipv4_set(ipv4 * ip, int pos, uint8_t value)
{
    if(ip == NULL)
        exit(EXIT_FAILURE);
    
    uint8_t i1 = ipv4_get(*ip, 0),
            i2 = ipv4_get(*ip, 1),
            i3 = ipv4_get(*ip, 2),
            i4 = ipv4_get(*ip, 3);

    switch (pos)
    {
    case 3:
        i4 = value;
        break;
    case 2:
        i3 = value;
        break;
    case 1:
        i2 = value;
        break;
    case 0:
        i1 = value;
        break;
    }

    *ip  = ((ipv4)i1)<<24;
    *ip += ((ipv4)i2)<<16;
    *ip += ((ipv4)i3)<<8;
    *ip += ((ipv4)i4);
}

ipv4 ipv4_create(const uint8_t x, const uint8_t y, const uint8_t z, const uint8_t t)
{
    ipv4 ip = 0x00000000;

    ipv4_set(&ip, 0, x);
    ipv4_set(&ip, 1, y);
    ipv4_set(&ip, 2, z);
    ipv4_set(&ip, 3, t);

    return ip; 
}

ipv4 ipv4_create_from_cidr(const uint8_t cidr) 
{
    ipv4 ip = 0x00000000;
    for(uint8_t i=0; i<cidr; i++)
        ip += (0x01) << ((IPV4_BIT_MAXLENGHT-cidr) + i);

    return ip;
}

char * ipv4_toString(const ipv4 ip)
{
    char buffer[16];
    sprintf(buffer, "%d.%d.%d.%d", ipv4_get(ip,0), ipv4_get(ip,1), ipv4_get(ip,2), ipv4_get(ip,3));
    return strdup(buffer);
}

IpClass ipv4_class(const ipv4 ip)
{
    uint8_t i1 = ipv4_get(ip, 0);
    if(i1<128) return IP_CLASSA;
    else if(i1<192) return IP_CLASSB;
    else if(i1<224) return IP_CLASSC;
    else if(i1<240) return IP_CLASSD;
    else return IP_CLASSE;
}

char ipv4_class2char(IpClass classIp)
{
    char c = 'X';

    switch (classIp)
    {
    case IP_CLASSA: c='A'; break;
    case IP_CLASSB: c='B'; break;
    case IP_CLASSC: c='C'; break;
    case IP_CLASSD: c='D'; break;
    case IP_CLASSE: c='E'; break;
    }
    return c;
}

ipv4 ipv4_defaultNetmask(IpClass classIp)
{
    switch (classIp)
    {
    case IP_CLASSA: return ipv4_create_from_cidr(8);
    case IP_CLASSB: return ipv4_create_from_cidr(16);
    case IP_CLASSC: return ipv4_create_from_cidr(24);
    default: return ipv4_create_from_cidr(0);
    }
}

static void ipv4_octect2bin(uint8_t byte[8], uint8_t octect)
{
    uint8_t r=0, i=0;
    do{
        r = octect % 2;
        octect = octect / 2;
        byte[i] = r;
        i++;
    } while(octect!=0);
}

char * ipv4_tobin(const ipv4 ip)
{
    uint8_t oct;
    char buffer[64];
    memset(buffer, 0, 64);
    //
    char tmp[2];
    for(int i=0; i<4; i++) 
    {
        oct = ipv4_get(ip, i);
        uint8_t byte[8] = {0};
        ipv4_octect2bin(byte, oct);
        for(int j=0; j<8; j++) {
            snprintf(tmp, 2, "%d", byte[7-j]);
            strncat(buffer, tmp, 1);
        }
    }
    return strdup(buffer);
}

char * ipv4_type2str(const IpType type)
{
    switch (type) {
    case IP_PRIVATE:
        return strdup("PRIVATE");
    case IP_PUBLIC:
        return strdup("PUBLIC");
    }
    return strdup("UNKNOW");
}

IpType ipv4_type(const ipv4 ip)
{
    IpClass ipclass = ipv4_class(ip);
    uint8_t oct1 = ipv4_get(ip, 0);
    uint8_t oct2 = ipv4_get(ip, 1);

    switch (ipclass) {
    case IP_CLASSA:
        if(oct1==10 || oct1==127)
            return IP_PRIVATE;
        else
            return IP_PUBLIC;
    case IP_CLASSB:
        if(oct1==172 && (oct2>=16 && oct2<=31))
            return IP_PRIVATE;
        else
            return IP_PUBLIC;
    case IP_CLASSC:
        if(oct1==192 && oct2==168)
            return IP_PRIVATE;
        else
            return IP_PUBLIC;
    }

    return IP_UNKNOW;
}

void ipv4_print(const ipv4 ip)
{
    IpClass classIp = ipv4_class(ip);
    ipv4 defaultnetmask = ipv4_defaultNetmask(classIp);
    char class2char = ipv4_class2char(classIp);

    printf("IP(address=%s, class=%c, defaultnetmask=%s)\n", ipv4_toString(ip), class2char, ipv4_toString(defaultnetmask));
}

static void ipv4_strsplit(char * dst[4], const char ip[], const char sep)
{
    char * t = strdup((char *)ip);

    for(int i=0; i<4; i++) {
        t = strtok((char *)t, ".");
        dst[i] = strdup(t);
        t += strlen(t)+1;
    }
}

/*uint32_t ipv4_math_pow(uint32_t x, uint32_t y)
{
    uint32_t result = 1;
    for(uint32_t i=0; i<y; i++)
        result *= x;
    return result;
}*/

ipv4 ipv4_create_from_str(const char * str)
{
    ipv4 ip = 0x00000000;
    char * t[4] = {0x00, 0x00, 0x00, 0x00};
    ipv4_strsplit(t, str, '.');

    for(int i=0; i<4; i++)
        ipv4_set(&ip, i, (uint8_t)atoi(t[i]));
    return ip;
}

bool ipv4_is_correct_str(const char * ip)
{
    // if the length of str > 15 & i<7, there's an error

    char * dst[4] = { NULL };
    ipv4_strsplit(dst, ip, '.');
    for(int i=0; i<4; i++) {
        int n = atoi(dst[i]);
        if(n<0 || n>255) return false;
    }

    return true;
}
