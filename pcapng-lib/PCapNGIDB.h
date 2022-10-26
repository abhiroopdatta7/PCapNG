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

/**
 * @brief Interface Description Block
 * @ref https://www.ietf.org/archive/id/draft-tuexen-opsawg-pcapng-03.html#name-interface-description-block
 */
class InterfaceDescription : public Block
{
  public:
    typedef enum
    {
        LINKTYPE_NULL = 0,
        LINKTYPE_ETHERNET = 1,
        LINKTYPE_AX25 = 3,
        LINKTYPE_IEEE802_5 = 6,
        LINKTYPE_ARCNET_BSD = 7,
        LINKTYPE_SLIP = 8,
        LINKTYPE_PPP = 9,
        LINKTYPE_FDDI = 10,
        LINKTYPE_PPP_HDLC = 11,
        LINKTYPE_PPP_ETHER = 51,
        LINKTYPE_ATM_RFC1483 = 100,
        LINKTYPE_RAW = 101,
        LINKTYPE_C_HDLC = 104,
        LINKTYPE_IEEE802_11 = 105,
        LINKTYPE_FRELAY = 107,
        LINKTYPE_LOOP = 108,
        LINKTYPE_LINUX_SLL = 113,
        LINKTYPE_LTALK = 114,
        LINKTYPE_PFLOG = 117,
        LINKTYPE_IEEE802_11_PRISM = 119,
        LINKTYPE_IP_OVER_FC = 122,
        LINKTYPE_SUNATM = 123,
        LINKTYPE_IEEE802_11_RADIOTAP = 127,
        LINKTYPE_ARCNET_LINUX = 129,
    } LINK_TYPE;

    InterfaceDescription(LINK_TYPE LinkType) : Block(BLOCK_IDB)
    {
        _linkType = LinkType;
        _reserved = 0;
        _snaplen = 0;
    }

    // Option APIs
    void AddInterfaceName(::std::string description)
    {
        auto _option = Option(OPTION_IDB_IF_NAME, description);
        this->appendOption(&_option);
    }

    void AddInterfaceDescription(::std::string description)
    {
        auto _option = Option(OPTION_IDB_IF_DESCRIPTION, description);
        this->appendOption(&_option);
    }

    void AddIPv4Address(::std::string description)
    {
        auto _option = Option(OPTION_IDB_IF_DESCRIPTION, description.c_str(), 8);
        this->appendOption(&_option);
    }

    void AddIPv6Address(::std::string description)
    {
        auto _option = Option(OPTION_IDB_IF_DESCRIPTION, description.c_str(), 17);
        this->appendOption(&_option);
    }

    void AddMACAddress(::std::string description)
    {
        auto _option = Option(OPTION_IDB_IF_DESCRIPTION, description.c_str(), 6);
        this->appendOption(&_option);
    }

    void AddIFSpeed(uint64_t description)
    {
        auto _option = Option(OPTION_IDB_IF_DESCRIPTION, (char *)&description, 8);
        this->appendOption(&_option);
    }

    // TODO : if_EUIaddr
    // TODO : if_tsresol
    // TODO : if_tzone
    // TODO : if_filter
    void AddOSDescription(::std::string description)
    {
        auto _option = Option(OPTION_IDB_IF_NAME, description);
        this->appendOption(&_option);
    }
    // TODO : if_fcslen
    // TODO : if_tsoffset
    // TODO : if_hardware
    // TODO : if_txspeed
    // TODO : if_rxspeed

  protected:
    void serialize() override
    {
        _value << _linkType;
        _value << _reserved;
        _value << _snaplen;
    }

  private:
    uint16_t _linkType;
    uint16_t _reserved;
    uint32_t _snaplen;

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
};

} // namespace PCapNG

#endif /* __PCAPNG_IDB_H__ */