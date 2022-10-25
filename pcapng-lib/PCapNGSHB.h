/**
 * @file PCapNGSHB.h
 * @author Abhiroop Datta (abhiroopdatta7@gmail.com)
 * @brief
 * @version 0.1
 * @date 2022-10-24
 *
 * @copyright Copyright (c) 2022
 *
 */

#ifndef __PCAPNG_SHB_H__
#define __PCAPNG_SHB_H__

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

enum SHB_OPTION_TYPE
{
    OPTION_SHB_HW = 2,
    OPTION_SHB_OS = 3,
    OPTION_SHB_USRAPPL = 4,
};

/**
 * @brief Section Header Block
 *
 */
class SHB : public Block
{
  public:
    SHB() : Block(BLOCK_SHB)
    {
        _byteOrderMagic = 0x1A2B3C4D;
        _majorVersion = 1;
        _minorVersion = 0;
        _sectionLength = -1;
    }

    SHB(::std::string hwDescription, ::std::string osDescription, ::std::string appDescription) : Block(BLOCK_SHB)
    {
        _byteOrderMagic = 0x1A2B3C4D;
        _majorVersion = 1;
        _minorVersion = 0;
        _sectionLength = -1;
    }

    virtual void serialize() override
    {
        _value << _byteOrderMagic;
        _value << _majorVersion;
        _value << _minorVersion;
        _value << _sectionLength;
    }

  private:
    uint32_t _byteOrderMagic;
    uint16_t _majorVersion;
    uint16_t _minorVersion;
    int64_t _sectionLength;
};

} // namespace PCapNG

#endif /* __PCAPNG_SHB_H__ */