
#include <stdint.h>
#include "utils.h"

uint64_t math_pow(int x, int y)
{
    if(y == 0)
        return 1;
    
    return (uint64_t) (x * math_pow(x, --y));
}