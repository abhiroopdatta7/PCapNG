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

#include "PCapNGBlock.h"
#include "PCapNGBuffer.h"
#include <cstddef>
#include <cstdint>
#include <fstream>
#include <list>
#include <ostream>
#include <sys/types.h>

namespace PCapNG
{
/**
 * @brief Interface Statistics Block
 * @ref https://www.ietf.org/archive/id/draft-tuexen-opsawg-pcapng-03.html#name-interface-statistics-block
 */
class InterfaceStatistics : public Block
{
  public:
    InterfaceStatistics(uint32_t interface, uint32_t timestampHigh, uint32_t timestampLow) : Block(BLOCK_ISB)
    {
        _interfaceId = interface;
        _timestampHigh = timestampHigh;
        _timestampLow = timestampLow;
    }

  protected:
    void serialize() override
    {
        _value << _interfaceId;
        _value << _timestampHigh;
        _value << _timestampLow;
    }

  private:
    uint32_t _interfaceId;
    uint32_t _timestampHigh;
    uint32_t _timestampLow;

    enum OPTION_TYPE
    {
        OPTION_START_TIME = 2,
        OPTION_END_TIME = 3,
        OPTION_IF_RECV = 4,
        OPTION_IF_DROPPED = 5,
        OPTION_FILTER_ACCEPT = 6,
        OPTION_OS_DROP = 7,
        OPTION_USER_DELIV = 8,
    };
};

} // namespace PCapNG

#endif /* __PCAPNG_ISB_H__ */