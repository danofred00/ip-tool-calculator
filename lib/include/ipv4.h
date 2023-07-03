#ifndef __IPV4_H__
#define __IPV4_H__

    #include <stdint.h>
    #include <stdbool.h>

    /*
    #ifndef __cplusplus
        extern "C" {
    #endif
    */
    
    #ifdef LIB_EXPORT
        #define SHARED __declspec(dllexport)
    #else
        #define SHARED __declspec(dllimport)
    #endif
    
    typedef unsigned int ipv4;

    typedef enum IpClass {
        IP_CLASSA, IP_CLASSB, IP_CLASSC, IP_CLASSD, IP_CLASSE
    } IpClass;

    typedef enum IpType {IP_PRIVATE, IP_PUBLIC, IP_UNKNOW} IpType;

    #define IPV4_CLASSA_DEFAULT_LENGTH 8
    #define IPV4_CLASSB_DEFAULT_LENGTH 16
    #define IPV4_CLASSC_DEFAULT_LENGTH 24
    #define IPV4_BIT_MAXLENGHT 32

    uint8_t ipv4_get(const ipv4 ip, int pos);

    void ipv4_set(ipv4 * ip, int pos, uint8_t value);

    ipv4  ipv4_create(const uint8_t x, const uint8_t y, const uint8_t z, const uint8_t t);

    ipv4 ipv4_create_from_cidr(const uint8_t cidr);

    char * ipv4_toString(const ipv4 ip);

    IpClass ipv4_class(const ipv4 ip);

    char ipv4_class2char(IpClass classIp);

    ipv4 ipv4_defaultNetmask(IpClass classIp);

    static void ipv4_octect2bin(uint8_t byte[8], uint8_t octect);

    char * ipv4_tobin(const ipv4 ip);

    char * ipv4_type2str(const IpType type);

    IpType ipv4_type(const ipv4 ip);

    void ipv4_print(const ipv4 ip);

    static void ipv4_strsplit(char * dst[4], const char ip[], const char sep);

    /*extern uintSHARED 32_t ipv4_math_pow(uint32_t x, uint32_t y);*/

    ipv4 ipv4_create_from_str(const char * str);

    bool ipv4_is_correct_str(const char * ip);
    /*
    #ifndef __cplusplus
        }
    #endif
    */
#endif
