/**
 * @file PCapNGIDB.h
 * @author Abhiroop Datta (abhiroopdatta7@gmail.com)
 * @brief
 * @version 0.1
 * @date 2022-10-24
 *
 * @copyright Copyright (c) 2022
 *
 */

#ifndef __PCAPNG_IDB_H__
#define __PCAPNG_IDB_H__

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

enum IDB_OPTION_TYPE
{
    OPTION_IDB_IF_NAME = 2,
    OPTION_IDB_IF_DESCRIPTION = 3,
    OPTION_IDB_IPv4_ADDR = 4,
    OPTION_IDB_IPv6_ADDR = 5,
    OPTION_IDB_MAC_ADDR = 6,
    OPTION_IDB_EUI_ADDR = 7,
    OPTION_IDB_IF_SPEED = 8,
    OPTION_IDB_IF_TSRESOL = 9,
    OPTION_IDB_IF_TZONE = 10,
    OPTION_IDB_IF_FILTER = 11,
    OPTION_IDB_IF_OS = 12,
    OPTION_IDB_IF_FCSLEN = 13,
    OPTION_IDB_IF_TSOFFSET = 14,
    OPTION_IDB_IF_HARDWARE = 15,
    OPTION_IDB_IF_TXSPEED = 16,
    OPTION_IDB_IF_RXSPEED = 17,
};

typedef enum
{
    IDB_LINKTYPE_NULL = 0,
    IDB_LINKTYPE_ETHERNET = 1,
    IDB_LINKTYPE_AX25 = 3,
    IDB_LINKTYPE_IEEE802_5 = 6,
    IDB_LINKTYPE_ARCNET_BSD = 7,
    IDB_LINKTYPE_SLIP = 8,
    IDB_LINKTYPE_PPP = 9,
    IDB_LINKTYPE_FDDI = 10,
    IDB_LINKTYPE_PPP_HDLC = 11,
    IDB_LINKTYPE_PPP_ETHER = 51,
    IDB_LINKTYPE_ATM_RFC1483 = 100,
    IDB_LINKTYPE_RAW = 101,
    IDB_LINKTYPE_C_HDLC = 104,
    IDB_LINKTYPE_IEEE802_11 = 105,
    IDB_LINKTYPE_FRELAY = 107,
    IDB_LINKTYPE_LOOP = 108,
    IDB_LINKTYPE_LINUX_SLL = 113,
    IDB_LINKTYPE_LTALK = 114,
    IDB_LINKTYPE_PFLOG = 117,
    IDB_LINKTYPE_IEEE802_11_PRISM = 119,
    IDB_LINKTYPE_IP_OVER_FC = 122,
    IDB_LINKTYPE_SUNATM = 123,
    IDB_LINKTYPE_IEEE802_11_RADIOTAP = 127,
    IDB_LINKTYPE_ARCNET_LINUX = 129,
} IDB_LINK_TYPE;

/**
 * @brief Interface Description Block
 *
 */
class IDB : public Block
{
  public:
    IDB(IDB_LINK_TYPE LinkType) : Block(BLOCK_IDB)
    {
        _linkType = LinkType;
        _reserved = 0;
        _snaplen = 0;
    }

    virtual void serialize() override
    {
        _value << _linkType;
        _value << _reserved;
        _value << _snaplen;
    }

  private:
    uint16_t _linkType;
    uint16_t _reserved;
    uint32_t _snaplen;
};

} // namespace PCapNG

#endif /* __PCAPNG_IDB_H__ */