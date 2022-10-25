
#include <iostream>

#include "PCapNG.h"

size_t PCapNG::Pad32(size_t val)
{
    return (val % sizeof(uint32_t)) == 0 ? val : (val / sizeof(uint32_t) + 1) * sizeof(uint32_t);
}
