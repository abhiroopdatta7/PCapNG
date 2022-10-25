/**
 * @file PCapNGISB.h
 * @author Abhiroop Datta (abhiroopdatta7@gmail.com)
 * @brief
 * @version 0.1
 * @date 2022-10-24
 *
 * @copyright Copyright (c) 2022
 *
 */

#ifndef __PCAPNG_ISB_H__
#define __PCAPNG_ISB_H__

#include "PCapNGBase.h"
#include "PCapNGBuffer.h"
#include <cstddef>
#include <cstdint>
#include <fstream>
#include <list>
#include <ostream>
#include <sys/types.h>

namespace PCapNG
{

enum ISB_OPTION_TYPE
{
    OPTION_ISB_START_TIME = 2,
    OPTION_ISB_END_TIME = 3,
    OPTION_ISB_IF_RECV = 4,
    OPTION_ISB_IF_DROPPED = 5,
    OPTION_ISB_FILTER_ACCEPT = 6,
    OPTION_ISB_OS_DROP = 7,
    OPTION_ISB_USER_DELIV = 8,
};

/**
 * @brief Interface Description Block
 *
 */
class ISB : public Block
{
  public:
    ISB(uint32_t interface, uint32_t timestampHigh, uint32_t timestampLow) : Block(BLOCK_ISB)
    {
        _interfaceId = interface;
        _timestampHigh = timestampHigh;
        _timestampLow = timestampLow;
    }

    virtual void serialize() override
    {
        _value << _interfaceId;
        _value << _timestampHigh;
        _value << _timestampLow;
    }

  private:
    uint32_t _interfaceId;
    uint32_t _timestampHigh;
    uint32_t _timestampLow;
};

} // namespace PCapNG

#endif /* __PCAPNG_ISB_H__ */