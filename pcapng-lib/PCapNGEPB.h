/**
 * @file PCapNGEPB.h
 * @author Abhiroop Datta (abhiroopdatta7@gmail.com)
 * @brief
 * @version 0.1
 * @date 2022-10-24
 *
 * @copyright Copyright (c) 2022
 *
 */

#ifndef __PCAPNG_EPB_H__
#define __PCAPNG_EPB_H__

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
enum EPB_PACKET_FLAG
{
    EPB_PACKET_FLAG_NONE = 0,
    EPB_PACKET_FLAG_RX = 1,
    EPB_PACKET_FLAG_TX = 2,
};

/**
 * @brief Enhanced Packet Block
 * @ref https://www.ietf.org/archive/id/draft-tuexen-opsawg-pcapng-03.html#name-enhanced-packet-block
 */
class EnhancedPacket : public Block
{
  public:
    EnhancedPacket(uint32_t interface, uint32_t timestampHigh, uint32_t timestampLow, uint32_t capturedPacketLength,
                   uint32_t originalPacketLength, char *packet)
        : Block(BLOCK_EPB)
    {
        _interfaceId = interface;
        _timestampHigh = timestampHigh;
        _timestampLow = timestampLow;
        _capturedPacketLength = capturedPacketLength;
        _originalPacketLength = originalPacketLength;
        _packetData.append(packet, originalPacketLength);
    }

    // Option APIs
    void AddDropCount(uint64_t description)
    {
        auto _option = Option(OPTION_DROPCOUNT, (char *)&description, 8);
        this->appendOption(&_option);
    }

    void AddPacketID(uint64_t description)
    {
        auto _option = Option(OPTION_PACKETID, (char *)&description, 8);
        this->appendOption(&_option);
    }

    void AddVerdict(::std::string description)
    {
        auto _option = Option(OPTION_VERDICT, description);
        this->appendOption(&_option);
    }

    // TODO: OPTION_FLAGS
    // TODO: OPTION_HASH
    // TODO: OPTION_QUEUE

  protected:
    void serialize() override
    {
        _value << _interfaceId;
        _value << _timestampHigh;
        _value << _timestampLow;
        _value << _capturedPacketLength;
        _value << _originalPacketLength;
        _value << _packetData;

        auto length = _packetData.size();
        // PAD
        uint8_t padWith = 0;
        auto padLength = Pad32(length) - length;
        for (auto i = 0; i < padLength; i++)
            _value << padWith;
    }

  private:
    uint32_t _interfaceId;
    uint32_t _timestampHigh;
    uint32_t _timestampLow;
    uint32_t _capturedPacketLength;
    uint32_t _originalPacketLength;
    Buffer _packetData;

    enum OPTION_TYPE
    {
        OPTION_FLAGS = 2,
        OPTION_HASH = 3,
        OPTION_DROPCOUNT = 4,
        OPTION_PACKETID = 5,
        OPTION_QUEUE = 6,
        OPTION_VERDICT = 7,
    };
};

} // namespace PCapNG

#endif /* __PCAPNG_EPB_H__ */