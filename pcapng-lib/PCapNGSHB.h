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
 * @brief Section Header Block
 * @ref https://www.ietf.org/archive/id/draft-tuexen-opsawg-pcapng-03.html#name-section-header-block
 */
class SectionHeader : public Block
{
  public:
    SectionHeader() : Block(BLOCK_SHB)
    {
        _byteOrderMagic = 0x1A2B3C4D;
        _majorVersion = 1;
        _minorVersion = 0;
        _sectionLength = -1;
    }

    // Option APIs
    void AddHWDesc(::std::string description)
    {
        auto _option = Option(OPTION_HW, description);
        this->appendOption(&_option);
    }

    void AddOSDesc(::std::string description)
    {
        auto _option = Option(OPTION_OS, description);
        this->appendOption(&_option);
    }

    void AddUserApplicationDesc(::std::string description)
    {
        auto _option = Option(OPTION_USRAPPL, description);
        this->appendOption(&_option);
    }

  protected:
    void serialize() override
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

    enum OPTION_TYPE
    {
        OPTION_HW = 2,
        OPTION_OS = 3,
        OPTION_USRAPPL = 4,
    };
};

} // namespace PCapNG

#endif /* __PCAPNG_SHB_H__ */